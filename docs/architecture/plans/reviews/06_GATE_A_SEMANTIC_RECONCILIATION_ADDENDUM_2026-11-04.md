# Gate A — Semantic Reconciliation Addendum

**Date:** 2026-11-04  
**Planning PR:** #175  
**Candidate:** PR #156  
**Candidate code-bearing parent:** `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Candidate documentation HEAD:** `7fe212bbb0bd61116ea56581435e03b06c69b673`  
**Current main at inspected repository state:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Accepted specification:** PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`

## 1. Executive result

**Gate A remains NOT CLEARED. No implementation baseline is selected.**

This addendum completes a targeted static semantic review of:
- the 24 common Brain API function bodies previously identified as differing between the candidate and current-main API restoration;
- the two parser-unmatched API definitions;
- candidate-only API additions;
- the PR #151 → PR #155 and PR #150 → PR #156 divergent integration paths;
- all five workflow files introduced on current main after the shared ancestor.

The review found that most candidate API differences are deliberate and materially stronger event-first, validation, or provenance controls than the older current-main restoration. It also found two candidate-specific correctness risks requiring remediation or explicit acceptance before baseline selection.

This remains Builder-side review, not independent review. No runtime code, tests, builds or CI workflows were changed or executed.

## 2. Brain API restoration — exact semantic comparison

### 2.1 Reconciliation counts

Candidate `core/cpp/src/brain_restored_api.cpp` blob:
`00d69ab2eb3811d453a643ef18dc69741109cbc8`

Current-main blob:
`618deb6976eed951eae02b7f0da741e6d730bb0c`

The exact `Brain::` definition inventory contains 69 definition occurrences across 64 unique method names in current main, and 77 occurrences across 71 unique names in the candidate. Every one of the 64 current-main unique names is present in the candidate; the candidate has seven additional unique names. Overload-level caller/ABI compatibility remains a separate verification requirement.

Candidate `brain.hpp` blob:
`ca718aa4603bbdd0abc7de26ed296bcf8c6562fe`

Current-main `brain.hpp` blob:
`8268ef84e0b361ead536724ba7761904b30ee58f`

Manual comparison resolves the earlier two parser-unmatched definitions:
- `beliefs()`: signature and function body are byte-identical after line extraction. This is not an unresolved behavioral difference.
- `register_evolution_parameter()`: candidate declares/defines `bool`; current main declares/defines `void`. Candidate also rejects non-finite initial values and duplicate keys, journals/replays the event, and returns whether the parameter exists. This is a real API return-type change, not a missing definition. Ordinary call statements that ignore the return remain source-usable, but function-pointer, ABI and downstream contract compatibility still require caller/build verification.

The 24 common function bodies are individually classified below.

### 2.2 Twenty-four body differences

| Function | Candidate-side difference | Static disposition |
|---|---|---|
| `abandon_goal` | Checks existence and terminal status, journals then replays; main mutates GoalModel before journaling | Candidate event-first path is preferable; retain, with persistence-failure regression coverage |
| `activate_goal` | Checks goal state and completed prerequisites before journaling/replay | Candidate validation is consistent with GoalModel activation constraints; retain |
| `adopt_evolution` | Legacy proposal-only adoption fails closed; main can directly adopt a proposal | Candidate correctly prevents bypass of experiment evaluation/safety gate; retain |
| `adopt_evolution_experiment` | Validates adoption evidence and uses Brain-specific controller validation/adoption with compensation on journal failure | Candidate preserves stronger evidence and rollback boundary; retain, verify replay/compensation ordering |
| `append_goal_event` | Main includes a no-op timestamp self-assignment; candidate omits it | No meaningful behavior difference |
| `assimilate_goal_outcome` | Candidate rejects terminal goals and journals/replays progress before completion; main mutates progress before journaling | Candidate is safer against pre-persistence mutation; completion remains a multi-event transition and needs partial-failure/idempotency tests |
| `choose` | Candidate applies a learned strategy to action utility/value; main does not | Adds real learned-strategy use, but has a context-selection defect described in §3.1 |
| `choose_with_affect` | Same learned-strategy adjustment plus existing affective modulation | Same context-selection defect; retain only after correction and targeted multi-goal tests |
| `complete_goal` | Candidate checks goal state then journals/replays; main mutates GoalModel first | Candidate event-first sequence is preferable; retain |
| `create_goal` | Candidate checks duplicate ID and journals/replays; main journals before GoalModel creation | Candidate duplicate guard is useful, but non-finite priority/progress are not rejected before journaling; see §3.2 |
| `isolate` | Candidate checks component exists and journals/replays; main mutates resilience state before journaling | Candidate event-first path avoids unjournaled mutation; retain with failure-injection coverage |
| `isolate_capability` | Candidate checks capability exists and journals/replays; main mutates self-model first | Candidate event-first path is preferable; retain |
| `observe_capability` | Candidate journals and replays the observation; main directly updates self-model after append | Candidate replay-centered state transition is consistent with event ownership; retain |
| `observe_evolution_canary` | Candidate previews and validates observations, journals canary evidence, validates rollback and journals rollback; main directly updates canary controller and journals only rollback | Candidate provides substantially better evidence lineage; verify failed rollback and restart/replay behavior |
| `observe_evolution_fitness` | Candidate journals and replays; main directly updates evolution model after append | Candidate is more consistent with event-sourced state; retain |
| `predict` | Candidate rejects non-finite confidence/numeric values and incorporates learned adaptation into prediction calibration; main only clamps confidence | Candidate adds meaningful validation and adaptation; retain provisionally, require calibration and regression evidence |
| `recover` | Candidate validates finite health and component existence, then journals/replays; main mutates resilience state first and attempts compensating isolation on append failure | Candidate event-first path avoids pre-journal mutation; verify replay semantics and failed persistence |
| `reflect` | Candidate supplies affective calibration error/rate/observation data to reflection; main omits it | Candidate has richer metacognitive evidence; retain provisionally and verify calibration ownership/meaning |
| `register_evolution_parameter` | Candidate validates finite input and duplicate registration, returns bool and replays event; main returns void and directly registers | Candidate is safer; return-type/API contract change needs callsite and compatibility review |
| `resolve_prediction` | Candidate delegates to the explicit feedback resolver; main duplicates resolution/journaling logic | Candidate centralizes feedback validation; boolean result still means correctly resolved, not merely processed, consistent with main's error-based bool |
| `restore_capability` | Candidate checks capability exists and journals/replays; main mutates self-model before journaling | Candidate event-first path is preferable; retain |
| `rollback_evolution` | Candidate binds rollback to adopted experiment where available and records reason/evidence; main rolls back parameter directly and journals minimal event | Candidate preserves adoption lineage; verify event/controller failure ordering and restart behavior |
| `set_goal_priority` | Candidate rejects non-finite values and missing goals before journal/replay; main mutates model first | Candidate validation/event-first path is preferable; retain |
| `update_goal_progress` | Candidate rejects non-finite progress and terminal goals before journal/replay; main mutates model first | Candidate validation/event-first path is preferable; retain |

**Overall API conclusion:** the current-main restoration is not a superior replacement for the candidate implementation. Most common-name differences preserve stronger candidate-side validation, event-first state transitions, learned behavior, or provenance. Do not cherry-pick the current-main restoration over the candidate wholesale.

### 2.3 Candidate-only APIs

The candidate exposes seven APIs not present in the current-main restoration:
- `developmental_best_related_strategy`
- `developmental_feature_strategy_estimate`
- `developmental_related_strategies`
- `import_legacy_memory_event`
- `record_evolution_evaluation`
- `record_knowledge_source_feedback`
- `resolve_prediction_feedback`

These are candidate additions, not missing current-main behavior. They support related-strategy retrieval/feature estimates, restricted passive legacy import, evidence-bound evolution evaluation, source-bound knowledge feedback and explicit prediction-feedback status.

### 2.4 API restoration disposition

- All 64 current-main unique method names (69 definition occurrences, including overloads) are represented in the candidate; the candidate contains 71 unique method names (77 definition occurrences), including seven candidate-only names.
- The 24 differing common bodies have now been individually classified.
- `beliefs()` is manually confirmed identical.
- `register_evolution_parameter()` is a deliberate signature difference requiring downstream compatibility verification.
- Seven candidate-only APIs are recorded above.
- No candidate API was found to be absent merely because the current-main restoration commit was not imported.

The source-level API reconciliation is substantially closed, but repository-wide call-site/build compatibility is not verified because no build or full caller search was performed. This is not a claim of ABI compatibility.

## 3. Candidate-specific findings requiring attention

### 3.1 Learned-strategy context can be selected from the wrong goal

In candidate `Brain::choose` and `Brain::choose_with_affect`, the strategy lookup context is derived from:

`eligible.empty() ? "global" : eligible.front().id`

However:
- `GoalModel::eligible()` includes both pending and active goals and sorts by priority/creation cycle.
- `IntentModel::select()` explicitly ignores pending goals and selects among active goals using its own score, including progress, outcome momentum and deadline urgency.
- The selected intent exposes its actual goal identity as `selected_intent.id`.

Therefore `eligible.front().id` is not guaranteed to be the active goal selected by the IntentModel. A high-priority pending goal can be first in `eligible`, while a different active goal is selected as the intent. The candidate can then apply a learned strategy associated with the wrong goal context.

**Disposition: CONFIRMED CANDIDATE CORRECTNESS RISK.** The learning context should be tied to the selected active intent, with an explicit no-intent fallback. Add a multi-goal regression covering a pending high-priority goal and a different selected active goal. No runtime fix was made in this review.

### 3.2 Goal creation can journal invalid non-finite values before rejection

Candidate `Brain::create_goal` clamps priority/progress, appends a `goal_create` event, then replays/creates the goal. It does not explicitly reject non-finite priority or progress before appending. `GoalModel::create` rejects non-finite values.

For NaN inputs, clamping does not provide a reliable finite-value validation guarantee. The method can therefore persist a goal-create record that the GoalModel refuses to instantiate.

**Disposition: CONFIRMED INPUT/PERSISTENCE INTEGRITY RISK.** Validate finiteness before event creation and append; add NaN and ±infinity regression cases. No runtime fix was made in this review.

### 3.3 Multi-event and rollback failure ordering

Two further areas need explicit failure-injection/replay proof:
- `assimilate_goal_outcome` can persist a progress event before a separate completion event. If the latter append fails, the call returns false after progress has been committed.
- `observe_evolution_canary` and `rollback_evolution` persist evidence before/around controller rollback. Failure between durable event creation and controller state transition must not produce a false claim or inconsistent reconstruction.

These are recorded as **UNRESOLVED FAILURE-ORDERING RISKS**, not asserted defects. Acceptance requires idempotent recovery or explicit partial-transition semantics.

## 4. PR #151 → PR #155 integration fidelity

Source PR #151 and integrated PR #155 share five byte-identical files out of eight. Three files differ:
- `core/cpp/include/jarvis/core/brain.hpp`
- `core/cpp/src/brain.cpp`
- `core/cpp/src/brain_restored_api.cpp`

Static semantic review confirms the central adaptation:
- PR #151 adds compositional feature strategy estimation and a control to suppress feature-model updates.
- PR #155's integrated Brain replay path retains execution-reliability evidence while passing `false` for feature-model learning when there is no observed world consequence.
- The integrated API exposes the feature estimate.
- The five exact file matches retain the developmental-learning implementation, cognitive-cycle context work, test registration and DLT-004 test.

**Disposition:** the integration preserves the identified PR #151 intent with a meaningful adaptation; it is not a wholesale merge. Retain as candidate functionality. DLT-004's evidence remains bounded to additive feature composition, not parity/XOR or broad compositional reasoning.

## 5. PR #150 → PR #156 integration fidelity

PR #150's seven changed files reconcile as:
- Two byte-identical files: `evolution_controller.cpp` and `evolution_canary_controller_suite.cpp`.
- One test-file change already subsumed by PR #148/#155: `developmental_brain_integration_suite.cpp`, using the restricted legacy import API.
- Four divergent files: `brain.hpp`, `brain.cpp`, `brain_restored_api.cpp`, and `evolution_brain_integration_suite.cpp`.

Static review of the final candidate confirms the two distinct source workstreams are represented through different integration routes:
- Restricted legacy import is present through PR #148/#155. The candidate accepts only passive observation/action event kinds, labels them `legacy_import`, and replay excludes them from trusted state transitions/learning.
- Evolution replay safeguards are represented in candidate replay and controller code. External-source evolution lifecycle events are rejected; evaluation replay validates finite/ranged evidence and recomputes the claimed outcome; adoption is tied to evaluated evidence and isolation attestation.
- PR #156 adds later rollback-parameter binding and claim-source-bound knowledge feedback; these are additional integration corrections, not claims that PR #150's source branch was merged unchanged.

**Disposition:** source intent is accounted for at the level of the identified safeguards; the divergent files are not byte-equivalent and must not be described as unchanged merges. Existing candidate tests provide targeted evidence, but no runtime verification was performed here.

## 6. Current-main workflow reconciliation

The five workflow files introduced after the shared ancestor were inspected against the exact candidate workflow tree and CMake target registry.

| Current-main workflow | Candidate status | Reconciliation result |
|---|---|---|
| `.github/workflows/dlt-002-four-hour.yml` | Exact same blob `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` | Exact match; no drift |
| `.github/workflows/jbp-mem-001.yml` | Candidate blob `82cec28819357a26881584b4ceb951c258ea24ac`; main blob `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f` | Candidate lacks main's `source_ref` input and explicit tested-commit metadata; adapt these reproducibility controls if candidate is selected |
| `.github/workflows/jarvis-learning-mechanisms.yml` | Absent as a path in candidate | Main workflow defines 35 mechanism/test gates plus an integrated changing-environment trial. All 35 named targets were checked against candidate `core/cpp/tests/CMakeLists.txt` blob `0251936730f82a7a8c928fa31dfe1d7effc83d91`; none were missing. Valuable verification workflow; not replaced by candidate JBP-001 |
| `.github/workflows/jbp-brain-int-001.yml` | Absent as a path in candidate | Main workflow builds/runs five integrated suites plus persistence and DLT-002. Candidate JBP-001 overlaps on persistence and DLT-002 but does not run the same five integration suites; partial, not equivalent |
| `.github/workflows/jbp-learning-002.yml` | Absent as a path in candidate | Main workflow runs three independently seeded DLT-002 trials with configurable source ref/seed base. Candidate seed-sweep runs the same long-run executable across three fixed seeds, but lacks explicit source-ref and seed-base controls; partial, not identical |

The three absent workflows are not automatically runtime blockers, but they provide distinct and useful verification entry points. Preserve their capabilities through an explicit CI/workflow adaptation plan rather than copying blindly. The 35-gate workflow's test target names all exist in the candidate CMake registry; this was a static name check, not a build or run.

## 7. Inherited-history attribution — remaining blocker

The prior checkpoint already establishes:
- 1,416 unique inherited commit SHAs were enumerated between the shared ancestor and PR #155 head across 15 paginated compare responses.
- The 165-path final tree delta is reconciled as 145 PR #97-only paths, 14 paths modified in both the PR #97 and post-PR #97 segments, and six paths first introduced after PR #97.
- The 172-commit post-PR #97 segment is decomposed into 10 preparation commits, 153 PR #148 commits and nine PR #155 integration commits.
- PR #156 adds 12 code-bearing commits and one documentation commit.
- The main/specification side's 21-commit divergence is decomposed into nine current-main commits and 12 accepted specification commits.

What remains incomplete is the **per-commit origin → changed path → relevant hunk attribution across the entire inherited 1,416-commit history**, especially the 1,244-commit PR #97 line. The existing path-set and PR-lineage arithmetic do not substitute for that ledger.

The available GitHub connector's commit search returns at most 100 records per call and exposes no pagination cursor for exhaustive retrieval; compare results provide graph/file statistics but not a retrievable complete commit-page sequence. I will not claim exhaustive commit/hunk attribution from incomplete records. Completing that ledger requires a local clone or an API route that exposes all commit pages and per-commit file patches. A local clone was attempted during this pass, but the execution environment could not resolve github.com; no clone data was retrieved.

## 8. Independent-review operations

Live PR #175 inspection confirms:
- zero submitted reviews;
- no requested individual reviewers or review teams;
- no repository CODEOWNERS file found at the standard root or `.github/CODEOWNERS` paths;
- the visible PR discussion so far is authored by the repository owner account.

The Builder cannot turn its own technical review into an independent review. The GitHub review-request operation requires an actual GitHub username or team slug. None is identified by the current PR metadata, CODEOWNERS or visible discussion. No reviewer request was fabricated.

**Required from the Project Director:** identify an independent GitHub reviewer username/team or add an independent reviewer with repository access. Once identified, request the review against the exact current PR #175 HEAD and ask the reviewer to challenge both Gate A and Gate B records.

## 9. Updated disposition

- API semantic comparison: 24 common function-body differences classified; `beliefs()` manually matched; return-type change on `register_evolution_parameter()` recorded; seven candidate-only APIs identified.
- PR #151/#155 integration: central semantic adaptation reviewed; no byte-equivalence claim.
- PR #150/#156 integration: both workstreams accounted for; no byte-equivalence claim.
- Workflow reconciliation: all five current-main workflow paths classified; 35 learning-mechanism test targets confirmed present in candidate CMake.
- Candidate-specific correctness risks: wrong goal context in learned-strategy lookup and non-finite goal creation before journaling; additional partial-failure ordering remains unverified.
- Full 1,416-commit per-commit origin/path/hunk ledger: still incomplete.
- Independent review: still absent.

**Final Gate A status: NOT CLEARED. PR #156 remains a candidate only. No implementation baseline is selected.**

No runtime source, test, build, workflow, dependency, schema, API, branch history or deployment state was changed. This addendum is static review evidence only.
