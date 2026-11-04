# Gate A — Final Baseline Applicability Recommendation

**Date:** 2026-11-04  
**Audit:** Extended, time-boxed static Gate A review  
**Governing specification:** Accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Current main observed:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Candidate PR:** #156  
**Candidate code-bearing parent:** `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Planning PR:** #175, branch `plan/brain-implementation-roadmap-20261103`

## 1. Final builder recommendation

**DO NOT adopt PR #156 as a wholesale implementation baseline.**

**USE accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` as the integration starting point, and treat PR #156's code-bearing tree as a source of reusable mechanisms to be selectively ported, corrected and validated.**

This is the strongest repository strategy supported by the inspected evidence. It preserves the accepted Brain specification and the current-main history while retaining the substantial implementation work in PR #156 without inheriting its branch history and known defects wholesale.

This is a final Builder-side technical recommendation. It is **not** an independent review submission, a Project Director approval, or authorization to modify runtime code.

## 2. Why this is the correct starting point

The exact repository comparisons establish:

| Comparison | Result | Meaning |
|---|---|---|
| Current `main` → accepted PR #174 HEAD | Accepted specification is 12 commits ahead; the net changes are five documentation files | The accepted specification is the authoritative planning/integration point and does not replace runtime code with a competing implementation |
| Current `main` ↔ candidate code-bearing parent | Candidate is 1,428 commits ahead and current `main` is nine commits ahead; 165 paths differ in the net tree comparison | These are substantially divergent histories and trees, not a clean linear upgrade |
| Accepted PR #174 HEAD ↔ candidate code-bearing parent | Candidate is 1,428 commits ahead and is 21 commits behind the accepted specification point | The candidate predates the accepted design authority and does not contain the accepted specification history |

The nine commits present on current `main` after the shared comparison point contribute five validation workflows and a Brain API restoration change. The five workflows cover:
- the four-hour DLT-002 trial;
- the 35-gate learning-mechanisms probe and changing-environment trial;
- integrated Brain feedback and persistence;
- independent multi-seed adversarial learning;
- memory persistence with an explicit source-ref control.

These controls are part of the repository's validation infrastructure and must be preserved or replaced with demonstrably equivalent workflows. The accepted PR #174 HEAD is 12 commits ahead of current `main` and adds the accepted architecture/specification documents; it is therefore the appropriate implementation branch starting point.

## 3. What is reusable from PR #156

The candidate is not worthless and should not be discarded. Static source inspection establishes substantial reusable implementation work in these areas:

| Area | Candidate value | Required treatment |
|---|---|---|
| Experience intake and event journal | Sequenced experience, provenance fields, durable append and replay substrate | Reuse selectively; strengthen acquisition trust, immutable provenance and event-time semantics |
| Representation and perception | Structured representations and perception-to-memory integration | Reuse; improve alternative interpretations, semantic grounding and evidence lineage |
| Memory | Durable episodic records, ranked recall, action-specific retrieval and persistence tests | Reuse; improve contextual/semantic retrieval and ensure relevant memories can become reasoning premises |
| Belief and world state | Belief, knowledge and world-model state owners; source feedback and conflict handling | Reuse selectively; complete evidence history, temporal scope and dependency invalidation |
| Association, causal models and prediction | Adaptive association/causal links, prediction generation and feedback resolution | Reuse as bounded mechanisms; do not claim general causal discovery without confounder, intervention and context controls |
| Attention | Adaptive signal scoring and reinforcement/suppression | Reuse; build actual multi-context scheduling, interruption/resumption and starvation controls |
| Affective appraisal | Stateful affect and adaptive appraisal/learning | Reuse; verify contextual modulation and evidence lineage across other mechanisms; do not encode emotion-to-action mappings |
| Goals, intent, planning and decisions | Goal lifecycle, active-intent selection, planning and affective decision modulation | Reuse; add experience-derived candidate-goal formation and repair the goal-context defect below |
| Developmental learning | Strategy retrieval, related strategies, feature estimates and bounded feature adaptation | Reuse selectively; distinguish demonstrated additive transfer from unproven general compositional reasoning |
| Metacognition | Reflection and calibration summaries | Reuse as monitoring substrate; add a verified diagnose/correct/re-evaluate control loop |
| Integrated coordination | Cognitive cycle/runtime, action consequence feedback and replay integration | Reuse; close owner dependency, freshness, invalidation and recovery contracts |
| Reasoning | A real inference prototype with one downstream path into forward simulation/prediction | Reuse as a prototype only; add memory premises, premise/assumption provenance, alternatives, counterexamples and dependency lineage |
| Developmental environment and trials | Training environment and DLT-001 through DLT-004 trial source | Reuse as test infrastructure where it measures accepted requirements; expand coverage beyond current narrow transfer evidence |
| Evolution and guarded adaptation | Experiment evaluation, canary, adoption journal, rollback and safety paths | Reuse selectively; resolve failure ordering and replay/idempotency before trusting autonomous parameter changes |

The candidate therefore supplies a meaningful mechanism library. It does not supply a specification-complete Brain.

## 4. Findings that prevent wholesale adoption

### 4.1 Confirmed candidate defects

**D1 — Learned strategy can be retrieved under the wrong goal.**

The candidate's `Brain::choose()` and `choose_with_affect()` derive the developmental strategy context from `eligible.front().id`. Goal eligibility includes pending and active goals, while intent selection deliberately ignores pending goals and chooses an active intent using a different score. The first eligible goal can therefore differ from the selected active intent. Strategy retrieval can be associated with the wrong goal.

Required correction: derive the strategy context from the selected intent's identity, with an explicit safe fallback when no intent is selected. Add the multi-goal regression cases already specified in review artifact 11.

**D2 — Invalid non-finite goal inputs can reach the journal before model rejection.**

Candidate `Brain::create_goal()` clamps priority/progress and appends a `goal_create` event before the GoalModel rejects non-finite values. NaN can survive clamping and be journaled. Positive and negative infinity are clamped in the inspected path, but must still be rejected at the public boundary.

Required correction: reject every required non-finite numeric input before event construction, journal append, replay or mutation. Rejection must leave the journal and Brain state unchanged.

### 4.2 Unresolved failure-ordering risks

These are not promoted to confirmed defects without failure-injection evidence:

- `assimilate_goal_outcome()` can persist progress and then fail to persist a separate completion event. The contract must define and recover this partial transition.
- Evolution canary evidence, controller rollback and adoption-journal/history updates cross multiple persistence/state boundaries. Failure and restart/replay behavior must be proven idempotent and internally consistent.

### 4.3 Specification capability gaps

The existing Gate B audit maps all BM-01 through BM-12 owners, but capability acceptance is not passed. The most consequential gaps remain:

1. Retrieved memories are not yet demonstrated as provenance-bearing reasoning premises that materially change an inference.
2. Reasoning lacks complete premise/assumption/provenance/alternative/counterexample/dependency lineage.
3. Causal links and prediction feedback do not yet establish general causal discovery or full prediction contracts.
4. Attention/workspace presence does not establish reliable multi-context control and invalidation.
5. Goal lifecycle support does not establish experience-acquired candidate-goal formation.
6. Reflection does not yet establish a complete corrective control loop.
7. Developmental learning evidence is bounded; DLT-004 additive feature composition does not establish parity/XOR transfer or broad compositional reasoning.
8. The 73/73 CTest result is historical evidence for its exact candidate tree, not proof that all 34 accepted PR #174 foundational scenarios pass.

These are implementation and capability gaps, not reasons to throw away the reusable foundations.

## 5. API and workflow compatibility

- All 64 unique Brain API method names present in the current-main restoration were found in the candidate; the candidate contains seven additional unique APIs.
- The 24 common API body differences have been individually classified in the semantic addendum. Most candidate differences provide stronger validation, event-first transitions, provenance or learned behavior and should not be replaced wholesale with the older current-main bodies.
- `register_evolution_parameter()` changes from `void` to `bool`. Direct current-main call expressions inspected ignore the return value, but complete typed-reference, downstream and ABI compatibility has not been established.
- Candidate-only feedback, restricted legacy-import and evolution-evaluation APIs have candidate test-source references. Three developmental strategy accessor APIs had no references in seven targeted test files; repository-wide reachability remains unproven.
- The five current-main validation workflows are not all preserved in the candidate. One has an exact match, one needs source-ref/reproducibility adaptation, and three are absent or only partially represented. All must be retained or explicitly replaced before the new implementation plan treats validation continuity as complete.

## 6. Provenance and history closure

The prior reconciliation enumerated 1,416 unique inherited commit SHAs and the 165-path net tree delta. The 14 overlap paths now have direct blob-level comparison evidence between the historical comparison point and the candidate. The 24 API body differences and the two divergent integration paths were also statically classified.

The exhaustive per-commit origin → path → hunk ledger across all 1,416 inherited commits remains incomplete. That limitation is recorded rather than hidden. It does not change the baseline recommendation: the candidate is not to be adopted wholesale, and future integration is to occur as small, reviewable ports from exact source commits onto the accepted specification base. Each port will carry its own source SHA, path/hunk attribution, specification obligations, defect treatment and acceptance evidence. This risk-based method avoids spending further time building a historical ledger that cannot make a whole-branch adoption safe.

## 7. Required implementation approach after authorization

1. Create the implementation branch from accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.
2. Treat PR #156 code-bearing parent `15d49e5fdeb5723c475922ab78fb92f97c4b3b84` as the donor reference, not as a merge/cherry-pick target.
3. Port candidate mechanisms in dependency-sized work packages, beginning with experience/provenance, representation, memory and belief foundations; then prediction/causal, attention/affect, goals/intent/decision, action/consequence, learning/evolution, metacognition and reasoning integration.
4. Preserve the five current-main validation workflows and their tested-ref, seed, trial, artifact and failure semantics.
5. Make D1 and D2 corrections explicit prerequisites. Add failure-injection/replay tests for the unresolved multi-event and evolution ordering boundaries.
6. Map every port to the accepted BM-01–BM-12 contracts and relevant one of the 34 foundational acceptance scenarios.
7. Accept a mechanism only when an integrated, experience-dependent change persists and measurably affects later prediction, belief, decision or behavior. Do not accept source presence, registration, or isolated unit tests as learning capability.

No whole-branch merge, wholesale cherry-pick, rebase, history rewrite or runtime implementation is recommended.

## 8. Final Gate A disposition and authority boundary

**Builder technical result: PR #156 is REJECTED as a wholesale baseline and ACCEPTED AS A SELECTIVE SOURCE DONOR. The recommended integration base is accepted PR #174 HEAD.**

**Formal Gate A status: NOT FORMALLY CLEARED.** The repository currently has no submitted independent PR #175 review. This Builder-side audit cannot impersonate independent review or the Project Director's approval. The technical recommendation is now explicit; formal governance closure still requires an independent reviewer verdict and the Project Director's decision.

No runtime code, build configuration, tests or workflows were modified or executed during this audit. Existing CI results are not represented as newly run tests. This report does not authorize implementation; implementation still requires the Project Director's separate explicit authorization.

## 9. Evidence index

- Gate A closure assignment: `reviews/07_GATE_A_CLOSURE_ASSIGNMENT_2026-11-04.md`
- Risk-based provenance matrix and 14-path blob reconciliation: `reviews/08_GATE_A_RISK_BASED_PROVENANCE_MATRIX_2026-11-04.md`
- API compatibility and targeted caller evidence: `reviews/09_GATE_A_API_COMPATIBILITY_MATRIX_2026-11-04.md`
- Workflow continuity matrix: `reviews/10_GATE_A_WORKFLOW_CONTINUITY_MATRIX_2026-11-04.md`
- Confirmed defects and future acceptance criteria: `reviews/11_GATE_A_CANDIDATE_DEFECT_DISPOSITION_2026-11-04.md`
- Independent review packet: `reviews/12_GATE_A_INDEPENDENT_REVIEW_PACKET_2026-11-04.md`
- BM-01–BM-12 candidate traceability audit: `reviews/05_GATE_B_MECHANISM_TRACEABILITY_AUDIT_2026-11-03.md`
- Semantic/API/workflow addendum: `reviews/06_GATE_A_SEMANTIC_RECONCILIATION_ADDENDUM_2026-11-04.md`

**End of final Builder-side Gate A baseline recommendation.**
