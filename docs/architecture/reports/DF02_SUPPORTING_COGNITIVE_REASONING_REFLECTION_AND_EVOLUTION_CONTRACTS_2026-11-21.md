# DF-02 — Supporting cognitive, reasoning, reflection and evolution contracts

**Date:** 2026-11-21  
**Candidate source baseline:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor source baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

> **Scope:** This report closes source inspection of a further set of candidate-branch divergent paths. It compares the pre-PR-#97 candidate with the unmerged donor implementation; it does not claim the candidate previously integrated these donor mechanisms and later lost them.

## 1. Reasoning must preserve disputed-evidence and confidence semantics

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/reasoning.cpp` | `feec78b2e8a1f2b0b58733fd509e4e5a750258fc` | `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1` |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | `a7119afd091e045d6294aa1b15c20de349ed6a1c` | `ceb6d471b3283f4a89fe243ac3c9e79f52f137a2` |

Candidate reasoning treats every premise as authoritative for deduction, including disputed beliefs. It derives conclusion confidence from causal-link strength alone and returns confidence 1.0 for an internally consistent premise set even if the premise evidence is low-confidence. Donor reasoning excludes disputed beliefs from the authoritative premise map, propagates the minimum confidence across the causal chain, and reports zero confidence when no authoritative premise exists. It also decodes causal-link sides through the typed codec rather than the candidate's local key=value parser.

The registered reasoning suite falls from 33 donor assertions to 19 candidate assertions. This is a substantive evidence-quality gap: contradictions remain evidence, but must not silently become authoritative premises.

## 2. Reflection must not mistake missing experience for certainty

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/reflection.hpp` | `435e03f8f03f74cb910338ab4ab1264e4eaf085c` | `5d9e11d7529f35445adbd23209914f6363548186` |
| `core/cpp/src/reflection.cpp` | `06f34e20f35aad535a2c606b3669b2127ef7a480` | `fe7dd1fada300300673b90caffa128384c65bde1` |

Candidate reflection initializes uncertainty to zero and coherence to one. With no beliefs and no resolved predictions, it returns uncertainty 0 and coherence 0.5, and does not say that experience is insufficient. Donor reflection sets uncertainty to 1 when the belief set is empty and coherence to 0 when there is no evidence. It keeps contradiction pressure separate from confidence, counts disputed beliefs, and records affective calibration error/learning pressure/observation count as metacognitive measurements.

This is directly relevant to the developmental starting state: absence of evidence must not be interpreted as evidence of competence or certainty. The donor's fixed appraisal coefficients and thresholds remain subject to separate validation; no coefficient is adopted by this report.

## 3. Planning and intent consume learned outcomes and continuous affective context

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/planning.hpp` | `303731d3ac52362ec86afdb482a5567c3b38a8ff` | `2bc6fc8a6bc4649da475f71f112a9fa3fd2b3610` |
| `core/cpp/src/planning.cpp` | `aab022b7cbc06f380413395757d590b56a1f3a20` | `9fcc2317e5acf0bfc24865a89eb9a54b80f8a80a` |
| `core/cpp/include/jarvis/core/intent.hpp` | `1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f` | `d9d926db40a3361f8354a42051106ab2b00b3c77` |
| `core/cpp/src/intent.cpp` | `4283a4255284c51257df6bad12734782f2a6cde9` | `9707d5b6da4ddede4dfc99d52f30e7cdc7eed032` |

Candidate planner receives goal, threat, uncertainty, resource and deadline context only. Donor adds valence, arousal, affective uncertainty, tension and stability as continuous appraisal dimensions. It modulates utility, reversibility and risk weighting without directly selecting or rejecting an action. Intent selection also consumes learned goal outcome momentum and offers a continuous affect-aware appraisal path. Donor intent treats only active goals as committed intent; candidate also selects pending goals. That status-boundary difference must be aligned with goal activation semantics, not silently copied.

The donor planner's weights and intent coefficients are fixed parameters, not learned facts. They are evidence of the required interface and mechanism integration, not an automatic adoption recommendation. No stimulus-to-emotion or emotion-to-action mapping is introduced by this report.

## 4. Cognitive workspace and action assessment omit feedback context

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/cognitive_workspace.hpp` | `b015d44e332ea2511d29e607495714d0b982d44e` | `e002025dd69183311b41afa9d57c2b0780b7f7f8` |
| `core/cpp/include/jarvis/core/action_model.hpp` | `6a3b1720d5b58630faf320ba1e3c082cb417b7a9` | `a4e67038e57eb7637e53a532b8da62f2d0f68727` |

Candidate workspace stores observation, memory, beliefs, causal links, predictions, reasoning, goals, plan, decision context, decisions, action assessments, intent, strategy and reflection. Donor additionally carries structured perceptual representation, affective state/appraisal, attention and action execution results. Candidate ActionAssessment lacks the developmental context associated with the decision; donor carries it forward so observed consequences can train the same representation/context that produced the action.

These are integration-contract fields, not proof that every donor subsystem is correct. The candidate's action-model architecture suite is 11 assertions in both snapshots, so no test-count regression is claimed for that suite; its current coverage simply does not demonstrate the donor's additional context propagation.

## 5. Adaptation retains only long-run error in the candidate contract

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/adaptation.hpp` | `9a2bb897a120f7585286481a6138dc9cb767ac30` | `dec808ad879c9d1e7afc3adb3ae777ee611fadb7` |

Candidate AdaptiveMetric stores estimate, mean_error and observation count. Donor also stores recent_error and consecutive_surprises, explicitly derived from ordered outcome-journal replay. These fields allow the learner to distinguish a short-term regime change from a single noisy observation. The broader adaptation behavior/test reduction is already recorded in the cognitive-runtime/memory/association/adaptation report; this section pins the missing metric contract.

## 6. Evolution history, orchestration and compensation require idempotent durable evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/evolution_history.cpp` | `4c023ab4a726efb07f563c2b5425b824e19aeee9` | `e394042ba7fc6db85e4663722f735918aa1ce7fb` |
| `core/cpp/src/evolution_orchestrator.cpp` | `efd55281ba7d2edf95c6a9f6537ed2944022617e` | `c913ff0f42fc4647605376579b3f343b5c12c387` |
| `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` | `f902abfc65d705e15b6b9c8690f8e023f55afacc` | `289e4dd74ad6646d0fd9c2b77645722c2aa3f3fe` |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | `e06441d23685093a3c533498a09adf3a8baf5914` | `c1af30f84f03d87d151fe3c5fbfd89ef39fbe34e` |

Candidate EvolutionHistory appends repeated experiment/parameter/action records; donor treats an identical repeat as already recorded, preventing retry duplication. Candidate orchestrator can proceed from an improved experiment to adoption after attempting to record evaluation; donor explicitly refuses adoption if the winning experiment's evaluation was not durably accepted. Donor also executes canary evidence after adoption and reports rollback/retention state. The donor orchestrator accepts an explicit trial configuration; candidate constructor silently uses the default.

Donor adoption journal stores the proposal's current/proposed values, expected gain, proposal confidence, minimum improvement and isolation status. It adds compensation transitions `restore_pending` and `restore_adopted` for failures after persistence. Donor controller adds Brain-facing validation, replay, adoption, compensation, canary-preview and rollback lifecycle methods. The focused action-feedback/evolution-adoption report already establishes the wider candidate safety/attestation gap; this report adds the exact supporting journal/history/orchestrator contracts.

## 7. Process-isolation child path must be async-signal-safe after fork

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/src/process_isolation.cpp` | `eac7a12fafe36b6c5f463ad0a41caa3bb835a61c` | `8bb621fc986b4957f079bfdf99f4a1038949bc72` |

Candidate constructs and allocates its `std::vector<char*>` argument array in the child after `fork()`. If the parent is multithreaded and another thread held an allocator lock at fork time, the child may deadlock when it allocates. Donor prepares `argv` before fork and uses the prepared array in the child, explicitly avoiding non-async-signal-safe allocation in the post-fork child path. This is a concrete process-safety difference additional to the previously recorded missing isolation attestation and fail-closed adoption gaps.

## 8. Knowledge evidence type boundary

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/knowledge.hpp` | `50eb1113a4569c3de05489c421d1cabb1437733d` | `3da0d2059331af405bbb0ba98c61308ead99c405` |
| `core/cpp/src/knowledge.cpp` | `25ecf822e6132f576266c1f86a964a227c7fb75f` | `21de8abbcd4426cb4ead70cb089e7d7c4ed0e81a` |

Candidate uses the generic `Evidence` type; donor uses `KnowledgeEvidence` for source reliability assimilation. The arithmetic and update behavior in `KnowledgeModel::assimilate` and `score_source` are otherwise the same. This is recorded as an API/type-boundary clarification, not a behavioral learning regression.

## 9. Evidence-based disposition

This report adjudicates the above supporting contracts and adds the reasoning/reflection, planning/intent, workspace/action-context, adaptation, evolution-history/orchestration and process-isolation findings to the focused DF-02 record. It does not authorize copying donor code or adopting its fixed coefficients. The candidate branch's 76 divergent paths are not all equivalent in significance: some are substantive missing feedback/safety contracts; some are additive context fields; and the knowledge evidence rename is a typed API boundary with unchanged update arithmetic.

No source, CMake or runtime file was modified. DF-02 remains OPEN pending the remaining path-by-path semantic and duplicate-owner reconciliation and Director-only source-baseline/retirement/non-adoption decisions.
