# Phase 2 — Donor Runtime Fairness, Correlation, Idempotency and Recovery Test Contract

**Date:** 2026-11-06  
**Donor baseline:** PR #97 exact HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25  
**Runtime source:** core/cpp/src/cognitive_runtime.cpp, blob cf00acb6abd52308343f3a0e7016e6173b945603  
**Runtime interface:** core/cpp/include/jarvis/core/cognitive_runtime.hpp, blob e5a3c853add8b5fcb9b8c04c9b25f20179b5b629  
**Existing test source:** core/cpp/tests/cognitive_runtime_suite.cpp at the same donor HEAD  
**Status:** Contract/test preparation only. No runtime/test source changed and no test was executed.

## 1. Purpose and authority boundary

This contract makes the remaining IR-03 criteria precise enough to implement and independently verify. It defines end-to-end correlation identity, idempotency scope/retention, scheduler fairness, in-flight shutdown, result saturation, restart/retry and recovery accounting.

PR #97 remains an unmerged, unapproved donor. The accepted mechanism specification does not authorize runtime implementation or test execution, and Phase 2 has not cleared its implementation gates. This document therefore does not authorize modifying donor runtime code or claim test results.

## 2. Source-derived risk statement

At the pinned donor source, the Phase 2 review records:
- feedback is selected whenever the feedback queue is non-empty; no finite feedback burst quota, aging rule or cross-queue service bound is visible in the inspected worker loop;
- stop sets the stopping state, after which submit_feedback rejects new feedback;
- execute_actions discards the boolean result of secondary submit_feedback using (void);
- a full result queue drops the oldest result and increments an aggregate dropped_results metric;
- the inspected interface does not establish per-result acknowledgement/reconciliation or durable idempotency across an unknown external side effect.

These are source-visible control-flow properties and conditional risks, not claims that a production incident occurred.

## 3. Required identity model

Concrete type names, serialization and API shape remain implementation decisions. The following semantic identities are required.

### 3.1 Logical request correlation identity

Assign a correlation identity when a logical input/request is accepted. It must:
- identify that request through queueing, execution, result publication, dropped-result accounting, feedback generation, restart and recovery;
- remain unchanged for retries of the same logical request;
- be queryable by callers/operators for reconciliation;
- be persisted before claiming durable acceptance;
- not be reused for a distinct logical request within the documented namespace and retention period.

A retry keeps its original correlation identity. A separately submitted request receives a new identity even when its payload is byte-for-byte identical.

### 3.2 Attempt identity

Each execution attempt has a distinct attempt identity linked to the logical request. It distinguishes initial execution, retries, interrupted/unknown attempts and recovery attempts. It must not replace the stable logical request identity.

### 3.3 Action identity and idempotency key

Each externally effectful action has a stable action identity and idempotency key identifying the logical side-effect intent, not one execution attempt. The key remains the same across retries, including post-restart retries.

The key namespace/scope must prevent collisions across independently valid operations. It should include the authorized principal/tenant boundary, target capability/provider and logical operation identity as applicable; exact encoding is an implementation decision.

Do not derive the key from payload equality alone: identical payloads may represent two legitimate independent actions. Conversely, retrying one action must retain its original key even if transport metadata changes.

If one logical request contains multiple independent side effects, each side effect gets its own stable action identity/key while preserving the parent correlation identity.

### 3.4 Retention and expiry

The idempotency record must survive at least the maximum permitted retry, queue recovery, crash recovery, delayed-result and reconciliation window.

If those windows are not bounded, the system must not silently expire a key while a prior effect could still be replayed. A finite retention policy is acceptable only if request/action expiry and recovery rules make post-expiry replay impossible or force explicit manual reconciliation.

A tombstone or equivalent durable record may be required after detailed result data is compacted, preventing a late retry from repeating an already-performed side effect.

Provider-side idempotency retention must be considered. The runtime must document and test the intersection of its durable ledger and provider guarantees. Do not claim exactly-once external execution unless the external system and transaction boundary actually provide it.

## 4. Required lifecycle and caller-visible outcomes

| State | Meaning | Required recovery behavior |
|---|---|---|
| Accepted | Runtime accepted the logical request | Correlation identity is fixed |
| Queued | Work awaits dispatch | Work remains discoverable and attributable |
| Executing | An attempt is in progress | Interruption is not reported as completion |
| Effect unknown | Side effect may have occurred; acknowledgement/verification is missing | Do not blindly repeat a non-idempotent action |
| Effect verified | External consequence independently verified | Record evidence and attribution |
| Feedback pending | Action-derived evidence exists but is not durably accepted | Expose pending/recovery status |
| Feedback committed | Feedback was durably accepted for processing | Reprocessing is idempotent |
| Result published | Caller can retrieve the result | Correlation remains queryable |
| Result dropped | Completed result was lost from bounded delivery queue | Durable reconciliation record remains queryable |
| Failed before effect | Attempt failed before external effect could occur | Retry may be allowed under policy |
| Rejected | Request/feedback was not accepted | Caller receives explicit rejection reason |

The public contract must distinguish never executed, failed before effect, effect verified, effect unknown, completed-but-undelivered, and feedback pending/rejected. An aggregate counter alone is insufficient.

## 5. Fairness contract

The scheduler must provide a documented finite service bound for eligible input while feedback remains continuously available. The implementation may use quota, aging, weighted scheduling or another justified policy; this document does not select the algorithm.

Define a finite maximum K of consecutive feedback dispatches permitted while eligible input waits. Once K is reached, eligible input must be selected before another feedback item. Also define and test a reciprocal service guarantee for feedback under sustained input, or document and justify a different priority contract.

Assert dispatch counts and selected-work order. Do not use arbitrary wall-clock thresholds as the primary fairness assertion.

## 6. Deterministic test matrix

| ID | Setup | Required assertion |
|---|---|---|
| RT-01 | Keep a feedback producer continuously active while valid input remains queued; observe dispatches deterministically. | Eligible input is dispatched after at most K consecutive feedback dispatches; K is finite/documented. Verify reciprocal feedback service under sustained input. |
| RT-02 | Block an executor callback on a test barrier; begin stop; release callback so it attempts secondary feedback submission. | Action result/caller receives durable feedback acceptance or explicit feedback-rejected/pending-recovery status with original correlation/action identity. No ignored false return or false claim that feedback committed. |
| RT-03 | Use a small result capacity, stop polling, and publish more completed results than capacity. | Every dropped result is attributable by correlation identity and result sequence. Caller distinguishes completed-but-undelivered from never-executed; aggregate metrics reconcile with per-result records. |
| RT-04 | Crash/reconstruct after an external side effect but before feedback/result acknowledgement; retry the same logical request. | Correlation/action identity/idempotency key remain stable. No duplicate side effect where provider guarantees it; otherwise effect remains unknown pending reconciliation. |
| RT-05 | Submit same logical request more than once, including concurrent duplicate delivery and post-restart retry. | Duplicate delivery is recognized as same logical request and does not create a second logical action or double-count learning/goal progress. A distinct request with identical payload remains distinct. |
| RT-06 | Reject action-derived feedback during shutdown, restart and recover. | Accepted/rejected/pending/processed/failed/unknown work reconciles by identity. Rejected feedback is not counted processed; learning is not applied twice. |
| RT-07 | Force result overflow and restart before caller reconciliation. | Durable dropped-result records survive restart, or explicit unrecoverable-loss state is exposed. A result cannot disappear from both queue and reconciliation record. |
| RT-08 | Simulate provider timeout after the provider may have performed the side effect. | Runtime marks effect unknown, reconciles with same idempotency key where supported, and does not infer success/failure from timeout alone. |

## 7. Harness and evidence requirements

Use deterministic barriers, bounded queues, a controllable fake executor/provider, explicit crash/reconstruction points and a durable test ledger. Avoid sleeps as synchronization.

For each test retain exact source commit/blob identities, build target and CTest registration, command/environment, output/exit status, observed correlation/action identities, durable ledger before/after restart, provider-side effect count, and test level (unit/component/runtime integration/host integration).

A test file or registered CTest name is not evidence of execution. A fake-provider test does not prove every external provider honors the same idempotency semantics. A donor-only test does not prove main contains the donor runtime.

## 8. Acceptance criteria

IR-03 may be considered runtime-verified only when:
1. identity propagation is implemented end to end and survives restart/recovery;
2. idempotency scope and retention are explicit and tested at the external-effect boundary;
3. RT-01 through RT-08 are implemented, or an excluded scenario has an evidence-backed rationale accepted by the proper authority;
4. the exact runtime commit builds and tests are registered and actually executed;
5. result-loss and unknown-effect outcomes are caller-visible and reconcilable;
6. duplicate delivery/replay cannot double-count learning or goal progress;
7. an Independent Tester reproduces the scenarios at the relevant runtime boundary.

Documentation precision does not satisfy runtime verification.

## 9. Phase 1 Continuity and Impact

This contract inherits Phase 1's distinction between main and unmerged donor implementation; single authoritative cognitive-state ownership; separation of intention, attempt, execution result, verified consequence and unknown effect; and persistence/replay, partial-commit, idempotency, compensation and recovery obligations. It preserves PR #97 as donor evidence and does not promote it to an implementation baseline.

## 10. Current status and authorization

- Correlation identity/idempotency semantics: specified; not implemented or runtime-verified.
- Fairness/shutdown/result-saturation tests: specified; not executed.
- PR #97: unapproved, unmerged donor.
- Runtime implementation/test execution: not authorized by this document.
- Phase 2: IN PROGRESS.
- Gate A: NOT CLEARED.
- Gate B: not assessed or cleared.
- Independent review and Project Director disposition: pending.

**Conclusion:** This contract closes the documentation-level precision gap identified by IR-03. It does not close runtime verification or authorize donor reliance.
