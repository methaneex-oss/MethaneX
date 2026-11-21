# DF02 — Seven Newly Exposed No-Symbol Paths: Semantic Adjudication and Source-Line Reconciliation
## 2026-11-21

**Status:** Builder evidence addendum. This report makes no runtime-code changes, selects no source baseline, and does not authorize donor adoption. Project Director authority remains reserved for source-line selection and Stage A.

## 1. Exact evidence scope

This adjudication follows the all-ref consumer and branch/blob ownership scan executed by the documentation-link-audit workflow on PR #192.

- Repository: methaneex-oss/MethaneX
- Candidate PR #192 head used for this scan: 19c1c168fdbdab58ed9732cd250d2ae4624936eb
- Candidate branch: docs/whole-brain-planning-scope-correction-20261107
- Donor PR #97 head: c1da222e6c94aeb3f2ad000392c21fe4fc81ab25
- Scanner branch: audit/df02-all-ref-consumer-scan-20261120
- Scanner commit: b8a594ea514ff44cadb5342986c68b1eac6e22ed
- Workflow run: 44931803411
- Branch/blob ownership artifact: 14717933378
- Downloaded artifact SHA-256: 189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f

The scan covered 254 live branch refs and 213 unique branch tips. It found 159 donor paths: 63 absent from the candidate at the same path, 95 divergent, and one identical. The candidate lexical-consumer scan identified 111 paths (76 divergent and 35 absent). Separately, 48 donor paths had no candidate lexical-consumer match: 28 absent, 19 divergent, and one identical.

The prior no-symbol supplement adjudicated 41 of those 48 paths. This report adjudicates the remaining seven. It does not claim the separate 76-path divergent set is semantically closed.

The artifact contains 798 exact path/blob ownership rows, 1,938 path-reference rows, and 1,226 consumer-blob/path/category occurrences. It records branch names against exact blob versions rather than treating a branch name or filename as proof of implementation.

## 2. Seven-path adjudication

### 2.1 core/cpp/include/jarvis/core/experience_memory.hpp — absent from candidate

The donor contains a standalone ExperienceMemory helper and a separately registered experience-memory test. The helper indexes individual prediction experiences by sequence and also supports lookup by semantic key. It is not included by the donor Brain header and is not the Brain's active memory implementation. Its presence must not be counted as a separate integrated cognitive-memory subsystem.

The donor Brain itself stores prediction records in a sequence-preserving vector and resolves a prediction by sequence. The current candidate Brain instead stores predictions in an unordered map keyed by semantic key and resolves by that key. Repeated unresolved predictions for the same semantic key can therefore collapse onto one map entry. This is a meaningful behavioral difference.

**Disposition:** Do not adopt ExperienceMemory as a second Brain memory subsystem merely because the header is absent. Preserve the underlying requirement—distinct experience identity and sequence-safe prediction feedback—and evaluate porting that behavior into the current Brain architecture after the source baseline is selected. The actual gap is the candidate's key-collapsing prediction store, not the absence of this standalone helper.

### 2.2 core/cpp/src/brain_affective_planning.cpp — absent from candidate

In the b627 source line this file is compiled into the cognitive core and called by Brain planning methods. It combines current affective state and developmental strategy evidence when evaluating candidate actions. It is not merely a declaration or an isolated demonstration file.

The mechanism changes planning scores using the Brain's current internal state and experience-derived strategy evidence. It is a functional affect-to-planning connection, not proof of biological emotion or a complete human-like affect system. Its coefficients and transfer rules remain engineered parameters requiring calibration and counterexample testing.

**Disposition:** A real donor capability candidate for future architecture integration. Do not copy it into the current candidate as an isolated patch. First reconcile its state contracts, planning interfaces, and parameter semantics with the accepted whole-Brain architecture.

### 2.3 core/cpp/src/brain_prediction_context.cpp — absent from candidate

In the b627 source line this file implements contextual prediction behavior invoked by Brain. It uses contextual concepts and evidence strength to adjust predictions and preserves the contextual prediction path in Brain's prediction history.

This is an integrated Brain method path in that source line, not a standalone utility. The current candidate has no equivalent method with the same contextual prediction contract.

**Disposition:** Record as a genuine donor capability candidate. Evaluate it alongside the candidate's prediction identity and feedback model; do not port it before the whole-Brain representation and prediction contracts are accepted.

### 2.4 core/cpp/tests/affective_planning_suite.cpp — absent from candidate

The donor CMake configuration registers this suite with CTest. It exercises the interaction between affective state and plan scoring. Its existence provides test evidence for the donor implementation, but the suite does not by itself prove that affective state is learned, biologically grounded, or robust across a broad environment.

**Disposition:** Treat as donor integration-test coverage for the affective-planning mechanism. If that mechanism is adopted or reimplemented, port the behavioral assertions and add held-out and counterexample coverage. Do not count the absent test file as a separate production capability.

### 2.5 core/cpp/tests/association_causality_phase5_suite.cpp — divergent candidate path

The candidate version is substantially shorter than the b627 version (57 lines versus 177 lines in the inspected revisions). The donor suite exercises a broader set of behaviors, including reliability-weighted associations, contextual association behavior, and causal-learning checks after experience. The candidate retains a narrower association/causality test surface.

This is a confirmed test-coverage difference. It is not sufficient, on its own, to prove that every donor behavior is absent from candidate production code; some candidate behavior may have moved into other modules or contracts.

**Disposition:** Mark as a test-coverage regression/gap requiring source-level successor mapping. Do not copy the test file blindly. Map each donor assertion to a candidate implementation path and classify it as equivalent, superseded, missing, or intentionally excluded.

### 2.6 core/cpp/tests/reasoning_architecture_suite.cpp — divergent candidate path

The candidate version is shorter than the b627 version (55 lines versus 96 lines in the inspected revisions). The donor suite includes additional checks around disputed evidence and causal-link codec behavior, including delimiter-bearing values and legacy/malformed serialization cases. The donor line contains a typed causal-link codec contract that is not represented by the same candidate header/path.

This is a concrete validation-surface difference. The candidate may have a different serialization implementation, so the correct next step is to trace the candidate parser and its consumers rather than assume the donor codec should be copied.

**Disposition:** Keep open as a reasoning/evidence-serialization coverage gap. Require explicit tests for disputed evidence exclusion from inference and unambiguous serialization round trips, whether implemented through the donor codec or a verified candidate successor.

### 2.7 engineering/cpp/include/jarvis/engineering/task_ledger.hpp — absent from candidate

The b627 line includes an EngineeringTaskLedger integrated through EngineeringCoordinator::dispatch_tracked. It provides task identity, status transitions, dependencies, agent assignment, revision tracking, evidence references, compare-and-swap transition checks, and a file-backed append-only journal protected by operating-system file locks.

This is an engineering-orchestration primitive, not Brain memory. It is also not a complete multi-agent LLM builder: the EngineeringAgent remains an abstract interface; the current main coordinator has no provider adapter, Git operation adapter, or durable shared message bus. The task ledger test uses separately constructed ledger instances and concurrent operations within one test process; it does not spawn independent operating-system processes. The file-lock implementation is relevant evidence, but the test must not be described as a completed cross-process stress test.

**Disposition:** Optional donor engineering capability. Do not count it as cognitive memory or a complete agent collaboration system. Evaluate it separately against the accepted engineering-orchestration scope, and strengthen true multi-process and crash-durability tests before relying on it for shared agent coordination.

## 3. Corrected interpretation of the source lines

The exact branch/blob ownership data changes how the 159-path comparison should be described:

- Current main and PR #192's documentation branch have identical core/cpp and engineering/cpp source trees. PR #192 is documentation work; it has not adopted the donor cognitive implementation.
- The current main candidate has one identical donor path, 95 divergent paths, and 63 absent donor paths.
- The b627 branch integration/priority-one-memory-bool-hardening contains all 159 donor paths: 139 are byte-identical to the PR #97 donor version and 20 are later variants. It also contains additional core files. It is a later, tested source line, not an accepted or merged baseline.
- The b627 branch has exact-head successful Brain CI, JARVIS Brain Tests, ThreadSanitizer, and native build runs. The CTest log reports 74/74 passing. Relevant runs include 41238156443, 41238156399, 41238156415, and 41238156428.
- The separate fix/gate-a-d1-d2 line is divergent from b627 and includes additional changes to integration suites and restored-API code. No exact-head CI evidence was found for that branch. It is not a safe substitute for b627.
- PR #97 remains an open draft with a very large history divergence from current main (reported as 1,244 commits ahead and 84 behind, with mergeability false). It must not be merged or rebased as a routine change.
- PR #165 (b627 source line) and PR #170 (brain-constitution/MCU documentation line) are separate open draft stacks. Neither is part of main.

The b627 line is therefore the strongest currently verified donor-derived source candidate found in this scan, but it is not automatically the correct baseline. The current main has a different source architecture and later validation work. Any integration requires a deliberate port/reconciliation plan, not a blind merge.

## 4. Training evidence and its limits

The historical long-run artifacts are real and valuable, but their provenance must remain exact:

- JBP-MEM-001 run 40564048699: 60/60 iterations passed in a 30-minute memory and fresh-process restart trial.
- JBP-LEARNING-002 run 40564002262: three 15-minute seeded runs, each with six phases including environmental change, reversal, and a generalization probe.
- JBP-BRAIN-INT-001 run 40563931674: an eight-minute integration trial covering action consequence feedback, prediction resolution, and memory restoration.
- JARVIS Learning Mechanisms Probe run 40563880254: 36/36 mechanism gates and a 30-minute integrated trial with 1,643 episodes.

All four runs used tested commit 3a4524b6723b976a3141e66ec90ab1686a9f5762 from feat/jarvis-affective-state. The workflow definition itself was executed from a323ce776c033f7eb1c27629d17b9aaa116509cf. These artifacts do not validate the later b627 HEAD.

The three-seed learning experiment demonstrated adaptation across a controlled, seeded, partially observed environment with noisy outcomes and reversals. Final action-selection accuracy varied by seed and phase; prediction mean absolute error remained approximately 0.61–0.66. The 30-minute integrated probe ended at approximately 96.98% decision accuracy but approximately 0.713 prediction MAE, with many unresolved non-action predictions. These are useful controlled-learning results, not evidence of general intelligence, real-world perception, or broad open-world competence.

The b627 DLT-002 source has since added a feedback-mode control path and records whether consequence feedback actually reaches the Brain. The existing JBP-LEARNING-002 workflow does not expose that mode as an input and defaults to the feedback-enabled run. The old artifacts therefore do not establish a paired no-feedback causal control for the later code.

**Required revalidation if b627 is selected:** rerun DLT-002 on the exact selected SHA across multiple seeds, include feedback-enabled and feedback-disabled controls, preserve the artifact bundle, and evaluate both action-selection accuracy and prediction calibration. Do not use old 3a results as a substitute.

## 5. Additional implementation claims that require precise wording

The b627 Memory implementation learns a simple event-kind-to-tier distribution from promotion/consolidation feedback. That is a genuine but narrow adaptive mechanism. It does not mean every memory decision is learned.

The same implementation still uses engineered consolidation coefficients, tier thresholds, and a fixed recall-ranking formula. The Memory header comment says salience and retrieval are learned rather than encoded as fixed cognitive weights; the inspected implementation does not substantiate that full claim. Salience/confidence are read from event evidence or defaulted, while consolidation and retrieval use fixed formulas. Correct the claim or implement and evaluate the promised learning mechanism before describing salience and retrieval as learned.

The knowledge-source feedback path requires host-supplied provenance and evaluator verification callbacks. The default calibration policy is deliberately disabled unless a caller supplies a freshness/minimum-evidence policy. No production host trust root, evaluator identity/key lifecycle, independent ground-truth adjudicator, or cryptographically protected journal is established by the repository. The Priority One trust-boundary contract correctly identifies these as unresolved prerequisites.

## 6. DF02 disposition after this addendum

The 48 no-symbol paths are now individually covered by the earlier 41-path supplement plus this seven-path adjudication. This closes only the no-symbol-path semantic inventory.

DF02 remains OPEN because the 76 divergent lexical-consumer paths still require path-by-path semantic successor/retirement decisions, and the exact source baseline remains a Project Director decision. The new 798-row branch/blob ownership artifact supplies the exact branch/version evidence needed for that work; it does not itself authorize adoption.

No production source, tests, runtime behavior, or architecture was changed in this adjudication. Stage A remains held.