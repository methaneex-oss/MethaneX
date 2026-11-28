# DF-02 Engineering Message Bus / Task-Ledger Authority Adjudication — 2026-11-28

## Scope and evidence boundary

This is a bounded source/API/build/test-reachability adjudication for the engineering coordination cohort. It compares exact immutable blobs at candidate PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0` and donor PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`, then verifies the current PR #203 branch still matches the candidate-shaped files for the inspected paths. It is additive audit evidence only. No runtime source, baseline, donor adoption, retirement, merge, or gate decision is made.

Inspected exact blobs:

| Path | Candidate SHA | Donor SHA | Current PR #203 |
|---|---|---|---|
| `engineering/cpp/include/jarvis/engineering/message_bus.hpp` | `2658f6c12d60f3df611f5cc0a01569b51b59bcb7` | `a8a334881dc087e83640c984bf02e1704802754a` | candidate SHA |
| `engineering/cpp/src/message_bus.cpp` | `9811d41fc237e33c80086e33049f9ae482c58c77` | `94700db67f43c8bdb0bcc774f1fb0464f5bff81c` | candidate SHA |
| `engineering/cpp/include/jarvis/engineering/agent.hpp` | candidate file fetched; donor SHA `6acadd5558b7385c5993323ad963ed80b08b6652` | donor adds task dependencies and result revision | current differs from candidate in metadata only; see below |
| `engineering/cpp/src/coordinator.cpp` | `44f42429e9730683bd8b529b37ea4e53c4b09c74` | `e175dd61aaa3d8302aba6381401305db9f034062` | candidate SHA |
| `engineering/cpp/CMakeLists.txt` | `7e2621c8678ad784d6e8c9e777b22b7c5310b855` | `44ad82199248b9a6a53d996d046e2e3eb8265f1c` | candidate SHA |

The connector returned a 404 for the guessed test path `engineering/cpp/tests/message_bus_suite.cpp`; therefore no test-source claim is made for that guessed filename.

## Semantic delta: message bus

Candidate registration and delivery use a `void` handler and report success immediately after invoking the callback. A bounded endpoint queue silently drops the oldest message when full. This means the bus can report `accepted=true` even when the receiver's bounded queue has overflowed, and it has no duplicate identity or retry semantics.

The donor changes the handler contract to `bool`, adds a bounded deduplication window, separates in-flight IDs from accepted IDs, rejects message-ID reuse with different content, length-prefixes the delivery key to avoid delimiter collisions, and propagates receiver rejection as backpressure. The donor endpoint rejects delivery when its queue is full instead of evicting old work.

This is a material authority/reliability delta, not a cosmetic refactor:

- Candidate authority says “the bus accepted/delivered” even when the endpoint may have discarded work.
- Donor authority says acceptance requires the receiver to confirm enqueue, and duplicate retries are only acknowledged for the same content.
- Donor deduplication is bounded. Once an ID leaves the retention window, a later retry can be delivered again. The design therefore provides bounded idempotency, not permanent exactly-once semantics.
- The donor key excludes `correlation_id`, message type and payload from the primary lookup key, but `same_content` checks those fields after a key hit. This prevents same-identity mutation while retaining a compact index.
- The donor invokes user code outside the bus mutex, which avoids lock reentrancy, but leaves a race window in which unregistering an agent does not cancel an already-copied handler invocation. This requires lifecycle tests and is not closed by source inspection.

## Semantic delta: engineering task authority

Candidate `EngineeringTask` has no dependency list and `AgentResult` has no revision field. Candidate `EngineeringCoordinator::dispatch` validates the supplied task and descriptor, asks an authorizer, then executes directly through the boundary. It has no durable task state, claim/version check, transition recording, exception-to-ledger conversion, result identity verification, or durable completion requirement.

Donor `EngineeringTask` adds durable task dependencies and `AgentResult` adds a revision field. Donor `dispatch_tracked` reads a task from `EngineeringTaskLedger`, checks existence, expected version and queued status, uses the stored task definition as authoritative, performs authorization, claims with compare-and-set semantics, transitions to running, catches standard and unknown exceptions, checks returned agent/task identity, and refuses to report accepted completion when ledger persistence fails.

This is the strongest concrete authority correction in the cohort: the donor moves task definition and completion authority from caller memory into a versioned ledger. It does not by itself prove that dependency completion, permission provenance, artifact digests or ledger durability are correct.

## Provenance and retention observations

- The exact candidate/donor blobs are immutable and traceable to frozen PR SHAs.
- The current PR #203 branch still exposes candidate-shaped message-bus/coordinator/CMake blobs for the inspected paths, so the donor's stronger semantics are not currently present in those files.
- Donor deduplication retains only a bounded FIFO of accepted message IDs. Retention policy is explicit in the API, but the security/operational consequence is that replay protection expires.
- The donor task-ledger path references a durable ledger, but this cohort inspection does not establish journal framing, fsync, torn-tail recovery, sender identity authenticity, or cross-process locking.
- No source owner/branch authority beyond the immutable PR SHAs was inferred. Historical branch-tip and retirement authority remain open.

## Build and reachability

Candidate engineering CMake registers five library translation units and one test executable. Donor adds `src/task_ledger.cpp`, requires Threads for tests, and adds a dedicated `jarvis_engineering_task_ledger_suite` target/CTest registration.

The exact donor build change demonstrates that the task-ledger implementation is not merely an unreferenced file in the donor lineage: it is compiled into `jarvis_engineering` and has a dedicated test target. However, the current PR #203 branch still has the candidate CMake file, so the donor task-ledger path is not reachable in the current candidate graph.

No native configure, build, CTest, sanitizer, or fault-injection command was executable through the current connector. Static CMake reachability was inspected only.

## Missing behavioral evidence

The source changes imply required tests that were not executed here:

1. duplicate retry with identical content is acknowledged without a second callback;
2. same message ID with changed correlation/type/payload is rejected;
3. queue-full delivery propagates backpressure and preserves already queued messages;
4. handler throws and the in-flight reservation is released for retry;
5. task claim rejects stale versions and non-queued states;
6. dependency completion is enforced by ledger policy rather than merely stored;
7. returned agent/task identity mismatch cannot complete a task;
8. completion/failure persistence errors are surfaced;
9. unregister versus in-flight delivery has defined lifecycle semantics;
10. bounded deduplication expiry is documented and tested.

## Disposition

- Message-bus source/API semantic comparison: **implemented / source-inspected / native execution blocked / independent verification pending / not accepted**.
- Task-ledger authority comparison: **implemented / source-inspected / native execution blocked / independent verification pending / not accepted**.
- Build/test reachability: **static evidence only / no native execution**.
- Provenance/retention/retirement: **partial; immutable refs known, historical owner authority and retirement not closed**.
- DF-02 path closure: **OPEN**. This cohort provides evidence but does not select donor code, establish a baseline, or authorize implementation.

## Capability benchmark

If Tony Stark built real JARVIS with the candidate message bus and coordinator, the system would have a serious reliability defect: it could claim delivery after silently evicting queued work, and it could accept task execution without a durable, versioned authority record. The donor semantics are materially closer to a reliable engineering control plane, but they still describe a bounded local mechanism, not autonomous cognition, perception, general reasoning or closed-loop real-world usefulness. The design is useful infrastructure; it is not JARVIS by itself.

