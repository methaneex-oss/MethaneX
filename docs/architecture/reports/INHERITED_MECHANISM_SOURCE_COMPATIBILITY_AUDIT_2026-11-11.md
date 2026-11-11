# Inherited Mechanism Source Compatibility Audit — 2026-11-11

## 1. Purpose and decision boundary

This report tests the inherited-rule concerns raised during the blind Brain Foundation Architecture review against actual source, rather than treating a prose disposition as proof of compatibility.

**Audited source revision:** PR #97 donor branch HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` (open, draft, unmerged; base `main`). This is the exact source revision used by the Phase 2 source-integration map for the donor implementation. The audit does not claim that this donor branch is the current default-branch runtime or that every historical branch has been searched.

**Scope:** production cognitive source files and their directly relevant headers for source reliability, confidence/decision thresholds, goal selection and belief revision. No source files, tests, workflows, dependencies or runtime behavior were changed. This is a read-only compatibility audit, not a code remediation or implementation authorization.

## 2. Executive result

| Concern | Source finding | Compatibility disposition |
|---|---|---|
| Fixed/historical source reliability | Reliability defaults and an arithmetic running mean exist; the production path largely averages incoming reliability metadata. Correctness-based `score_source` exists but no call site was found in the 14 inspected production cognitive source files; its discovered use is a unit test. | **ADAPT.** Do not treat this as calibrated source trust. Preserve the raw evidence and provenance; add domain/task/time scope, independent outcome scoring, uncertainty, calibration and drift handling in a later specification. |
| Fixed confidence threshold | No single global confidence cutoff was found in the inspected paths. Several distinct numeric defaults exist: action-score classification thresholds, context-similarity retrieval threshold, retention/forgetting threshold, prediction/concept minimum-strength defaults and evidence-confidence priors. They have different semantics and must not be conflated. | **CONDITIONALLY RETAIN AS PROVISIONAL ENGINEERING DEFAULTS**, not learned beliefs or universal truth. Each must have an explicit objective, scope, owner, calibration/evaluation evidence, version and consequence. |
| First-eligible-goal selection | The cognitive cycle falls back to `eligible.front()`; eligible goals are sorted by descending priority then creation cycle. Other planning/decision paths also use the first eligible goal as a strategy context, even when intent is selected separately. | **REPLACE AS A GENERAL SELECTOR.** Any bounded fallback must be an explicitly authorized external policy. Contextual strategy lookup must use the selected intent/goal, not an unrelated first eligible goal. |
| Belief overwrite | The authoritative `beliefs_` map overwrites an existing value before marking the record disputed. Action-outcome beliefs are also unconditionally replaced. WorldModel stores some conflicting incoming facts, but retains only one active fact per subject/predicate and may replace the active fact; the event journal is not a versioned belief ledger. | **REPLACE.** Require versioned claims/hypotheses, provenance, temporal/contextual scope, competing values, explicit revision/supersession rationale and dependency invalidation. |

**Overall source compatibility:** NOT COMPATIBLE AS-IS with the architecture's no-silent-overwrite and non-hardcoded goal-selection requirements. Some defaults are defensible as provisional engineering parameters, but are not validated learned mechanisms. This is a donor-revision finding, not a claim about all runtime branches.

## 3. Source reliability: metadata average is not calibrated trust

### 3.1 Exact evidence

- [knowledge.hpp at audited revision](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/knowledge.hpp), blob `3da0d2059331af405bbb0ba98c61308ead99c405`, lines 12–20: `KnowledgeEvidence::reliability` and `KnowledgeMetric::reliability` both default to 0.5.
- [knowledge.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/knowledge.cpp), blob `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a`, lines 8–19: `assimilate` sets the first metric from incoming evidence reliability, then computes an observation-count-weighted arithmetic mean of later incoming reliability values.
- The same file, lines 22–28, implements `score_source(source, correct)` as a running mean of binary correctness observations. No call site was found in the 14 inspected production cognitive source files; the discovered use is in [knowledge_memory_phase3_suite.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/tests/knowledge_memory_phase3_suite.cpp), blob `e33b9813edbfaf02a91a3f94988f5c7a54ceed8f`, lines 26–36.
- [brain.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`, lines 624–652: replay supplies 0.5 when a learning event omits reliability and 0.7 for non-learning events; it then feeds the resulting value into `KnowledgeModel::assimilate`. Lines 790–820 show `Brain::learn` returns the source metric's reliability after assimilation, or the supplied evidence reliability if no metric exists.
- [memory.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/memory.cpp), blob `ab42bba1d32d6f48d091787491c72294a4a55bb5`, defines a 0.5 fallback for memory confidence; [memory.hpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/memory.hpp), blob `5401d5bd236cca8d3a93f2815164a7734cf6990f`, also initializes record confidence to 0.5.

### 3.2 Interpretation

The current production assimilation path does not independently verify whether a source was correct before updating its reliability metric. It averages caller-supplied reliability metadata. The correctness-scoring method exists but was not found wired into the inspected production path. The resulting value is therefore not an empirically calibrated, domain-specific or time-sensitive estimate of source trust.

The 0.5 and 0.7 values are defaults, not learned facts. A neutral/default value can be useful to initialize an unknown quantity, but downstream behavior must preserve its provisional status and uncertainty rather than treating it as evidence of source quality.

**Required later specification:** distinguish source identity from evidence reliability; define task/domain and time scope; define independent correctness/outcome adjudication; represent sample size and uncertainty; address drift and conflicting sources; prevent caller-supplied reliability from validating itself; and specify what happens when reliability is unknown.

## 4. Confidence and numeric thresholds: distinct purposes

### 4.1 Exact evidence

- [decision.hpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/decision.hpp), blob `88ee24e6dc93826759de46b38d15a08a685a3aac`, lines 10–29: configurable `DecisionPolicy` defaults include act score 0.5, reject score -0.5, clarify uncertainty 0.75, escalate threat 0.75 and escalate risk 0.65. [decision.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/decision.cpp), blob `012025bc2ef66b1b9555b9b9f2b220b49c8d36c4`, lines 88–101, applies these to decision classification. The policy is replaceable through `set_policy`; these are action-policy defaults, not a universal belief-confidence gate.
- [developmental_learning.hpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/developmental_learning.hpp), blob `e3b9bf8af265b67829fd7deb323d88a3a9dd4b75`, lines 67–72, exposes a default related-context minimum similarity of 0.5 and consolidation retention threshold of 0.05. [developmental_learning.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/developmental_learning.cpp), blob `dbf5f43271dfa0a3c57236e2faa82eb88d15490d`, lines 368–375 and 403–434, applies them to retrieval and forgetting.
- [brain.hpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/brain.hpp), blob `671186f4c39879a182f9e511394fc564d86f2988`, line 62, defaults prediction/context minimum strength to 0.5 and minimum shared contexts to 2.
- [brain.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`, lines 201–215 and 724–744, uses 0.5 as a fallback evidence/relevance-confidence prior.
- [developmental_learning.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/developmental_learning.cpp), lines 250–278, uses a fixed weighted learning-rate equation with fixed coefficients and a 0.05–0.95 clamp. This is an engineered update schedule, not an acquired preference or outcome mapping; its weights nevertheless need evaluation and explicit ownership.

### 4.2 Interpretation

The inspected code does **not** establish one global confidence threshold that turns beliefs into truth. It contains several different kinds of fixed numeric defaults: action-score boundaries, uncertainty/risk escalation boundaries, similarity filters, forgetting cutoffs, minimum-strength filters and evidence priors. Treating them all as one “confidence threshold” is technically inaccurate.

They may remain provisional engineering parameters only if their objective, semantic meaning, decision consequence, domain, calibration/evaluation evidence, version and owner are explicit. A threshold must not be used to silently convert a hypothesis into a fact or authorize an external action. The fixed learning-rate coefficients must likewise be treated as a provisional mechanism parameterization, not evidence that the learning dynamics are already learned.

## 5. First-eligible-goal selection and context coupling

### 5.1 Exact evidence

- [cognitive_cycle.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/cognitive_cycle.cpp), blob `f191dd610d6cbe1621756c35e7c13af2054a7266`, lines 118–137: an explicit caller goal is respected; otherwise the learned intent is attempted; if no matching intent exists, the function returns `eligible.front()`.
- [goals.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/goals.cpp), blob `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`, lines 75–94: eligible goals are filtered by status, deadline and prerequisites, then sorted by descending priority and ascending creation cycle. The fallback is therefore the highest-priority/oldest eligible item, not arbitrary insertion order.
- [brain_affective_planning.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_affective_planning.cpp), blob `2a9406257c23f3a66a64071842be7d6448799406`, lines 96–107, uses `eligible.front().id` as a strategy context whenever any eligible goal exists.
- [brain_restored_api.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain_restored_api.cpp), blob `7155d4d9c8eef527836fb79bf901aa32ddbae38b`, lines 217–218, selects an intent but independently binds developmental strategy context to `eligible.front()`. This can make learned strategy retrieval use a different goal context from the selected intent.

### 5.2 Interpretation

The reviewer concern is valid, but “first eligible” is more than one isolated fallback. It also leaks into context selection. The priority/creation ordering is deterministic, but deterministic ordering is not a sufficient cognitive selection mechanism and does not prove the chosen goal is the one the intent/planning system evaluated.

**Required later correction:** use the selected intent/goal consistently as the context key; make candidate-set evaluation and tie-breaking explicit; represent no-intent/no-evaluation conditions as unresolved rather than silently selecting the first item. Any emergency fallback must be an explicitly authorized operational policy with bounded consequences and a traceable reason.

## 6. Belief overwrite and partial conflict preservation

### 6.1 Exact evidence

- [brain.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/brain.cpp), blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`, lines 672–688: for an existing belief key, the code assigns the incoming value to `it->second.value` and only then sets a disputed flag when the value differs. The active `Belief` object retains one value and one update sequence.
- The same file, lines 430–434, assigns `beliefs_[belief_key]` unconditionally for action execution status, replacing the prior action-status belief.
- [world_model.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/world_model.cpp), blob `5b68e8fe37d99732557237e347ae02234a3de172`, lines 9–37: WorldModel keeps one active fact per subject/predicate and stores the incoming conflicting fact in `disputed_facts_`; when the incoming fact has greater confidence, it replaces the active fact. The previous active value is not added to the disputed list in that branch.
- [world_model.hpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/include/jarvis/core/world_model.hpp), blob `1c14f692374b0ab272f05634b7bdd26e358b4f1f`, lines 13–28, defines a single value/confidence/observation count/sequence/disputed flag per active fact and relation.
- [reasoning.cpp](https://github.com/methaneex-oss/MethaneX/blob/c1da222e6c94aeb3f2ad000392c21fe4fc81ab25/core/cpp/src/reasoning.cpp), blob `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1`, lines 34–44, excludes disputed beliefs from authoritative deduction premises. This is a useful safeguard, but it does not restore the overwritten alternative into the authoritative belief record.

### 6.2 Interpretation

The system does retain raw episodes in the memory journal and has a partial disputed-fact mechanism. Therefore it would be inaccurate to say that every contradictory observation is globally erased. However, the authoritative belief map and active fact model still use latest-value replacement, with incomplete alternative preservation and no complete belief-level version/provenance lineage. This fails the architecture's stronger revision contract.

**Required later correction:** replace single-value mutation with an evidence-backed claim ledger or equivalent versioned representation; preserve both old and new claims; retain source, time, context, uncertainty and contradiction links; record why one claim is promoted/suspended/superseded; and invalidate dependent predictions/inferences when the authority changes.

## 7. Source compatibility register

| Mechanism | Result | Required next work | Responsible owner |
|---|---|---|---|
| Source reliability defaults/metric | ADAPT; not calibrated source trust | Separate evidence reliability from source competence; add scope, provenance, sample uncertainty, independent scoring and drift | Architecture & Engineering Builder |
| Decision/retrieval/retention thresholds | Provisional only; semantics differ | Inventory each default and calibrate against its own objective and error costs | Architecture & Engineering Builder |
| Fixed learning-rate equation | Provisional engineered schedule | Evaluate sensitivity, transfer and adaptation; do not present coefficients as acquired behavior | Architecture & Engineering Builder |
| Goal fallback/context selection | Replace general fallback and fix selected-goal/context mismatch | Candidate evaluation, explicit no-intent handling, permutation tests, correct context binding | Architecture & Engineering Builder |
| Belief/action-status overwrite | Incompatible with foundational revision contract | Versioned claim state, conflict preservation, provenance and replay-safe revision | Architecture & Engineering Builder |

Project Director approval is required for any change to foundational cognitive authority, scope or decision rights. The Independent Reviewer may challenge the source audit and proposed correction; that role does not approve the architecture.

## 8. Limitations and completion criteria

This audit covers the exact PR #97 donor HEAD and the identified production cognitive files. It does not establish that every other branch, historical revision, runtime binary or external consumer uses identical code. It does not run the test suite, prove runtime behavior, assess numerical calibration from data, or authorize code changes.

The source-level portion of the blind-review finding is now **ASSESSED for this donor revision**. Compatibility is not accepted as-is. Before a later implementation specification can preserve any of these mechanisms, it must either (a) supply the required evidence and explicit bounded exception, or (b) define the correction and tests. The current architecture must not imply these donor implementations already satisfy its contracts.

## 9. Exact source manifest

| Path | Blob SHA |
|---|---|
| core/cpp/src/brain.cpp | dec9e5442b3ca4b81a7879855c6146b2619934cc |
| core/cpp/src/cognitive_cycle.cpp | f191dd610d6cbe1621756c35e7c13af2054a7266 |
| core/cpp/src/knowledge.cpp | 21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a |
| core/cpp/include/jarvis/core/knowledge.hpp | 3da0d2059331af405bbb0ba98c61308ead99c405 |
| core/cpp/src/developmental_learning.cpp | dbf5f43271dfa0a3c57236e2faa82eb88d15490d |
| core/cpp/include/jarvis/core/developmental_learning.hpp | e3b9bf8af265b67829fd7deb323d88a3a9dd4b75 |
| core/cpp/src/goals.cpp | afaedcfb0f2f68ff88b3a20e474fce04bb59815c |
| core/cpp/include/jarvis/core/goals.hpp | 66f8cd436a18a0bca8039205f682fc929c32b6a5 |
| core/cpp/src/memory.cpp | ab42bba1d32d6f48d091787491c72294a4a55bb5 |
| core/cpp/include/jarvis/core/memory.hpp | 5401d5bd236cca8d3a93f2815164a7734cf6990f |
| core/cpp/src/world_model.cpp | 5b68e8fe37d99732557237e347ae02234a3de172 |
| core/cpp/include/jarvis/core/world_model.hpp | 1c14f692374b0ab272f05634b7bdd26e358b4f1f |
| core/cpp/src/brain_affective_planning.cpp | 2a9406257c23f3a66a64071842be7d6448799406 |
| core/cpp/src/brain_restored_api.cpp | 7155d4d9c8eef527836fb79bf901aa32ddbae38b |
| core/cpp/include/jarvis/core/brain.hpp | 671186f4c39879a182f9e511394fc564d86f2988 |
| core/cpp/include/jarvis/core/decision.hpp | 88ee24e6dc93826759de46b38d15a08a685a3aac |
| core/cpp/src/decision.cpp | 012025bc2ef66b1b9555b9b9f2b220b49c8d36c4 |
| core/cpp/tests/knowledge_memory_phase3_suite.cpp | e33b9813edbfaf02a91a3f94988f5c7a54ceed8f |
