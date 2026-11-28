# DF-02 Engineering Agent, Message Bus and Durable Task Ledger Adjudication — 2026-11-27

**Scope:** engineering C++ agent validation, message bus/endpoint, coordinator dispatch, durable task ledger and tests. This is a separate orchestration layer, not proof of JARVIS cognitive autonomy.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds bounded message delivery/backpressure/dedup, tracked dispatch and a cross-process durable task ledger. Source/test inspection only.

## 1. Exact refs

- `engineering/cpp/src/message_bus.cpp`: candidate `9811d41fc237e33c80086e33049f9ae482c58c77`; donor `94700db67f43c8bdb0bcc774f1fb0464f5bff81c`.
- `engineering/cpp/include/jarvis/engineering/message_bus.hpp`: candidate `2658f6c12d60f3df611f5cc0a01569b51b59bcb7`; donor `a8a334881dc087e83640c984bf02e1704802754a`.
- `agent.hpp`: candidate `b71c525a97790f460535713d85a705db086c55ac`; donor `6acadd5558b7385c5993323ad963ed80b08b6652`.
- `agent.cpp` (donor-only): `d922dab52bd2f8d774f3734686da21391cabbf19`.
- `coordinator.cpp`: candidate `44f42429e9730683bd8b529b37ea4e53c4b09c74`; donor `e175dd61aaa3d8302aba6381401305db9f034062`.
- `task_ledger.cpp` (donor-only): `7acff8990319392c9984035a4a14cc83f7154072`.
- Donor agent/console test `7ac8c21e6df0d157d4d95fe87fabae962734139a`; donor task-ledger test `e90c062261c95ff99d4b1bdcb55ce7bfad0512ec`.

## 2. Message bus

Donor message bus:
- requires nonempty run/sender/recipient/message/correlation IDs and payload within configured bytes;
- dedup delivery key is length-prefixed over run/workspace/sender/recipient/message ID;
- rejects message-ID reuse with different content;
- reserves in-flight IDs against concurrent retries;
- invokes handler outside the mutex, releases reservation after exception/rejection;
- keeps bounded recent accepted-message FIFO; accepted retries are acknowledged without redelivery;
- endpoint queues are bounded and return backpressure rather than evicting earlier messages.

This provides bounded in-memory delivery and idempotency within the configured recent-message window, not durable exactly-once delivery.

**Trust gap:** raw `AgentMessageBus::send` does not authenticate or verify that `sender_id` is a registered sender. Recipient registration is checked; sender can be spoofed by a caller of the bus. Endpoint wrappers fix the sender ID for their own send calls, but do not make the bus an authenticated trust boundary. Empty workspace scope permits an endpoint to accept any workspace. No cryptographic sender identity/signature, durable delivery, replay after dedup eviction, or inter-process transport exists.

## 3. Agent validation and coordinator

Donor `valid_descriptor` requires nonempty ID/name, finite nonnegative cost and reliability in [0,1]. `valid_task` requires nonempty task ID/objective, nonempty capability list with nonempty entries, and finite nonnegative maximum cost.

Coordinator eligibility checks capability/permission/artifact-type declarations, availability, risk and budget; ranking uses reliability × availability factor / (1+cost). Tracked dispatch:
- reloads durable queued task and checks expected version;
- validates agent/task, rechecks eligibility/authorization;
- CAS claims, starts, executes through boundary;
- catches exceptions and records failure;
- verifies result task/agent identity (fills blank IDs with expected values);
- records completion/failure with revision/evidence and reports ledger-persistence failure explicitly.

Gaps: descriptor/task validators do not validate enum ranges, empty permission/artifact/dependency elements or duplicate declarations; direct message-bus identity is not authenticated. Coordinator verifies declared output-artifact capability but does not validate actual returned artifacts against task expected outputs (artifacts are not persisted in ledger record); an accepted agent result can contain no artifacts or empty revision. Reliability is a static descriptor field; outcome-based agent calibration is not implemented in this bounded source.

## 4. Durable task-ledger contract

Donor ledger is an append-only hex-encoded versioned record journal with cross-process file locking (Windows LockFileEx / POSIX flock). Operations reload under lock and compare-and-swap version/status. It enforces:
- task creation with dependencies that already exist, unique/nonempty dependency IDs and no self-dependency;
- queued→claimed→running→completed or failed/blocked paths, and explicit requeue;
- claim checks prerequisite tasks completed;
- startup replay of complete newline-terminated records, truncating an incomplete final append;
- persistence of task evidence, revisions, assigned agent and detail.

This is substantially stronger than the candidate's non-tracked coordinator.

## 5. Source-derived ledger integrity/durability gaps

- **Task immutability:** replay transition checks immutable ID/objective/dependencies but does not compare all task constraints (required capabilities/permissions/input/output artifacts, risk, cost). A later record can mutate those fields without rejection.
- **Transition validation:** replay checks version increments and status enum range, but not an explicit legal status-transition graph for every journal record. Live API guards transitions, but malformed journal records can bypass that graph.
- **No checksum:** hex encoding is representation, not integrity. Parseable corruption is not detected.
- **Torn first record:** if a non-newline-terminated journal has no prior newline, the recovery size calculation can truncate to zero, discarding that incomplete file; there is no quarantine/backup. Incomplete-tail handling is not a complete integrity recovery strategy.
- **Durability:** append flushes stream but does not fsync file or directory; lock prevents concurrent writers but not power-loss durability.
- **Result artifacts:** ledger stores evidence and revisions but not `AgentArtifact` records; coordinator does not verify expected artifacts are actually returned.

These are source-level gaps, not reproduced failures.

## 6. Test evidence and limits

Donor agent/console tests cover ranking, direct dispatch, tracked claim/start/complete, stale duplicate dispatch, message dedup/conflicting ID, response handling, bounded queue backpressure/retry. Donor task-ledger suite covers dependency blocking, CAS stale versions, completion, block/requeue, reconstruction, incomplete-tail recovery, two independent ledger instances and a claim race where only one succeeds.

Tests inspected, not run. Gaps: spoofed sender/workspace, dedup eviction replay, payload/type edge cases, message-bus durability, task-record tampering/constraint mutation/status-transition corruption, checksum, first-record torn-tail/quarantine, fsync fault injection, artifact/revision validation, task cycle/dependency fault, cross-platform file-lock failure.

## 7. Five review lenses

1. **Semantics:** bus bounded/idempotent delivery and ledger CAS/replay contract confirmed.
2. **Build/test:** donor tests source inspected; engineering CTest/native execution not available here.
3. **Security/trust:** sender spoofing and task-journal mutation/integrity gaps remain.
4. **Autonomy:** this layer provides agent dispatch/work tracking; no proof of agent reasoning, independent verification or unattended safe operation.
5. **Hostile review:** in-memory bus is not exactly-once durable; ledger flush is not crash durability; agent outputs not independently verified.

## 8. Open obligations / disposition

| Item | State |
|---|---|
| Message bus, agent, coordinator and ledger source | Compared |
| Donor test contracts | Inspected |
| Bounded queue/dedup/CAS/race behavior | Test contract present |
| Sender identity authentication | Gap |
| Ledger immutable constraints/transition/checksum | Gaps |
| Torn-tail/durability/fault tests | Open |
| Output artifact validation/persistence | Gap |
| Full consumer/authority/retention | Open |
| Native tests | Not executed |
| DF-02 | OPEN |

Engineering-agent orchestration remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
