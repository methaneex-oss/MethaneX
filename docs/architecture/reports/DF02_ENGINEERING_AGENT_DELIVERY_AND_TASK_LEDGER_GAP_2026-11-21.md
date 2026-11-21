# DF-02 — Engineering-agent delivery and durable task-ledger gap

**Date:** 2026-11-21  
**Candidate source baseline:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor source baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

> **Scope:** exact source/build/test comparison. This is a capability-gap comparison between the candidate and unmerged donor line; it is not a claim that the candidate previously integrated the donor mechanisms and later lost them.

## 1. Durable task ledger is absent from candidate source and build

| Artifact | Candidate | Donor |
|---|---|---|
| `engineering/cpp/include/jarvis/engineering/task_ledger.hpp` | absent | `95d3f2e42be742f9e75aed8e55ea389723534a64` |
| `engineering/cpp/src/task_ledger.cpp` | absent | `7acff8990319392c9984032c21fe4fc81ab25` |
| `engineering/cpp/tests/task_ledger_suite.cpp` | absent | `e90c062261c95ff99d4b1bdcb55ce7bfad0512ec` |

The donor ledger stores durable task records with task definition, status, version, assigned agent, base/result revisions and evidence. It supports dependency checks, versioned compare-and-swap state transitions, recovery from the journal and safe reconstruction of the latest valid state. The candidate has no same-path ledger artifact.

Candidate engineering CMake blob `7e2621c8678ad784d6e8c9e777b22b7c5310b855` compiles five library sources and registers one test. Donor CMake blob `44ad82199248b9a6a53d996d046e2e3eb8265f1c` adds `src/task_ledger.cpp`, finds Threads, and registers `task_ledger_suite.cpp` as a second CTest target. The candidate therefore does not compile or test the donor's durable ledger mechanism.

## 2. Coordinator has no durable tracked-dispatch path

Candidate coordinator header blob `d395db8ce7ae24e40d56aa923758a2251f9188e4` exposes discover/rank/dispatch only. Donor header blob `fc2cced25d47b23893571a100ee7f36a05d37a9b` adds `dispatch_tracked`, which requires a task ID, ledger, expected version and base revision.

Candidate coordinator source blob `44f42429e9730683bd8b529b37ea4e53c4b09c74` is 12 lines / 2,463 bytes and implements direct in-memory dispatch. Donor source blob `e175dd61aaa3d8302aba6381401305db9f034062` is 78 lines / 6,264 bytes and performs the durable lifecycle:
1. read the stored task and verify the expected version and queued state;
2. use the durable task definition as authoritative;
3. re-check agent eligibility and authorization;
4. claim the task with compare-and-swap;
5. transition to running;
6. execute through the existing boundary;
7. record exception/failure or validated result, including agent identity and exact result revision;
8. reject duplicate/stale dispatch and preserve recovery evidence.

The candidate's basic dispatch remains present; the missing capability is the durable, version-bound, restart-recoverable dispatch contract.

## 3. Message bus silently drops work and lacks idempotent delivery

Candidate message-bus header blob `2658f6c12d60f3df611f5cc0a01569b51b59bcb7` defines a `void` receiver callback and only a payload-size setting. Donor header blob `a8a334881dc087e83640c984bf02e1704802754a` changes the callback to return acceptance/rejection, adds a bounded deduplication window and declares exact delivery-key/content comparison.

Candidate message-bus source blob `9811d41fc237e33c80086e33049f9ae482c58c77` is 18 lines / 3,940 bytes. Its endpoint receive path drops the oldest queued message when the pending queue is full and returns no failure signal to the sender. The bus therefore reports a successful delivery even when the endpoint has silently evicted earlier work. It also has no accepted-message identity window to prevent duplicate delivery after an uncertain acknowledgement.

Donor source blob `94700db67f43c8bdb0bcc774f1fb0464f5bff81c` is 130 lines / 7,085 bytes. It:
- propagates receiver acceptance as backpressure;
- rejects overflow without evicting already queued work;
- releases in-flight reservations after receiver failure so the sender can retry;
- stores accepted message IDs in a bounded FIFO deduplication window;
- acknowledges identical retries without redelivery;
- rejects reuse of an accepted ID with different content;
- uses length-prefixed delivery keys to avoid delimiter collisions.

This is a material reliability and at-least-once delivery/idempotency gap, not a formatting difference.

## 4. Engineering agent task/result contract is also narrower

Candidate agent header blob `b71c525a97790f460535713d85a705db086c55ac` lacks task dependencies and the result revision field. Donor blob `6acadd5558b7385c5993323ad963ed80b08b6652` adds both. Those fields are consumed by the task ledger/coordinator to enforce dependency readiness and bind evidence to an exact result revision.

The same-path agent implementation `agent.cpp` is byte-identical in candidate and donor (`d922dab52bd2f8d774f3734686da21391cabbf19`), so this finding is limited to the data contract and its consumers, not a claimed implementation regression in that file.

## 5. Test evidence

The same-path candidate engineering agent/console suite has seven assertions (blob `b1f7a48df7adad95750e6970fa76f75acb2ac6ea`); donor suite has 31 (blob `7ac8c21e6df0d157d4d95fe87fabae962734139a`). Donor-only task-ledger suite has 43 assertions. The donor agent/console suite covers duplicate retry acknowledgement, conflicting duplicate rejection, bounded queue backpressure, preservation of queued work, retry after draining, durable task dispatch, exact base/result revision recording, stale duplicate dispatch rejection and journal recovery. Candidate CMake registers neither the ledger suite nor the ledger implementation.

## 6. Alternate ownership and disposition

The same donor-identical task-ledger header/source/test and their CMake/coordinator integration exist on alternate branch `ci/priority-one-validation-20261031`, as recorded in the compiled-consumer/alternate-branch report. This is a mature alternate implementation line, not a candidate-baseline successor and not authority to merge or transplant it.

**DF-02 disposition:** the engineering-agent subset is now source/build/test adjudicated. Candidate retains direct coordinator dispatch and a basic message bus, but lacks durable tracked task execution, task dependency/revision evidence, idempotent delivery and backpressure. The task-ledger implementation is absent from the candidate tree/build and has a compiled/tested alternate owner. No source code was changed or copied; no source baseline or adoption is selected.


## 7. Exact same-path source and test blob cross-reference

| Path | Candidate blob | Donor blob |
|---|---|---|
| `engineering/cpp/include/jarvis/engineering/agent.hpp` | `b71c525a97790f460535713d85a705db086c55ac` | `6acadd5558b7385c5993323ad963ed80b08b6652` |
| `engineering/cpp/include/jarvis/engineering/coordinator.hpp` | `d395db8ce7ae24e40d56aa923758a2251f9188e4` | `fc2cced25d47b23893571a100ee7f36a05d37a9b` |
| `engineering/cpp/include/jarvis/engineering/message_bus.hpp` | `2658f6c12d60f3df611f5cc0a01569b51b59bcb7` | `a8a334881dc087e83640c984bf02e1704802754a` |
| `engineering/cpp/src/coordinator.cpp` | `44f42429e9730683bd8b529b37ea4e53c4b09c74` | `e175dd61aaa3d8302aba6381401305db9f034062` |
| `engineering/cpp/src/message_bus.cpp` | `9811d41fc237e33c80086e33049f9ae482c58c77` | `94700db67f43c8bdb0bcc774f1fb0464f5bff81c` |
| `engineering/cpp/tests/agent_and_console_suite.cpp` | `b1f7a48df7adad95750e6970fa76f75acb2ac6ea` | `7ac8c21e6df0d157d4d95fe87fabae962734139a` |
| `engineering/cpp/include/jarvis/engineering/task_ledger.hpp` | absent | `95d3f2e42be742f9e75aed8e55ea389723534a64` |
| `engineering/cpp/src/task_ledger.cpp` | absent | `7acff8990319392c9984035a4a14cc83f7154072` |
| `engineering/cpp/tests/task_ledger_suite.cpp` | absent | `e90c062261c95ff99d4b1bdcb55ce7bfad0512ec` |

The candidate/donor `agent.cpp` blob is identical (`d922dab52bd2f8d774f3734686da21391cabbf19`); no behavioral delta is claimed for that file.


## 8. Task-ledger test scope clarification — 2026-11-21

The 43-assertion task-ledger suite uses multiple independently constructed ledger instances and concurrent/stale operations within the same test process. It does not spawn separate operating-system processes. The implementation uses OS file locking, but the existing suite does not independently validate lock exclusion across two real processes. Describe this as multi-instance/concurrent ledger testing, not as a completed cross-process stress test. A true cross-process test remains required before relying on the ledger for multiple independent builder processes.