# Phase 2 — Donor Runtime Reliability Contract and Verification Matrix

**Date:** 2026-11-06  
**Target source:** PR #97 donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Relevant source:** `core/cpp/src/cognitive_runtime.cpp`, `core/cpp/include/jarvis/core/cognitive_runtime.hpp`, `core/cpp/tests/cognitive_runtime_suite.cpp`  
**Status:** Contract clarification for review. No runtime implementation or tests changed or executed.

## 1. Purpose and boundary

This document makes the remaining IR-03 acceptance criteria executable at the contract level. It addresses fairness, shutdown during in-flight action execution, bounded result loss, restart/retry, correlation identity and idempotency.

The donor is not approved or merged. This document does not authorize production implementation, donor port, baseline selection, merge or deployment. Source observations are inherited from the second independent review and remain pinned to the donor HEAD above. The tests below are required future verification, not executed evidence.

## 2. Identity model: do not overload one identifier

A single identifier cannot safely represent accepted work, an execution attempt, an external side effect, and a published result. The following logical identities are required; concrete types and serialization remain undecided.

| Identity | Created when | Stability / purpose |
|---|---|---|
| `operation_id` | A logical input/request is first accepted by the runtime | Stable across queueing, processing, restart, result publication and retries of the same logical request |
| `action_id` | A specific logical side effect is derived from an operation | Stable across retries of that same intended side effect; distinct for different side effects within one operation |
| `attempt_id` | Each actual execution attempt begins | New for every attempt; allows retries to be distinguished without changing the logical action identity |
| `feedback_id` | Action-derived feedback is created | Stable for the same feedback fact across retry/recovery; deduplicated by its durable identity |
| `result_id` | A result record is created | Stable for the same logical result across redelivery; distinct from the operation and attempt identifiers |

All records must carry the identifiers relevant to their lifecycle. At minimum, `operation_id` must flow through accepted input, cycle execution, each derived action, feedback submission, published result, dropped-result/loss record, durable ledger and recovery report. The corresponding `action_id` and `attempt_id` must be present where side effects and retries are represented.

Identifiers must not be regenerated during reconstruction in a way that makes one logical operation appear to be new work.

## 3. Idempotency contract

### 3.1 Key scope

The idempotency key is scoped to a logical external side effect, not merely a worker invocation, process, queue item, session or attempt.

The key must be derived from or durably associated with:
- the stable `operation_id`;
- the stable `action_id`;
- the identity of the intended external effect and its target/resource scope.

A retry of the same logical action must reuse the same key. A genuinely new action must receive a different key even if its payload happens to be byte-identical. The `attempt_id` must never be used as the idempotency key because it changes on retry.

### 3.2 Retention

The idempotency record and its outcome/reconciliation state must survive process restart and remain available for at least the full period in which the same logical action can be retried, replayed or recovered. The safe default is durable retention for the lifetime of the corresponding operation/action record, including a tombstone after completion. Expiry is permitted only when the system can prove that no retry, replay, delayed feedback or recovery path can reissue the effect.

A session boundary or process restart is not a valid expiry boundary.

### 3.3 External side-effect boundary

Exactly-once external effects cannot be claimed solely because the local runtime stores an idempotency key. The external executor/target must support the same idempotency key, a transactional commit protocol, or an independently queryable reconciliation mechanism.

If the process crashes after the external effect may have happened but before durable acknowledgement, the state is **UNKNOWN / RECONCILIATION_REQUIRED**. It must not be converted to success or failure by assumption, and the action must not be blindly re-executed. Recovery must first query/reconcile the target or use target-side deduplication with the same stable key.

If the target cannot deduplicate or report whether the effect occurred, the system must preserve the ambiguity and require an explicit recovery policy; it cannot honestly promise at-most-once or exactly-once behavior.

## 4. Required lifecycle and state distinctions

The runtime contract must distinguish:
- accepted by runtime;
- queued;
- selected for execution;
- execution started;
- action requested;
- authorization granted/denied;
- external effect attempted;
- effect outcome confirmed;
- effect outcome unknown;
- feedback durably accepted;
- feedback rejected/pending recovery;
- result published;
- result delivered/acknowledged;
- result dropped/unobserved;
- operation reconciled.

Queue acceptance is not execution. Execution completion is not verified external consequence. Result publication is not caller receipt. Feedback rejection is not proof that the action failed. An unknown side effect must remain unknown until reconciled.

## 5. Fairness contract

The feedback-first donor scheduler has no source-visible maximum feedback burst or aging guarantee. A sustained feedback producer can therefore prevent eligible input selection.

The contract must define a finite configured bound `B >= 1`: after at most `B` consecutive feedback dispatches while at least one eligible input remains queued, the scheduler must select an eligible input before dispatching another feedback item. If no input is eligible, the scheduler may continue servicing feedback. The bound is a dispatch-count guarantee, not a wall-clock latency promise.

The selected policy must also define what happens when an input becomes eligible concurrently with the Bth feedback dispatch, how cancellation/invalid work is treated, and how fairness is preserved across worker restart. A test must assert the deterministic dispatch-count bound.

The value of `B` is an implementation/configuration decision and is intentionally not selected here.

## 6. Shutdown while an action is in flight

Once an action has begun, shutdown must not silently erase its secondary feedback obligation.

Required behavior:
1. An in-flight action retains its `operation_id`, `action_id` and `attempt_id`.
2. The action's external effect is recorded as confirmed, failed or unknown independently of feedback acceptance.
3. Action-derived feedback is durably accepted before shutdown completes, or the action/result record is durably marked `FEEDBACK_PENDING_RECOVERY` / `FEEDBACK_REJECTED` with its stable `feedback_id`.
4. The boolean/result of feedback submission must be handled, never discarded.
5. Restart discovers pending feedback by stable identity and retries it without double-counting learning or goal progress.
6. Shutdown completion must state whether all in-flight actions and feedback obligations are drained, durably pending, or unresolved.

A completed action with silently discarded feedback is not an acceptable terminal state.

## 7. Result saturation and loss reconciliation

The current donor's drop-oldest queue policy exposes an aggregate dropped-results counter, which does not identify which caller's completed result was lost.

Required behavior:
- every result has a stable `result_id` and parent `operation_id`;
- every drop creates a durable/observable loss record identifying the dropped result and operation;
- the caller-facing status distinguishes `COMPLETED_RESULT_DELIVERED`, `COMPLETED_RESULT_UNOBSERVED`, `NOT_EXECUTED` and `EXECUTION_UNKNOWN`;
- a dropped result must not be reclassified as an unexecuted operation;
- result redelivery must be idempotent and must not duplicate cognitive learning, goal progress or action execution;
- queue metrics must reconcile to identifiable records rather than being the only evidence of loss.

## 8. Required verification matrix

These tests are not present as executed evidence in this document. They must be added to the relevant donor/runtime test boundary under a separately authorized implementation/test task, then run at the exact tested commit.

| ID | Scenario | Deterministic setup | Required assertions |
|---|---|---|---|
| RT-01 | Feedback fairness | Keep feedback continuously available while a valid input remains queued; instrument dispatch order | An eligible input is selected after no more than configured `B` consecutive feedback dispatches; assert count, not wall-clock time |
| RT-02 | In-flight action shutdown | Executor blocks on a barrier after side-effect boundary; initiate stop; release callback | Action outcome is confirmed/failed/unknown; feedback is durably accepted or explicitly pending/rejected with stable IDs; no discarded submission result |
| RT-03 | Result queue saturation | Small result capacity; stop polling; publish more completed results than capacity | Every lost result is identifiable; caller can distinguish completed-but-unobserved from not executed; counters reconcile with loss records |
| RT-04 | Crash after possible side effect | Simulate target effect then crash before local acknowledgement; reconstruct and retry same logical action | Same stable idempotency key is reused; outcome remains unknown until target reconciliation; no blind duplicate side effect |
| RT-05 | Restart with pending feedback | Persist action and feedback obligation; stop/crash before processing feedback; restart | Same feedback identity is resumed once; accepted/processed accounting reconciles; learning/goal progress is not double-counted |
| RT-06 | Result redelivery | Publish result, simulate lost acknowledgement, retry delivery | Stable result identity; duplicate delivery is recognized; downstream state changes once |
| RT-07 | Recovery ledger consistency | Mix accepted, rejected, processed, failed, unknown and dropped records; restart | All counts reconcile by identity and state; no unknown item is silently promoted to success/failure |
| RT-08 | Fairness plus shutdown interaction | Keep feedback queue non-empty and initiate stop while input is waiting | Shutdown policy is deterministic; queued work is drained or explicitly retained/rejected with identity; no hidden starvation/loss |

## 9. Evidence required before donor reliance

For each test:
- record exact source commit and test binary/configuration;
- show the test name and actual execution result;
- preserve relevant logs/traces with operation/action/attempt/feedback/result identities;
- demonstrate restart/reconstruction using persisted state, not an in-memory fixture only;
- record failures and reruns; do not report a test as passed if it was skipped, not built or only registered;
- independently review the contract and evidence.

A source inspection, test registration, mock-only test or aggregate metric is not sufficient to claim that the donor runtime meets this contract.

## 10. Explicit non-claims and authorization

- No fairness policy or numeric bound has been implemented or selected.
- No runtime identifiers, idempotency key, durable ledger or result-loss record have been implemented.
- No runtime tests were added or executed.
- No build, CTest, sanitizer, benchmark, concurrency stress or failure-injection run was performed.
- No external side-effect guarantee is claimed.
- PR #97 remains donor-only, unapproved and unmerged.
- Gate A remains NOT CLEARED; Gate B remains unassessed/not cleared.
- This contract does not authorize production implementation, donor port, merge, deployment or baseline selection.

**Owner:** Main Builder prepares the contract and implementation/test proposal.  
**Independent Reviewer:** Must challenge the contract and later inspect executed evidence.  
**Project Director:** Retains acceptance and authorization authority.

**End of runtime contract.**
