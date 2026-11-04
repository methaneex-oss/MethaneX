# Brain Implementation Planning Run 02 — Repository and Capability Audit

**Run identity:** Run 02  
**Date:** 2026-11-03  
**Elapsed investigation window:** 13:32:52Z–14:03:22Z (30 minutes, 30 seconds)  
**Status:** Time-box elapsed; planning outcome BLOCKED pending baseline reconciliation  
**Governing specification:** PR #174, accepted HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Planning proposal:** PR #175, branch `plan/brain-implementation-roadmap-20261103`  
**Candidate implementation line:** PR #156, branch `integration/priority-one-20261031`  
**Candidate documentation HEAD:** `7fe212bbb0bd61116ea56581435e03b06c69b673`  
**Latest code-bearing parent:** `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**Scope:** Static source and repository evidence only. No runtime source, tests, builds, dependencies, workflows, branches or PR metadata were modified.

---

## 1. Executive result

Run 02 confirms that the repository contains meaningful developmental learning, affective appraisal, memory persistence, prediction feedback, action-consequence learning and integrated runtime work. It also confirms that the candidate implementation line does **not** yet satisfy the accepted 12-mechanism specification as an integrated Brain.

The primary blocker is not a lack of modules. It is that the accepted architecture and the accumulated implementation history have not been reconciled into one reviewable implementation baseline.

**Run disposition: NOT READY for implementation authorization.**

The following must happen before implementation planning can safely become implementation work:

1. Reconcile the accepted specification branch with the candidate implementation history.
2. Produce an exact implementation-to-specification ownership matrix for all 12 mechanisms.
3. Distinguish source presence, local tests, integrated capability evidence and persistent developmental-learning evidence.
4. Resolve the identified BM-12, BM-05, BM-08, BM-10 and transfer-evaluation gaps.
5. Obtain independent review and a Project Director decision on the reconciled baseline and plan.

This report does not authorize implementation, runtime tests, technology selection, merge or deployment.

---

## 2. Run-control and checkpoint integrity

The Project Director requested a 30-minute investigation with automated checkups every three minutes: ten checkpoints at 03, 06, 09, 12, 15, 18, 21, 24, 27 and 30 minutes.

### 2.1 Actual checkpoint execution

The automation service limited the run to three active scheduled tasks. Six checkpoint tasks were ultimately created and completed. The scheduler did not honor exact three-minute timing consistently; some started early, others late, and CP-04/CP-05 ran out of scheduled order.

| Checkpoint | Scheduled UTC | Actual start UTC | Actual completion UTC | Result |
|---|---|---|---|---|
| CP-01 | 13:35:52 | 13:36:32 | 13:37:04 | FAIL |
| CP-02 | 13:38:52 | 13:37:34 | 13:38:14 | FAIL |
| CP-03 | 13:41:52 | 13:42:45 | 13:43:17 | FAIL |
| CP-04 | 13:44:52 | 13:49:20 | 13:50:32 | FAIL |
| CP-05 | 13:47:52 | 13:48:35 | 13:49:35 | FAIL |
| CP-06 | 13:50:52 | 13:53:44 | 13:54:58 | FAIL |
| CP-07 | 13:53:52 | Not scheduled | Not run | NOT RUN |
| CP-08 | 13:56:52 | Not scheduled | Not run | NOT RUN |
| CP-09 | 13:59:52 | Not scheduled | Not run | NOT RUN |
| CP-10 | 14:02:52 | Not scheduled | Not run | NOT RUN |

The actual investigation reached the 30-minute time-box at 14:03:22Z. Only six of ten checkpoint tasks were completed. The three-minute automated supervision requirement therefore **FAILED**. The report does not represent six checks as ten, nor sequential checks as a reliable three-minute cadence.

### 2.2 Checkpoint decisions

- **CP-01 — FAIL:** PR #175 still identifies its previous artifact as Run 01; no Run 02 audit artifact existed at checkpoint time. Exact candidate source/ownership audit was not yet recorded in the planning PR.
- **CP-02 — FAIL:** Candidate implementation history is materially diverged from the accepted specification history. Baseline reconciliation is mandatory.
- **CP-03 — FAIL:** Mechanism ownership is explicit in the accepted specification but not demonstrated end-to-end in the candidate source. Some automated-report statements relied on the historical main audit; this report corrects those using exact candidate-line source inspection.
- **CP-04 — FAIL:** BM-12 memory-to-reasoning and inference-lineage obligations are not satisfied by the candidate data contracts.
- **CP-05 — FAIL:** BM-05 causal attribution, evidence lineage, prediction scope, assumptions and resolution conditions remain incomplete.
- **CP-06 — FAIL:** BM-06 active context, BM-08 candidate-goal formation and BM-10 corrective metacognition are not demonstrated as complete integrated capabilities; BM-07 is only partially adaptive.

No checkpoint authorized code changes or runtime verification.

---

## 3. Repository baseline reconciliation

### 3.1 Accepted specification line

- PR #174: `https://github.com/methaneex-oss/MethaneX/pull/174`
- Accepted HEAD: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`
- Branch: `spec/brain-mechanism-specification-20261103`
- This is the governing planning/specification baseline, not an implementation branch.

### 3.2 Candidate implementation line

- PR #156: `https://github.com/methaneex-oss/MethaneX/pull/156`
- Branch: `integration/priority-one-20261031`
- Actual PR HEAD: `7fe212bbb0bd61116ea56581435e03b06c69b673`
- Latest code-bearing parent: `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`
- PR remains open, draft and unmerged.
- Independent review/adversarial clearance and Priority One acceptance remain outstanding.

The current PR head is documentation-only. The inspected code-bearing parent is the correct source reference for implementation claims. Seven key source files were fetched at both SHAs; their blob identities matched exactly:
- `cognitive_cycle.cpp`: `989f4d154f07b31bcdab175aefbea6edd61eb930`
- `reasoning.cpp`: `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1`
- `causal_model.cpp`: `8b884ed11a1a019d0e52bf7f35b0295edcc912b0`
- `knowledge.cpp`: `c38e0909c220b450502b46fd4a145e63ab6d21a0`
- `goals.cpp`: `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`
- `intent.cpp`: `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032`
- `developmental_learning.cpp`: `c9a34d562fa1a20641530daba81bfdc1f3621fee`

### 3.3 Divergence

Comparing accepted specification HEAD `0811a59e...` with candidate PR #156 HEAD `7fe212bb...` returns:

- status: **diverged**
- candidate ahead of common ancestor: **1,429 commits**
- accepted specification ahead of common ancestor: **21 commits**
- merge base: `af09cf28d35e4a7b75c3c019e9f97893d8e19364`

The candidate is not a clean implementation branch created from the accepted specification lineage. It carries a large accumulated implementation/test/workflow history. The related feature commit `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25` is an ancestor of the candidate line; the candidate is 185 commits ahead of it.

PR #156's description contains older exact-SHA references. Current PR metadata is authoritative for its actual head; code claims must identify the code-bearing parent separately.

### 3.4 Required baseline decision

**Recommended path: retain PR #156 as a candidate and build a reconciliation matrix before deciding whether to rebase or reconstruct.**

Do not rewrite or rebase a large accumulated history before identifying which changes are required, duplicated, superseded, integration-specific or unrelated. The matrix must map each inherited change to:
- originating PR/commit;
- accepted BM mechanism and specification section;
- source files/symbols and call paths;
- authoritative state owner;
- tests and exact CI evidence;
- accepted, draft, unreviewed or unresolved status;
- external SYS/governance dependency;
- conflict, duplication or supersession risk;
- retain, adapt, exclude or replace recommendation.

The Project Director must decide the eventual implementation base after reviewing this evidence. PR #156 is not automatically accepted as the implementation base.

---

## 4. Candidate implementation-to-specification evidence

This is a bounded static audit of the candidate code-bearing parent `15d49e5f...`, not proof that all uninspected callers or runtime paths behave identically.

| Mechanism | Candidate evidence | Run 02 assessment |
|---|---|---|
| BM-01 Experience/provenance | `Brain::observe`, event validation, provenance verifier hooks, journaled events | Substantial intake and validation exists; host trust and journal authenticity remain external/unresolved |
| BM-02 Representation | Perceptual representation and feature extraction in `CognitiveCycle` | Present; alternative interpretation and semantic grounding need deeper exact-target audit |
| BM-03 Memory | Event journal, episodic records, learned tiers, `recall_ranked` | Persistent retrieval exists; ranking is structured attribute overlap, not demonstrated semantic retrieval; memories are not reasoning premises |
| BM-04 Belief/world state | Belief store, disputed flags, `WorldModel`, provenance-aware `KnowledgeModel` | Conflict handling improved; factual `KnowledgeAssessment` is not consumed by the inspected cycle to revise ordinary beliefs/plans |
| BM-05 Causality/prediction | `CausalModel::observe_transition`, `simulate`, sequence-aware prediction feedback | Real bounded learning and feedback exist; causal attribution, scope, assumptions, lineage and resolution conditions remain incomplete |
| BM-06 Attention | `AttentionModel::score/focus/reinforce/suppress` | Adaptive weights exist; active-context ownership, goal/memory competition, interruption and starvation control are not demonstrated |
| BM-07 Affective appraisal | `AffectiveStateModel`, `AffectiveLearningModel`, outcome calibration | Genuine parameter adaptation exists; structural coefficients/event-to-signal mapping remain fixed, and broad context-sensitive integration is incomplete |
| BM-08 Goals/intent/decision | Goal lifecycle, progress momentum, intent selection, planning | Existing goals can be reprioritized; candidate-goal formation from experience is not demonstrated |
| BM-09 Learning | Strategy learning, additive feature model, prediction feedback, evolution/replay | Real experience-dependent strategy and feature updates exist; transfer scope and cross-mechanism learning remain bounded |
| BM-10 Metacognition | `ReflectionModel::evaluate` computes uncertainty, prediction accuracy, appraisal calibration | Monitoring summaries exist; diagnose → corrective request → correction verification is not demonstrated |
| BM-11 Coordination/continuity | `CognitiveCycle`, `CognitiveRuntime`, journal replay and evolution integration | Significant integration exists; general dependency invalidation and coherent multi-owner recovery need further evidence |
| BM-12 General reasoning | `ReasoningProblem`, `ReasoningResult`, `ReasoningEngine` | Narrow inference exists; accepted general reasoning contract is not implemented |

### 4.1 BM-12: precise integration finding

Candidate source:
- `core/cpp/src/cognitive_cycle.cpp`, blob `989f4d154f07b31bcdab175aefbea6edd61eb930`
- `core/cpp/include/jarvis/core/reasoning.hpp`, blob `5c6f82797d4f5052ad5d71a25624de192a2c87d9`
- `core/cpp/src/reasoning.cpp`, blob `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1`

The cycle retrieves memories into `result.context.memories`, but constructs `ReasoningProblem` from beliefs, causal links and a step limit. Retrieved memories do not enter the reasoning premises.

`ReasoningProblem` does not contain explicit assumptions, question/scope, premise provenance, retrieved-memory references or dependency versions. `ReasoningResult` contains kind, validity, confidence, a free-form explanation and derived beliefs, but not premise-to-conclusion lineage, alternatives, counterexamples or unresolved premise dependencies.

Important correction to the historical source audit: reasoning is **not** wholly display-only in the candidate. Valid reasoning conclusions can feed forward simulation and prediction generation; prediction uncertainty then informs planning. This is partial downstream integration. It does not close the accepted BM-12 contract or give BM-12 authority to commit beliefs.

### 4.2 Knowledge and belief integration

Candidate sources:
- `brain.hpp`: blob `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe`
- `brain.cpp`: blob `93a10a5021a5775a3a239037cbb0b58a1e0c67a9`
- `knowledge.hpp`: blob `ae1adcffeeb090eb102c05156388bce7c030538f`
- `knowledge.cpp`: blob `c38e0909c220b450502b46fd4a145e63ab6d21a0`

The candidate separates incoming observation quality from empirical source calibration, supports host-verified provenance, retains conflicting claims as disputed, and records externally adjudicated source feedback with replay validation.

However, `KnowledgeModel::assess` is exposed through the Brain API but is not called by the inspected `CognitiveCycle` to weight ordinary factual belief revision or downstream planning. The cycle does use `knowledge_source("action_executor." + action.name)` to adjust action-executor reliability. That is a narrower operational reliability path, not end-to-end factual source trust.

### 4.3 BM-05: causal and prediction limits

Candidate source:
- `causal_model.hpp`: blob `a6bf02cf75c6f55fa47120c772aad9c77fa40cf1`
- `causal_model.cpp`: blob `8b884ed11a1a019d0e52bf7f35b0295edcc912b0`
- `cognition.hpp`: blob `92febfa5d5feab45de1a3a19fe37282852898e6c`
- `brain.cpp`: blob `93a10a5021a5775a3a239037cbb0b58a1e0c67a9`

The causal model learns from changed before/after belief transitions. A new link begins at strength 0.40; repeated matching transitions strengthen it by a bounded fraction of the remaining distance to 1.0. Failed predictions weaken matching links. This is genuine experience-dependent updating, not a static lookup table.

But the link does not preserve the exact experience lineage, intervention/action attribution, confounders, context scope or independent evidence count. Repeated observations are not distinguished from independent episodes in the causal link's simple observation count.

Prediction records support identity, sequence-aware resolution, confidence, error and limited concept context. The record does not preserve the full premise/assumption set, model revision, temporal applicability, expected observation conditions or explicit resolution criteria required by BM-05.

Action execution and outcome are partly separated: the action result distinguishes authorization, execution, verification and observed consequence, and the DLT-004 no-feedback control checks that an execution failure does not train feature utility. This is useful bounded protection, not a complete evidence-attribution contract.

### 4.4 BM-06/BM-07/BM-08/BM-10 limits

Candidate evidence:
- Attention header/source blobs: `bc3f97b79664e433fed5bca07b24a6b94dbec1d3`, `67def4987f4a49a852bd2e4c9760f05c2ee15216`
- Affective header/source blobs: `f63da2e0060938864bf434012d0b3b4d74fa5f29`, `563a61cd8f6440f78a084f76a799b2c84bdd6813`
- Affective learning header blob: `fa06043dc481336ba544247f365d37f5476a0651`
- Goals/intent source blobs: `afaedcfb0f2f68ff88b3a20e474fce04bb59815c`, `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032`
- Reflection source blob: `fe7dd1fada300300673b90caffa128384c65bde1`

Attention has adjustable salience weights and reinforcement/suppression, but the inspected focus path supplies novelty as a fixed 1.0 and does not demonstrate the complete active-context, goal competition, interruption/resumption and starvation contract.

Affective appraisal has genuine outcome-calibration learning and continuous state variables. Its initial weights, learning-rate structure, decay constants and state-combination formulas are fixed enabling structure. The issue is not simply that formulas exist; it is that broad context-dependent influence and lineage across memory, attention, goals, learning and reasoning remain insufficiently demonstrated.

Goal records can be created, activated, updated, completed or abandoned. Progress changes can adjust priority and outcome momentum. Intent selects among existing active goals; the cognitive cycle accepts a supplied goal ID, uses an existing active intent, or falls back to the first eligible goal. No candidate-goal generator from experience is demonstrated.

Reflection measures belief uncertainty, contradictions, prediction accuracy and affective calibration. The inspected model reports observations; it does not route targeted corrective work and verify whether the correction succeeded.

**Correction to the old-main audit:** The affective APIs are integrated in the candidate line's Brain header and build/test structure. The earlier source-level integration discrepancy observed on historical main must not be carried forward as a current candidate-line blocker.

---

## 5. Learning and transfer evidence

### 5.1 Candidate CI evidence

At candidate documentation HEAD `7fe212bbb0bd61116ea56581435e03b06c69b673`, GitHub reported four required workflows successful. The Brain Tests job log records **73/73 CTest tests passed**, including:

- cognitive cycle and runtime integration;
- memory and knowledge suites;
- reasoning architecture suite;
- learning/adaptation and evolution suites;
- affective and goal-outcome suites;
- developmental training environment;
- DLT-001, DLT-003 and DLT-004;
- DLT-002 persistence train/verify.

Relevant run identifiers inspected:
- Brain tests: `41174439423`
- Core verification: `41174439433`
- ThreadSanitizer: `41174439446`
- Native brain build and ASan/UBSan: `41174439557`

The 73/73 result is evidence for that exact candidate tree and its registered CTest suite. It is not evidence that every accepted BM contract is satisfied.

### 5.2 DLT-004 feature composition

Test source:
- `core/cpp/tests/dlt_004_feature_composition.cpp`
- blob `e486bedc813c1a70dc48b610133a147283e0d7ef`

The test runs five seeds, trains on multiple contexts, withholds one combination, tests a fresh-process restored Brain, verifies that execution failure without an observed consequence does not train feature utility, and checks that memory, affective updates and action-consequence predictions persist.

The learner is a small additive feature model: bias plus a sum of individual feature-value weights. It does not contain explicit feature-interaction terms. DLT-004 demonstrates a bounded held-out combination of independently useful features; it does not demonstrate arbitrary compositional reasoning or parity/XOR transfer.

### 5.3 JBP-004 unseen-combination challenge

The separate JBP-004 workflow was inspected at older commit `c6718cc7fb58b4fa4183bf8bc2402b7cdedc67b0`. Its job log shows:

- Seeds 17 and 29: familiar contexts passed 20/20; held-out parity combination scored 0/20.
- Seed 43: one familiar training context reached only 11/20 against a 12/20 minimum; held-out combination scored 0/20.
- Evaluation withheld outcome feedback.
- The challenge failed.

This failure predates the candidate's DLT-004 additive feature-composition work. JBP-004 is not registered in the candidate's 73-test CTest suite. Therefore, it is not valid to claim that PR #156 currently fails JBP-004, but it is equally invalid to claim that DLT-004 solved it.

**Required future evaluation:** after baseline reconciliation and separate runtime-test authorization, rerun the same JBP-004 challenge against the exact candidate implementation head. Preserve the parity challenge as a distinct test from additive feature composition.

---

## 6. Revised planning priorities

The previous PR #175 roadmap's first vertical slice—experience → memory → reasoning → belief—remains a plausible capability target, but it is not ready to be assigned to a code branch until repository reconciliation is complete.

The next planning work should proceed in this order:

### Gate A — Repository reconciliation

Produce the branch/PR/commit and file-level divergence matrix described in Section 3.4. Identify the exact implementation base that the Project Director is willing to accept for future work. Do not rebase or reconstruct history before the matrix is reviewed.

### Gate B — Implementation-to-specification ownership matrix

For each BM-01 through BM-12, record:
- authoritative owner in accepted specification;
- candidate source files/symbols;
- current call path;
- state/persistence owner;
- existing tests and exact evidence;
- gaps and overlapping/duplicated responsibilities;
- external SYS/governance dependencies;
- acceptance scenarios not yet demonstrated.

### Gate C — Epistemic and reasoning integration design

Design a coherent evidence path that addresses:
- source/provenance and knowledge assessment;
- evidence-sensitive belief/world-state revision;
- retrieved memory as a provenance-bearing reasoning premise;
- BM-12 assumptions, alternatives, contradictions, counterexamples and inference lineage;
- BM-04 ownership of belief acceptance;
- BM-05 ownership of causal/prediction state;
- qualified downstream use by planning/decision.

Do not merge knowledge, belief and reasoning into one state owner.

### Gate D — Causal/prediction and developmental capability design

Define:
- causal hypothesis scope and evidence lineage;
- attribution and counterexample requirements;
- prediction assumptions, temporal scope and resolution conditions;
- experience-acquired candidate-goal formation;
- metacognitive corrective-work lifecycle;
- attention active-context and interruption/resumption;
- transfer tests that distinguish additive feature composition from interaction/parity generalization.

### Gate E — Independent review and Project Director decision

The Independent Reviewer must challenge the reconciliation matrix, ownership mapping, evidence claims, proposed sequence and verification design. Project Director acceptance of the planning package remains separate from implementation authorization.

No code or runtime tests are authorized by this report.

---

## 7. Final disposition

- **30-minute investigation time-box:** elapsed.
- **Three-minute automated checkpoint protocol:** failed; six of ten tasks completed, timing drift and concurrency limit documented.
- **Source investigation:** meaningful candidate-line audit completed for BM-03/BM-04/BM-05/BM-06/BM-07/BM-08/BM-09/BM-10/BM-12 and core integration paths.
- **Repository changes during Run 02:** none.
- **Implementation readiness:** not established.
- **Recommended next action:** prepare the baseline reconciliation matrix, with PR #156 retained as a candidate rather than assumed as the accepted implementation base.
- **Implementation authorization:** none.
- **Merge/deployment authorization:** none.

**The project must not proceed by treating 73 passing tests as proof that the accepted Brain architecture is implemented. It must proceed by reconciling ownership, closing the demonstrated integration gaps and proving persistent experience-dependent behavioral change.**

**Governing principle remains: ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**
