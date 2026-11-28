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


## Builder self-review correction and deeper task-ledger source inspection — 2026-11-28

A Builder self-review re-fetched the exact candidate and donor files rather than relying on the preceding report summary. This review found one reporting omission and one imprecise table entry; both are corrected here.

### Corrected exact API identity

The candidate and current PR #203 engineering/cpp/include/jarvis/engineering/agent.hpp are the same blob:
- Candidate PR #192 frozen blob: b71c525a97790f460535713d85a705db086c55ac.
- Current PR #203 blob: b71c525a97790f460535713d85a705db086c55ac.
- Donor PR #97 blob: 6acadd5558b7385c5993323ad963ed80b08b6652.

The earlier table wording “current differs from candidate in metadata only” was inaccurate. The current file is byte-identical to the candidate file. The donor adds EngineeringTask::dependencies and AgentResult::revision. No current-candidate metadata-only delta was found.

### Corrected test-source inventory

The earlier 404 concerned only the guessed path engineering/cpp/tests/message_bus_suite.cpp; it did not establish that the donor had no task-ledger test. The donor does contain:
- engineering/cpp/tests/task_ledger_suite.cpp, blob e90c062261c95ff99d4b1bdcb55ce7bfad0512ec.
- Donor engineering/cpp/CMakeLists.txt, blob 44ad82199248b9a6a53d996d046e2e3eb8265f1c, registers jarvis_engineering_task_ledger_suite and CTest name of the same spelling.
- Candidate CMake blob 7e2621c8678ad784d6e8c9e777b22b7c5310b855 does not register that suite or compile task_ledger.cpp.

The test source covers task creation, dependency gating, compare-and-swap stale-claim rejection, claim/start/complete/block/requeue, restart reconstruction, incomplete-tail truncation, independent ledger instances and a two-thread claim race. This is meaningful source-level test-contract evidence; it was not executed in this Builder run.

### New source-level findings from exact donor task-ledger inspection

Additional exact donor blobs:
- engineering/cpp/include/jarvis/engineering/task_ledger.hpp: 95d3f2e42be742f9e75aed8e55ea389723534a64.
- engineering/cpp/src/task_ledger.cpp: 7acff8990319392c9984035a4a14cc83f7154072.
- engineering/cpp/tests/task_ledger_suite.cpp: e90c062261c95ff99d4b1bdcb55ce7bfad0512ec.
- engineering/cpp/include/jarvis/engineering/coordinator.hpp: fc2cced25d47b23893571a100ee7f36a05d37a9b.
- engineering/cpp/src/agent.cpp: blob SHA not recorded in this pass; do not infer one.

The following defects/limitations are directly visible in the fetched task_ledger.cpp source:

1. **Integer parser narrowing is unchecked.** parse_integer<T> parses into unsigned long long and casts to T without checking parsed <= numeric_limits<T>::max(). Subsequent enum-range checks operate on the narrowed value. Out-of-range serialized values can therefore wrap/narrow before validation; this requires malformed-journal tests and a root-cause correction before any ledger trust claim.
2. **Journal replay does not validate the full task definition as immutable.** When a task ID already exists, load_locked() compares only version continuity, task ID, objective and dependencies. It does not compare required capabilities, permissions, input/output artifacts, maximum risk or maximum cost. A modified later journal record can change those authority-relevant fields while passing the visible replay checks.
3. **Journal replay checks version continuity but not legal state-transition continuity.** A complete record with the next version can change status without proving that the previous status permits that transition. API methods enforce selected transitions, but replay does not independently enforce them.
4. **Requeue carries prior-attempt evidence forward.** requeue() clears assigned agent, base/result revision and updates detail, but leaves record.evidence intact. The latest task snapshot can therefore expose evidence from an earlier failed/blocked attempt without an explicit attempt identity or provenance boundary.
5. **Completion evidence is not independently validated.** complete() accepts an empty result revision and arbitrary evidence; dispatch_tracked() verifies result agent/task identity but does not verify expected artifact types, artifact locations, content digests or that the revision identifies the produced artifact set.
6. **Append durability remains weaker than the “durable ledger” label may suggest.** append_record() writes a newline-delimited hex record and calls stream flush, but no file or directory fsync is present. Torn-tail recovery truncates to the last newline; records have no checksum/authentication. A flush is not a power-loss durability guarantee.
7. **The test suite does not exercise the malformed/tampered journal cases above.** It tests a partial final append and normal CAS/lifecycle behavior, but not integer narrowing, unauthorized task-definition mutation, illegal replay transitions, stale evidence across requeue, empty revision, artifact digest mismatch, or fsync/power-loss guarantees.

These findings are static source observations, not demonstrated exploits or executed failures. They are assigned to the donor implementation lineage only; they do not imply that the donor should be selected or adopted. The candidate absence of this ledger is a capability gap, while the donor implementation has its own correctness and integrity gaps. Both facts must remain visible in any later authority adjudication.

### Updated verification ledger for this cohort

| Item | Status | Evidence / limitation |
|---|---|---|
| Candidate/donor API and source comparison | Implemented; source re-fetched | Exact immutable blob SHAs above |
| Current PR #203 identity check | Implemented; source re-fetched | Current agent.hpp equals candidate blob exactly |
| Donor task-ledger test-source inspection | Implemented; source-inspected | Exact test blob and CMake registration verified |
| Donor task-ledger parser/replay review | Implemented; source-inspected | Seven concrete limitations above |
| Native configure/build/CTest/sanitizer | Blocked | Current connector exposes no shell/worktree execution; successful CI run below is Configure + Build only and does not run CTest |
| Independent review / blind fresh testing | Pending | Builder cannot issue either verdict |
| Path/authority/retention closure | Open | No source owner selection, donor adoption, retirement or deletion |

### Self-review disposition

The Builder corrected the inaccurate API identity statement and the incomplete test-source inventory. The newly identified donor-ledger defects cannot be fixed in source under the current audit/evidence-only authorization; they are now explicitly recorded as unresolved donor-lineage risks. No runtime source was modified. This cohort remains OPEN and is not ready to be represented as a complete DF-02 disposition.

### Exact source anchors for the seven findings

All line numbers below refer to donor blob 7acff8990319392c9984035a4a14cc83f7154072 at PR #97 frozen HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25:
- Integer narrowing: task_ledger.cpp lines 133–140.
- Incomplete immutable-task comparison and version-only replay continuity: lines 284–294; the equality checks are limited to task ID, objective and dependencies.
- No replay transition validation: same replay loop, lines 284–294; no previous-status/current-status transition predicate is applied.
- Requeue retains prior evidence: lines 446–464; evidence is not cleared or attempt-scoped.
- Completion does not validate revision/artifacts: lines 385–404; revision is assigned without non-empty or artifact/digest validation.
- Append durability: lines 304–309; stream flush only, with no fsync call in this function.
- Torn-tail recovery: lines 273–300; final incomplete line is truncated to last newline, but complete records have no checksum/authentication verification.

The supporting donor agent validation file was also fetched and SHA-verified: engineering/cpp/src/agent.cpp blob d922dab52bd2f8d774f3734686da21391cabbf19. Its valid_task() checks task ID/objective, non-empty required capabilities and finite non-negative maximum cost; it does not validate dependency semantics itself. EngineeringTaskLedger::create() performs dependency existence/duplicate/self checks, while the journal replay omissions above remain.

These anchors improve reproducibility but do not replace malformed-journal or crash/fault-injection execution.

 
## Engineering subproject build graph and task-ledger source review — 2026-11-28

### Exact CMake reachability

There is no repository-root CMakeLists.txt and no engineering/CMakeLists.txt on candidate or donor refs. engineering/cpp/CMakeLists.txt is a standalone CMake project; .github/workflows/engineering.yml runs CMake from working-directory engineering/cpp. It is not part of the core/cpp target graph.

Frozen candidate:
- CMake blob 7e2621c8678ad784d6e8c9e777b22b7c5310b855.
- Static library has five TUs: agent.cpp, coordinator.cpp, execution.cpp, message_bus.cpp, operator_console.cpp.
- One CTest executable: agent_and_console_suite.

Frozen donor:
- CMake blob 44ad82199248b9a6a53d996d046e2e3eb8265f1c.
- Static library has six TUs: the five candidate TUs plus task_ledger.cpp.
- Two CTest executables: agent_and_console_suite and task_ledger_suite.
- find_package(Threads REQUIRED) is inside BUILD_TESTING, and Threads::Threads is linked only to task_ledger_suite, not PUBLIC/INTERFACE on jarvis_engineering. The library itself uses std::mutex in message_bus/task_ledger. Downstream consumers may not inherit the thread-link requirement; BUILD_TESTING=OFF also skips find_package(Threads). This is a portability/build-interface gap to resolve before the standalone library is consumed broadly.

The engineering workflow blob 46738b2a3b1c6ab66a7f2eeb3d0a9e892be829e7 runs build-test, ASan/UBSan and TSan from engineering/cpp, but triggers only on push/pull_request changes under engineering/** or the workflow file. It has no workflow_dispatch. The frozen donor HEAD c1da222 and historical e737 head have no JARVIS Engineering Layer workflow run. e737 contains donor CMake blob 44ad, but its Brain CI/Native Brain Build runs do not execute engineering/cpp.

A different branch feat/engineering-agent-message-bus has Engineering workflow #199 success, but its CMake blob fdf681b7f23ca4b918a2eff9b39b62acc8e98119 builds a different 13-source worker/pipeline/provider architecture and does not contain task_ledger.cpp or task_ledger_suite.cpp. It is not evidence for the frozen donor task-ledger CMake. Other engineering feature branches likewise use distinct CMake variants. No native build/CTest/ASan/UBSan/TSan result is established for the frozen donor CMake 44ad or task-ledger source.

### Task-ledger behavioral contract

Exact donor blobs:
- task_ledger.hpp 95d3f2e42be742f9e75aed8e55ea389723534a64 (67 lines);
- task_ledger.cpp 7acff8990319392c9984035a4a14cc83f7154072 (494 lines);
- task_ledger_suite.cpp e90c062261c95ff99d4b1bdcb55ce7bfad0512ec (134 lines / 43 assert expressions);
- donor agent_and_console_suite.cpp 7ac8c21e6df0d157d4d95fe87fabae962734139a (74 lines / 31 assertions), versus candidate b1f7a48df7adad95750e6970fa76f75acb2ac6ea (10 lines / 7 assertions).

The task-ledger suite tests:
- task creation and dependency gating;
- compare-and-swap claim/start/complete transitions and stale-version rejection;
- block/requeue/reclaim;
- restart reconstruction of latest state and evidence;
- incomplete final append truncation;
- two independent ledger instances reloading under a shared journal lock before CAS;
- a same-process race where exactly one of two instances can claim the same version.

Positive design evidence: JournalFileLock uses LockFileEx on Windows and flock on POSIX; every mutation acquires the path lock and reloads the journal before version comparison. load_locked checks resize_file errors for a torn tail and fails closed on malformed complete records. This is stronger than an instance-local mutex alone.

### Self-review defects and gaps

1. Completion does not require evidence. task_ledger.hpp lines 40–42 declares complete(..., evidence = {}, detail = {}); task_ledger.cpp lines 385–403 checks task/version/status/agent but accepts an empty result_revision and empty evidence vector. The test supplies evidence but never asserts that evidence-free completion is rejected. This conflicts with evidence-before-completion governance.
2. Requeue retains stale evidence. task_ledger.cpp lines 446–464 clears assignment/base/result revision but does not clear record.evidence. Because the record has no attempt ID or per-attempt evidence history, evidence from a prior attempt remains attached to a newly queued attempt until replaced by a later complete/fail.
3. Replay does not validate legal status transitions. load_locked lines 282–294 checks version increment and immutable task id/objective/dependencies, but does not validate allowed prior-status -> next-status transitions or the actor/assignment rules enforced by public methods. The line journal has no checksum/MAC, so a validly hex-encoded modified record can alter status/evidence without detection.
4. parse_integer uses stoull then static_cast<T> without checking parsed <= numeric_limits<T>::max (lines 132–140). For unsigned risk/status fields, oversized values can wrap before enum-range validation.
5. append_record flushes and checks stream.good() (lines 304–309) but does not fsync/fdatasync the journal or containing directory. A successful completion result is not proof of power-loss durability.
6. Evidence is weakly typed. Serialization stores only AgentEvidence.kind and .value (lines 185–189); no immutable source path, blob hash, signer, timestamp, or verifier identity is bound by the ledger itself.
7. The file lock serializes independent instances, but the test uses two instances in one process, not two OS processes. No cross-process stress, lock-owner crash, lock timeout or Windows-specific runtime test exists.
8. The journal has no checksum/MAC. Hex encoding protects delimiters, not tampering or valid-field substitution. Corrupt complete records fail closed, but validly re-encoded modifications are not authenticated.
9. CMake does not propagate Threads::Threads from the static library to consumers.

The donor test's 43 assertions are valuable behavioral evidence at source level, but there is no native CI result for the frozen donor task-ledger CMake/source. The CMake file is not reachable from the core/cpp build and the available successful engineering workflow run #199 is a different 13-source architecture without the task ledger.

No runtime source or CMake was changed. These are Builder findings; completion-evidence enforcement, replay validation, numeric overflow checks, durability, and transitive thread linkage require future implementation authorization. Task-ledger adoption/retirement remains a Project Director decision.

 
### Evidence contract precision correction

The donor agent.hpp blob 6acadd5558b7385c5993323ad963ed80b08b6652 defines AgentArtifact {type, location, digest}, AgentEvidence {kind, value}, and AgentResult {accepted, agent_id, task_id, reason, artifacts, evidence, revision}. EngineeringTaskLedger::complete accepts only result_revision and vector<AgentEvidence>; EngineeringTaskRecord stores only that evidence vector and result_revision. It does not accept/store AgentArtifact digests/locations, the AgentResult.accepted flag, AgentResult.task_id/agent_id, or a verifier identity. The caller can therefore call complete with empty evidence, empty revision, or a result that was not accepted; the ledger itself cannot bind completion to verified artifact digests. This sharpens finding 6: the ledger is a versioned task-state journal, not an authenticated evidence-verification authority.

 
## Integration reachability and real-agent capability boundary — 2026-11-28

The production dependency graph is narrower than the names imply:
- donor coordinator.hpp blob fc2cced25d47b23893571a100ee7f36a05d37a9b and coordinator.cpp blob e175dd61aaa3d8302aba6381401305db9f034062 integrate EngineeringTaskLedger through dispatch_tracked.
- donor operator_console.hpp blob 196d3a6755aa7f6cf29a8f5d46a65764c27c9964 and operator_console.cpp blob bf94b8779f79fb52fc3bc39ebd8ff59b5fa13b41 integrate AgentMessageBus through AgentCommunicationEndpoint.
- The donor coordinator does not reference MessageBus. The message bus is used by the operator console, not by dispatch_tracked or EngineeringAgent::execute.
- EngineeringAgent remains an abstract interface in agent.hpp; agent.cpp contains validation helpers, not concrete agent implementations. EngineeringCoordinator receives a caller-supplied EngineeringAgent reference; it does not own/register/spawn a workforce.
- AgentCommunicationEndpoint is a generic endpoint; it is not embedded in or adapted to EngineeringAgent. The test creates a generic "builder" endpoint, not a concrete EngineeringAgent that receives a bus request and executes the task.
- dispatch_tracked invokes EngineeringExecutionBoundary::run synchronously. It does not publish task messages through AgentMessageBus. Thus task state and operator messaging are separate mechanisms, not an integrated multi-agent execution fabric.
- Coordinator::rank uses a static score: reliability × availability factor ÷ (1 + estimated_cost). It does not update reliability from task outcomes or use per-task historical performance. It is deterministic ranking, not adaptive agent learning.

A concrete failure-recording gap exists in donor coordinator.cpp lines 58–61: when AgentResult.agent_id/task_id mismatch, it calls ledger.fail(...) but ignores the return value. If that durable failure transition fails, dispatch_tracked still returns an identity error without the "; failure was not durably recorded" qualification used in the exception and ordinary-failure paths. The task can remain running with no durable failure record. This is inconsistent failure handling.

The donor coordinator trusts result.accepted and passes result.revision and result.evidence to ledger.complete, but does not pass result.artifacts, validate artifact digests, require a non-empty revision/evidence set, or verify a signed evaluator identity. The task ledger does not store AgentArtifact fields or AgentResult.accepted. This means the control plane can record a task as completed without an independently verifiable output artifact.

Capability verdict: the engineering subproject contains useful primitives—bounded message transport, operator console, task state ledger, eligibility/ranking and synchronous execution boundary—but it is not yet a real autonomous multi-agent workforce. There is no concrete agent implementation in this target, no message-bus-to-agent execution adapter, no durable message queue, and no outcome-driven agent selection. Under the MCU JARVIS benchmark, this is a control-plane foundation, not a capable adaptive agent workforce. Do not describe it as a working autonomous multi-agent system.

No runtime source was changed. The integration gaps and failure-recording defect remain open for future authorized implementation.

 
## Message-bus accepted-versus-processed semantics — 2026-11-28

The donor message_bus.cpp blob 94700db67f43c8bdb0bcc774f1fb0464f5bff81c lines 64–115 marks a message accepted after the recipient handler returns true. AgentCommunicationEndpoint::receive at line 126 returns true once it appends the message to an in-memory pending_messages deque. The bus then stores the message in accepted_messages_ and acknowledges same-ID retries without redelivery (lines 101–115). AgentCommunicationEndpoint::drain at line 127 removes all pending messages and returns them; there is no acknowledgement, negative acknowledgement, requeue or durable processing receipt.

Concrete loss scenario:
1. Sender sends message ID M; endpoint receive enqueues M and returns true.
2. Bus stores M in accepted_messages_ and reports "message delivered".
3. Endpoint is destroyed or drain() removes M and the consumer crashes before processing it.
4. Sender retries M to a re-registered endpoint with the same run/workspace/agent identity.
5. The bus finds M in accepted_messages_ and returns "duplicate retry acknowledged without redelivery"; the new endpoint never receives M.

Therefore the bus provides bounded deduplication of successful in-memory enqueue, not durable delivery, at-least-once processing or exactly-once execution. The 65,536-entry FIFO eventually evicts old IDs, after which an old retry may be delivered again. There is no durable queue, ack-after-processing, retry lease, dead-letter path or recovery after process restart. The operator console's receive() drains the endpoint queue without an acknowledgement contract.

Required future semantics must be named precisely: either durable at-least-once delivery with consumer acknowledgements/idempotent handlers, or explicitly best-effort in-memory enqueue with a documented loss window. Do not describe the current result as verified task execution or reliable message processing.

 
### Self-review precision: at-most-once enqueue is explicitly tested

The donor agent_and_console_suite.cpp blob 7ac8c21e6df0d157d4d95fe87fabae962734139a (31 assertions) explicitly asserts at lines 42–50 that after a message is enqueued and drained, retrying the same message ID returns accepted while the peer pending queue remains empty. The test comment describes this as preventing duplicate enqueue after an uncertain acknowledgement. It also tests queue overflow rejection and successful retry after the queue is drained.

Therefore the post-drain loss behavior is an explicit at-most-once-in-memory-enqueue contract, not an accidental implementation omission. The design is internally consistent if "accepted" means only "placed in the in-memory endpoint queue" and the consumer is responsible for processing without a later retry. It is not suitable to claim durable/reliable task delivery or at-least-once processing. If JARVIS needs reliable agent work, the bus needs a separate acknowledgement after processing or a durable queue; the current tests intentionally do not provide that.
