# Gate A — Candidate Defect Disposition and Future Acceptance Criteria

**Date:** 2026-11-04  
**Candidate source baseline:** PR #156 code-bearing integration, with exact blobs below  
**Status:** Both findings confirmed by supplied independent technical review; unfixed; runtime work unauthorized

## D1 — Learned-strategy lookup may use the wrong goal context

**Disposition:** CONFIRMED DEFECT — NOT FIXED

**Affected code and evidence**
- Candidate `core/cpp/src/brain_restored_api.cpp`, blob `00d69ab2eb3811d453a643ef18dc69741109cbc8`.
- Candidate `core/cpp/src/goals.cpp`, blob `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`.
- Candidate `core/cpp/src/intent.cpp`, blob `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032`.

**Failure mechanism**
- `GoalModel::eligible()` includes pending and active goals and sorts by priority/creation cycle.
- `IntentModel::select()` ignores pending goals and selects among active goals using its own scoring.
- `Brain::choose()` and `Brain::choose_with_affect()` key learned-strategy retrieval using `eligible.front().id`.
- The first eligible goal is therefore not guaranteed to be the selected active intent. A pending goal's strategy can be applied in place of the selected active goal's strategy.

**Required remediation invariant**
The strategy context must be derived from the identity of the intent actually selected for the current decision. If no active intent is selected, use a documented explicit fallback that cannot accidentally inherit an unrelated pending goal's context.

**Future regression acceptance criteria (after separate runtime authorization)**
1. Construct a high-priority pending goal and a different active goal selected by IntentModel; prove both choose paths use the selected active goal's context.
2. Prove the pending goal's strategy is not retrieved/applied merely because it sorts first in eligible goals.
3. Cover no-selected-intent behavior and verify the explicit fallback.
4. Cover multiple active goals where eligibility ordering and intent scoring differ.
5. Verify strategy context remains correct with affective modulation enabled.
6. Verify no unrelated goal's strategy state is mutated by retrieval.

## D2 — Non-finite goal input can be journaled before model rejection

**Disposition:** CONFIRMED INPUT/PERSISTENCE INTEGRITY DEFECT — NOT FIXED

**Affected code and evidence**
- Candidate `core/cpp/src/brain_restored_api.cpp`, blob `00d69ab2eb3811d453a643ef18dc69741109cbc8`.
- Candidate `core/cpp/src/goals.cpp`, blob `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`.

**Failure mechanism**
`Brain::create_goal()` clamps priority/progress, creates/appends the event, then delegates to `GoalModel::create()`, which rejects non-finite values. NaN can survive `std::clamp()` and reach the journal before rejection. Positive and negative infinity are clamped by the inspected code; nevertheless, accepting a non-finite input at the public boundary is an inconsistent contract and must be rejected explicitly.

**Required remediation invariant**
Every numeric goal input that is required to be finite must be checked with a finiteness predicate before event construction, journal append, replay, or any state mutation. Rejection must be side-effect free.

**Future regression acceptance criteria (after separate runtime authorization)**
1. Test NaN for priority and progress.
2. Test positive infinity for priority and progress.
3. Test negative infinity for priority and progress.
4. For every rejected input, assert no goal is created or changed.
5. Assert the journal length/content is unchanged and no replay-visible event is produced.
6. Assert rejection is consistent across fresh and restored/replayed Brain instances.

## Related unresolved ordering risks — not yet confirmed defects

- `assimilate_goal_outcome`: progress may be persisted before a separate completion event; second append failure could leave progress committed while returning failure.
- `observe_evolution_canary` / `rollback_evolution`: durable evidence and controller rollback may be separated by a failure boundary; restart/replay/idempotency needs proof.

These require failure-injection/replay evidence under later authorization. Do not promote them to confirmed defects without evidence.

## Authority and baseline treatment

- No runtime correction, test addition, build, or execution was performed.
- These findings do not by themselves prove PR #156 must be rejected; they are concrete remediation obligations whose severity and fixability inform the candidate decision.
- Do not silently drop them into general technical debt.
- If PR #156 is selected later, remediation must be an explicit prerequisite in the implementation plan and verified before the affected capability is accepted.

**Disposition:** D1 and D2 remain confirmed and unfixed. Gate A remains NOT CLEARED.
