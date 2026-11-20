# DF-02 — Action feedback and evolution-adoption regression audit

> **Scope clarification:** This is a capability-gap comparison between the pre-PR-#97 candidate source baseline and the unmerged PR #97 donor implementation line. It does **not** claim the candidate previously integrated these donor mechanisms and then lost them. The term “regression” in this historical report filename means a functional delta relative to the donor, not a post-integration code regression. The donor is not an adopted baseline; the Project Director retains source selection and adoption authority.

**Date:** 2026-11-20  
**Candidate baseline:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

This supplement records two high-impact source-level regressions. The comparison is exact at the two pinned revisions; it does not authorize donor adoption or establish that the donor is the final desired baseline.

## 1. Action consequence observation is removed from the candidate API

### Exact source evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/action_execution.hpp` | `38ff7033e7621db8f05cc1edc4bf59cb899ccdd3` | `04c73d02bdd4e1154be142dfeb024fc07ad432f8` |
| `core/cpp/src/action_execution.cpp` | `c2f8653eb755fa2790a88e49bc8b0b9c3077e439` | `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff` |
| `core/cpp/include/jarvis/core/brain.hpp` | `8268ef84e0b361ead536724ba7761904b30ee58f` | `671186f4c39879a182f9e511394fc564d86f2988` |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | `b4a0060596c91c67080ac0a2db324f720d760fbe` | `db11ac95d26a97b01dfeb67cfb85194dc284ffb8` |

The donor request adds an optional consequence observer returning `std::optional<double>`. The donor result adds `ActionOutcome` with expected consequence, observed flag, actual consequence and bounded consequence error, plus prediction sequence/key/value linkage. After an action executes, the donor records a finite observed consequence and computes the difference from the expectation. This observation is intentionally independent of verification/rollback status because a failed or rolled-back action can still have a real-world consequence.

The candidate request and result remove all of those fields. Its `Brain::execute_action` wrapper accepts execute/verify/rollback/authorization only and records a coarse status belief. It has no route for an observed consequence to enter the action outcome through this API.

### Behavioral test difference

The donor phase-7 suite does more than assert that an action was verified. It supplies an observed consequence, checks the expectation/actual/error values, then runs a cognitive cycle before and after learning. A negative consequence updates affective learning and developmental strategy; the same candidate action is demoted below the alternative on the next planning cycle. It then reconstructs Brain from the journal and verifies that the changed action preference survives restart.

The candidate suite retains basic authorization, execution, verification, rollback and status-belief checks, but removes the consequence-observation and post-learning behavioral-change/persistence scenario.

### Finding

This is not merely missing telemetry. It removes the explicit action → observed consequence → prediction error → affective/developmental update → changed planning behavior path from the candidate action-execution interface. The donor test is direct evidence of the intended end-to-end mechanism; the candidate test does not establish an equivalent path.

**Disposition:** high-priority candidate regression; no runtime change made in this documentation pass.

## 2. Evolution adoption no longer proves a durable, matching evaluation

### Exact source evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | `53bcd379fb788a3b0c369309c328f70d56f051ba` | `551d0d41b19abbeca425d102ec4c61984dfac0b6` |
| `core/cpp/src/evolution_controller.cpp` | `01484ebf12fc3902bce749030a1f54610b26236a` | `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` |
| `core/cpp/src/evolution_adoption.cpp` | `b62153de36395b3ef46e25a1af0520e15af85e3f` | `836216bb567e2c87d14b6442bd363e9861ac6974` |
| `core/cpp/src/evolution_safety.cpp` | `6c930ebbe69ad92fe155e3c169e3e996442f22cf` | `5a4669de9296958eacc77534bad87ce7c30ae52d` |
| `core/cpp/src/evolution_adoption_journal.cpp` | `a9e141ac0b784466e86575eefdb3260b2e15dfc0` | `d8df30a2902d3dac734fb1a571cbbecdd881b76f` |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | `24a1be9541cc038518065724aef1968efc4dc595` | `fc8ae17bb837831fef7bf69873ec0e5243e2bc22` |

### 2.1 Isolation attestation was removed from the experiment type

The donor `EvolutionExperiment` carries an `isolated` result and a private attestation snapshot covering the experiment ID, proposal key and values, baseline/candidate fitness, minimum improvement, confidence, outcome and execution state. `has_valid_isolation_attestation()` verifies that the evaluated fields still match the attested snapshot.

The candidate type contains no isolation field, no private attestation snapshot and no attestation validation method, despite the shared policy retaining `require_isolation{true}`.

### 2.2 The candidate safety gate does not enforce its isolation policy

The donor safety gate rejects when required isolation attestation is absent, validates finite and bounded confidence/policy values, and recomputes whether candidate fitness exceeds baseline by the declared minimum improvement before accepting an `Improved` label.

The candidate safety gate checks the outcome label, finite baseline/candidate fitness, minimum confidence and maximum regression. It does not inspect `policy.require_isolation`, does not validate the minimum-improvement field, and does not independently recompute the claimed improvement threshold. The policy flag therefore does not provide the protection its name and default imply.

### 2.3 The candidate controller accepts adoption without matching durable evaluation evidence

The donor controller's `validate_adoption_for_brain` requires a durable `Evaluated` history record for the same experiment ID and exact matching parameter key, outcome, baseline fitness, candidate fitness and confidence. It independently recomputes the outcome and checks the pending adoption-journal record against the experiment values. It also handles persistence compensation by restoring the model and journal to the correct prior state if commit/history writes fail.

The candidate controller's `adopt` checks `candidate_executed`, stages the supplied experiment, calls the weakened safety gate, adopts the model, commits the journal and appends an `Adopted` history record. It does not require a prior `Evaluated` history record matching the exact experiment. The separate `record_evaluation` API exists, but the adoption path does not require its successful prior use. The candidate compensation path also uses ordinary rollback/reject transitions where the donor has explicit `restore_pending` and `restore_adopted` recovery transitions.

The standalone candidate `EvolutionAdoption::adopt` is weaker still: it checks only `candidate_executed` and the safety gate, then calls `model.adopt`. The donor standalone helper deliberately returns false and documents that a stateless helper cannot verify durable matching evaluation history; adoption must go through `EvolutionController`.

### 2.4 Test coverage was sharply reduced

Candidate `evolution_adoption_journal_suite.cpp` is a five-line journal state-transition smoke test. The donor suite exercises controller-level rejection of neutral/unsafe experiments, successful adoption, rollback, replay compensation, durable history behavior and the stateless-helper fail-closed boundary. The donor's `EvolutionAdoptionJournal` also exposes explicit restore-pending and restore-adopted transitions; the candidate journal omits them.

### Finding

The candidate has weakened both the *evidence required before adoption* and the *recovery guarantees when persistence fails*. This is a safety-boundary regression, not just a missing test. The retained `require_isolation` setting is not enforced by the candidate safety implementation, and the candidate experiment type cannot carry the donor's tamper-evident isolation attestation.

**Disposition:** critical candidate regression; no runtime change made in this documentation pass.

## 3. Builder conclusion and bounded next work

These two comparisons demonstrate why the remaining DF-02 work cannot be closed by counting lexical matches or merely finding a file with the same name. The semantic audit must inspect API contracts, end-to-end behavioral tests, persistence and failure compensation, build registration and runtime integration.

The evidence also cautions against blindly copying the donor files: the correct repair must preserve the established candidate architecture while restoring the required guarantees and tests. No donor baseline is selected and no donor code is copied.

DF-02 remains OPEN until the other candidate-branch lexical paths and their semantic successors, dependencies, duplicate owners, retention/retirement and authority are adjudicated. This supplement closes only the two specific regression findings above.
