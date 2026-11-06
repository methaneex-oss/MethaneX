# Donor Runtime Reliability — Correlation, Idempotency and Acceptance Contract

**Status:** Documentation-level acceptance contract; implementation and execution tests remain unauthorized by the current Phase 2 review boundary.  
**Donor source baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Relevant donor source:** `core/cpp/src/cognitive_runtime.cpp`, `core/cpp/include/jarvis/core/cognitive_runtime.hpp`, `core/cpp/tests/cognitive_runtime_suite.cpp`  
**Related Phase 2 findings:** P2-I-023, P2-I-028, P2-I-029, P2-I-030, P2-I-035, P2-I-036 and IR-03.

## 1. Purpose and boundary

This document turns the donor runtime concerns into an implementation-neutral contract and deterministic verification plan. It does not prescribe a queue library, persistence engine, thread topology, transport, database, or concrete C++ type. It does not modify or approve donor code.

The contract addresses five separate properties:

1. bounded service fairness between feedback and input work;
2. explicit shutdown admission and in-flight action semantics;
3. identifiable result loss and recoverability under saturation;
4. safe restart/retry behavior across ambiguous external side effects;
5. accounting that distinguishes execution, observation, feedback and learning.

**Exactly-once external execution is not assumed.** If an executor or external system does not support idempotency or authoritative effect lookup, a crash after a side effect but before acknowledgement creates an unknown outcome. The runtime must preserve that uncertainty and reconcile it; it must not claim success, failure or safe replay by guesswork.

## 2. Identity model

The runtime contract requires distinct identities with distinct lifetimes:

| Identity | Meaning | Stability |
|---|---|---|
| `work_id` | One accepted logical input/work item | Stable across scheduling, restart and retry of that logical work |
| `correlation_id` | End-to-end trace identity linking input, cycle, action request, execution, feedback and result | Stable for the logical work and all derived records |
| `action_id` | One logical requested action within a work item | Stable across retries of that same logical action |
| `idempotency_key` | Deduplication identity for one side-effecting action at the external execution boundary | Stable across retries/restarts of the same logical action; never regenerated per attempt |
| `attempt_id` | One concrete dispatch/execution attempt | New for each attempt |
| `result_id` | One immutable published result record | Unique per result record; linked to its work/action/correlation identities |
| `feedback_id` | One immutable action/outcome feedback record | Unique per feedback record; linked to the originating action and correlation |

### 2.1 Required propagation

For every accepted work item, the correlation identity must be created before the first asynchronous handoff and propagated through:

`admission → input queue → CognitiveCycle → decision/action request → executor dispatch → action disposition → secondary feedback → result publication → persistence/replay → caller observation`.

A result-queue drop, rejected feedback, timeout, cancellation or recovery record must retain the same correlation/work/action identity. It is insufficient to create a correlation ID only inside a test fixture or only at result publication.

A retry must retain `work_id`, `correlation_id`, `action_id` and `idempotency_key`, while receiving a new `attempt_id`. A new user request that happens to contain identical text is not automatically the same logical work; identity is assigned by the admission contract, not inferred from payload equality.

### 2.2 Idempotency-key scope and retention

The idempotency key identifies the logical external side effect, not a thread attempt. Its scope must bind at least:

- the authorized principal or execution identity;
- the target external system/resource;
- the logical action identity;
- a canonical action intent/payload identity or equivalent immutable action record;
- the applicable authorization/tenant scope.

The key must be durable before dispatch, retained through restart and all retry/reconciliation windows, and not be reused for a materially different action. Retention must exceed the maximum supported retry/replay/reconciliation horizon. If external deduplication expires earlier, the runtime must not blindly retry after expiry; it must reconcile the effect or retain an `UNKNOWN_EFFECT` state pending operator/authority resolution.

The contract does not mandate that the key be a hash. It mandates stable identity, collision-resistant uniqueness within its scope, durable association and executor-side enforcement or authoritative reconciliation.

## 3. Action/effect lifecycle

The implementation must represent these semantic distinctions even if its internal names differ:

1. `ACCEPTED` — work accepted by runtime admission.
2. `READY` — eligible for scheduling.
3. `DISPATCHED` — an execution attempt was issued with a stable action/idempotency identity.
4. `EFFECT_CONFIRMED` — external effect was independently verified.
5. `EFFECT_REJECTED` — executor/authority explicitly confirms no effect occurred.
6. `EFFECT_UNKNOWN` — timeout, process crash or lost acknowledgement leaves effect uncertain.
7. `FEEDBACK_DURABLE` — consequence/feedback record was durably accepted with lineage.
8. `RESULT_PUBLISHED` — caller-visible result was made available.
9. `RESULT_OBSERVED` — caller acknowledged or otherwise observed the result, where the API promises observation.
10. `RECOVERY_REQUIRED` — an unresolved transition needs reconciliation; it is not a success or failure synonym.

The contract must not collapse:
- decision into authorization;
- dispatch into completion;
- executor return into verified external consequence;
- feedback submission attempt into durable feedback acceptance;
- result publication into caller observation;
- unknown effect into failure;
- persisted record into cognitive learning.

Learning may consume an outcome only after its evidence status and attribution satisfy the relevant cognitive mechanism's acceptance criteria. An unknown external effect must not be fed as a negative or positive outcome.

## 4. Fairness contract

The donor's inspected worker loop selects feedback whenever the feedback queue is non-empty and selects input only when feedback is empty. No quota or aging bound was visible in the inspected loop.

The implementation must define a finite maximum consecutive feedback dispatch count, `N_feedback`, or an equivalent explicit service guarantee. When at least one input is eligible and waiting, the scheduler must select an input after no more than `N_feedback` consecutive feedback dispatches, except for a separately specified and bounded emergency/critical class. Any such exception must have its own budget and cannot silently starve ordinary inputs.

Acceptance is measured by deterministic dispatch order/count, not fragile wall-clock thresholds. The test must hold queue conditions constant and verify the documented service bound. The value of `N_feedback` is an implementation decision to be proposed and justified; it must not be hidden as an unexplained magic constant.

## 5. Shutdown and in-flight work contract

Shutdown has two distinct boundaries:

- **Admission close:** after the runtime enters stopping state, new submissions are rejected with an explicit reason and observable accounting.
- **In-flight disposition:** work accepted before admission closes must be drained, cancelled before dispatch, or retained for recovery according to a documented policy. An already dispatched external action cannot be assumed cancelled merely because the runtime stops.

If an action finishes after shutdown begins and secondary feedback cannot be accepted, the action path must not discard the rejection. It must produce one of:
- a durably persisted feedback record before shutdown completes; or
- an explicit action/work disposition marked pending recovery/reconciliation, retaining correlation/action/idempotency identities and making the loss visible to the caller/operator.

A boolean submission result that is cast to void does not satisfy the contract. Stop must have a documented timeout policy; timed-out in-flight effects become unknown unless independently reconciled.

## 6. Result saturation contract

The donor's inspected bounded result queue drops its oldest queued result when full and increments an aggregate `dropped_results` counter.

A future accepted runtime must provide a recoverable distinction among:
- work never accepted;
- accepted but never dispatched;
- dispatched with unknown effect;
- effect confirmed but result not observed;
- result published and later evicted/dropped;
- result observed by caller.

Every dropped result must be identifiable by `result_id`, `work_id` and `correlation_id`, either in a durable overflow/dead-letter record or an equivalent caller-queryable ledger. Aggregate counts alone are insufficient to reconcile individual work. Backpressure, durable spillover or explicit publication failure are possible implementation strategies; the selected strategy must preserve this semantic contract.

## 7. Restart, retry and idempotency contract

A restart must reconstruct accepted work and action state without inventing outcomes. The critical crash window is:

`external side effect occurs → process crashes/lost acknowledgement → feedback/result not durable`.

On recovery:
1. locate the stable logical action and idempotency key;
2. query the executor/external authority if an authoritative status API exists;
3. if confirmed, persist the verified effect and continue feedback/result publication without repeating the side effect;
4. if explicitly rejected/no effect, record that outcome and permit a policy-authorized retry using the same logical action identity and key;
5. if still unknown and no authoritative idempotency/reconciliation mechanism exists, retain `EFFECT_UNKNOWN` / `RECOVERY_REQUIRED` and do not blindly repeat the external action.

The runtime must not claim exactly-once execution unless the external system's deduplication and reconciliation guarantees establish it. An at-least-once dispatch mechanism with idempotent effect handling may be acceptable; an unqualified exactly-once claim is not.

## 8. Required deterministic test matrix

| Test ID | Scenario | Setup / fault injection | Required assertions |
|---|---|---|---|
| RT-FAIR-01 | Sustained feedback load with waiting input | Keep feedback continuously replenished while at least one input remains eligible; record dispatch sequence | An input is selected within the configured maximum consecutive feedback dispatch bound; no starvation by unbounded feedback preference |
| RT-FAIR-02 | Feedback burst ends / multiple inputs wait | Queue a known sequence of feedback and input work | Documented fairness policy preserves bounded service and does not reorder within a queue without an explicit rule |
| RT-SHUT-01 | Shutdown while action callback is in flight | Block executor callback on a barrier; initiate stop; release callback; make feedback admission reject after stop | No silently discarded secondary feedback result; action ends as durable feedback or explicit pending-recovery/unknown disposition with stable IDs |
| RT-SHUT-02 | Submission after admission close | Start stop, then submit new input and feedback | Both reject according to documented admission policy; reason/counters are observable; no accepted item disappears |
| RT-RESULT-01 | Result queue saturation | Set small capacity, stop consumer, publish more results than capacity | Every lost/evicted result is individually identifiable and recoverable/queryable; aggregate counter reconciles with ledger |
| RT-RESTART-01 | Crash after external effect before feedback acknowledgement | Fake executor records side effect, then simulate process loss before feedback/result durability | Restart discovers prior effect through same idempotency key; does not repeat side effect; records effect/feedback once |
| RT-RESTART-02 | Crash after dispatch before external effect is known | Simulate lost executor acknowledgement and unavailable status lookup | Work remains `EFFECT_UNKNOWN`; no fabricated success/failure; no blind retry |
| RT-IDEMP-01 | Same logical action retried | Replay same work/action with same key but new attempt ID | Executor deduplicates or reconciliation proves one effect; identities remain linked |
| RT-IDEMP-02 | Distinct logical action with same payload | Submit a new logical action with identical payload | New action identity does not collide with previous action's idempotency identity |
| RT-RECOVER-01 | Full accounting across restart | Mix accepted, rejected, dispatched, confirmed, unknown, feedback-persisted and result-dropped work | Counts and per-item records reconcile; no double-counted goal progress or learning; unknown outcomes remain excluded from outcome learning |
| RT-REPLAY-01 | Journal replay order and duplicate records | Replay repeated/out-of-order lifecycle records | Replay is idempotent; invalid transitions are surfaced; later records do not fabricate missing acknowledgements |

## 9. Evidence and acceptance requirements

A runtime acceptance package must contain:

- exact donor/integration commit SHA and exact source/test blob SHAs;
- test target registration **and** executed CTest output for every RT-* case;
- deterministic test seed/configuration and fault-injection setup;
- assertions demonstrating stable identity propagation end to end;
- before/after ledger snapshots for restart and result-loss tests;
- executor fake contract, including what counts as an authoritative effect acknowledgement;
- test results for normal, failure and restart paths;
- explicit residual limitations for real external systems that do not support idempotency/status lookup.

Test registration, compilation, a test name, a passing unrelated suite, or a source-level assertion does not satisfy execution evidence.

## 10. Current donor source facts versus unproven incidents

Source-confirmed at PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`:
- feedback is selected ahead of input whenever feedback is non-empty;
- no bounded feedback quota/aging rule is visible in the inspected worker loop;
- stop sets the stopping state;
- feedback submission rejects during stopping;
- action execution discards the secondary feedback submission result;
- result queue overflow drops the oldest result and increments an aggregate counter.

Not demonstrated by the source inspection:
- that production input starvation has occurred;
- that any real external action was duplicated;
- that shutdown has caused a real feedback loss incident;
- that result overflow has occurred under production load;
- that a specific learning update was lost or double-counted.

These are conditional risks and acceptance gaps, not incident reports.

## 11. Authorization boundary

This document is a documentation-level contract only. It does not authorize:
- modifying donor or main production runtime code;
- adding or changing runtime tests;
- changing scheduler policy or persistence semantics;
- selecting PR #97 or another donor as implementation baseline;
- merging, deploying or clearing Gate A/Gate B.

Implementation and execution tests require the separate Project Director authorization applicable after Phase 2 and gate decisions. Until then, this contract is a review and planning artifact.

**Prepared by:** Main Builder role.  
**Independent review:** Required before any implementation specification is accepted.  
**Project Director decision:** Required before runtime implementation or donor acceptance.
