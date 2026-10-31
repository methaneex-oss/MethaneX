# Developmental Brain Plan and Engineering Handoff

**Status date:** 2026-10-30  
**Active implementation line:** PR #148 — `fix/learning-contradiction-resolution-after-dlt003`  
**Observed PR head at documentation time:** `7b9f50e588bb677882a7b8212cd84d41791b8053`  
**Purpose:** Preserve the developmental objective, current evidence, known gaps, work order, and mandatory rules for builders, testers, and reviewers.

This document is the controlling engineering handoff for the developmental-brain work. Future work must continue from the existing architecture and current branch/PR state. Do not restart the project, replace its architecture with a generic agent/chatbot, or divert into unrelated feature work.

## 1. Non-negotiable objective

**Engineer the mechanisms; let behaviour be acquired through experience.**

We are building an early developmental learning system — a primitive learning brain, not a finished adult intelligence and not a chatbot wrapped around an LLM. The objective is to make existing cognitive mechanisms cooperate so that experience produces durable changes in internal models and later behaviour.

Do not pursue apparent progress by adding isolated modules, hardcoded stimulus-to-response mappings, large fixed knowledge tables, or demonstrations that merely replay pre-programmed answers.

The intended developmental cycle is:

1. Experience acquisition and validation.
2. Representation and contextualisation.
3. Memory encoding, retrieval, and consolidation.
4. Belief formation and evidence-sensitive revision.
5. Prediction and prediction-error processing.
6. Internal valuation / affective appraisal and attention.
7. Association and causal learning.
8. Decision and action selection.
9. Outcome observation and consequence attribution.
10. Learning from outcomes, retaining the change, and adapting future behaviour.

The mechanisms must form a connected loop. A component existing in code is not evidence that the brain has learned.

## 2. Definition of the minimum developmental capability

The first target is narrow, demonstrable general learning — not human-level intelligence or unrestricted AGI.

A developmental capability is not accepted until the system can:

- acquire a relationship from experience in an environment it was not given a hand-authored answer for;
- retain the acquired information and retrieve it in a fresh process after restart;
- represent uncertainty and competing evidence rather than blindly overwrite prior beliefs;
- revise beliefs when sufficiently informative contradictory evidence arrives;
- transfer a learned relationship to a materially different, previously unseen context when relevant structure is shared;
- use the learned information to change a later decision or action;
- observe the consequence, update its internal model, and preserve the behavioural change after restart.

The strongest proof is an end-to-end sequence: learn in context A, restart, encounter unfamiliar context B, transfer the relevant relationship, make a changed decision, observe the result, update, restart again, and demonstrate the retained change. Tests must include controls to rule out hardcoded answers, leakage, memorised exact scenarios, and insertion-order artefacts.

## 3. Current baseline — evidence versus judgement

The following is a provisional engineering assessment, not a claim that every subsystem has been exhaustively audited. Ratings are maturity estimates, not test coverage percentages.

| Mechanism | Provisional maturity / 10 | Main concern |
|---|---:|---|
| Experience ingestion and validation | 7 | Coverage and integration across unfamiliar modalities |
| Internal representation | 5 | Contextual and relational representation depth |
| Episodic memory | 6 | Retrieval usefulness and developmental linkage |
| Persistent memory / replay | 6 | End-to-end behavioural continuity proof |
| Memory retrieval | 5 | Retrieval must influence live reasoning and decisions |
| Belief formation | 6 | Evidence quality and provenance |
| Belief revision | 6 | Conflict handling and calibrated resolution |
| Evidence aggregation | 5 | Dependence/correlation between observations |
| Source reliability | 3 | Reliability is not yet a coherent learned trust model |
| Uncertainty management | 5 | Calibration and uncertainty propagation |
| Prediction | 5 | Contextual predictive use |
| Prediction-error learning | 5 | Transfer from error to later choices |
| Association learning | 5 | Generalisation beyond exact co-occurrence |
| Causal learning | 4 | Robustness, interventions, and transfer |
| Attention | 5 | Whether selection improves learning efficiency |
| Affective / internal valuation | 4 | Whether appraisal causally informs learning and action |
| Threat appraisal | 3 | Calibration and downstream consequences |
| Decision-making | 3 | Learned knowledge must alter decisions |
| Planning | 3 | Multi-step consequence-sensitive planning |
| Action and consequence learning | 4 | Attribution and closed-loop evidence |
| Self-model | 4 | Accuracy and useful control implications |
| Strategy learning | 4 | Reliable outcome-based adaptation |
| Developmental learning | 3 | Cross-mechanism developmental progression |
| Evolution / adaptation | 3 | Safe, evidence-based improvement rather than proposal generation alone |
| Generalisation / transfer | 3 | Unseen-context transfer remains a critical proof gap |
| Cross-mechanism integration | 3 | The complete experience-to-behaviour loop is not yet established |

Earlier bounded developmental evidence (JBP-003, PR #107 at commit `92cce78985f2630f62a6e0beb49ac725623d7d85`) reported 20/20 acquisition and fresh-process recall, 56–57/60 adaptation under changed context, and 60/60 unchanged-context control. This was a bounded demonstration on an earlier isolated test line. It is not proof that the current PR #148 contains equivalent coverage, broad transfer, or an integrated general-learning brain.

## 4. Immediate work order — do not reorder without evidence

Work in this order. A later item must not be used to avoid an unresolved earlier dependency.

### Priority 1 — Make source reliability a real, evidence-grounded mechanism

**Why this is first:** The current knowledge layer stores a source-level reliability metric, but its assessment logic does not use that metric. The public `score_source(source, correct)` method has no observed production call site in the inspected code/search results. The current metric also mixes two conceptually different quantities: the reliability/confidence attached to an incoming observation and the source's empirically demonstrated accuracy.

**Verified code observations at PR #148 head `7b9f50e...`:**

- `core/cpp/include/jarvis/core/knowledge.hpp` defines `KnowledgeEvidence`, `KnowledgeMetric`, `KnowledgeAssessment`, and `KnowledgeModel`.
- `core/cpp/src/knowledge.cpp` updates `sources_[source].reliability` by averaging incoming `KnowledgeEvidence.reliability`.
- `KnowledgeModel::score_source` also updates that same average using a boolean correctness outcome.
- `KnowledgeModel::assess(key)` groups claims by distinct source and value, but selects/assesses using distinct-source counts; it never reads `sources_[source].reliability`.
- `ClaimEvidence` stores source, key, value, and observation count, but not per-claim evidence quality or calibrated source-trust snapshots.
- The current implementation separates incoming observation quality (`reliability`) from empirical source calibration (`empirical_accuracy`, `calibration_observations`).
- `KnowledgeModel::assess(key)` now applies calibrated trust to each source's claim weight after at least three explicit calibration outcomes. Repeated observations by one source do not add independent source weight, and conflicting values remain disputed rather than being erased by a weighted lead.
- `Brain::record_knowledge_source_feedback(...)` now appends a `knowledge_source_feedback` journal event linked to a specific earlier claim sequence, key, value, source, and evaluator. Replay validates that link, rejects self-evaluation and malformed feedback, deduplicates feedback, and calls `KnowledgeModel::score_source`.
- The caller remains responsible for evaluator independence and ground-truth provenance. The evaluator string is audit metadata, not cryptographic proof or independent truth verification.
- `core/cpp/tests/knowledge_memory_phase3_suite.cpp` covers separation of the metrics, calibration weighting, repetition, and conflict preservation. These model-level tests do not alone prove the Brain feedback journal lifecycle or fresh-process restoration.

**Required engineering work:**

1. Separate *observation quality/confidence* from *empirical source trust*. They are not interchangeable. Do not keep averaging both into one scalar.
2. Define what constitutes a valid correctness outcome for a source. It must be grounded in later evidence/outcomes with provenance; do not mark a source correct merely because another source repeats the same claim.
3. Trace and implement the complete lifecycle: source evidence arrives → claim is retained with provenance and evidence quality → independent/validated outcome becomes available → source calibration updates → assessment can consult calibrated trust → state survives journal replay/restart.
4. Keep evidence dependence explicit. Repeated claims from one source are not independent corroboration. Correlated sources must not be treated as independent merely because their source strings differ. Do not claim statistical independence unless the data supports it.
5. Preserve uncertainty and active disputes. A reliability-weighted score must not silently turn a weak plurality into truth. Ties, close evidence, insufficient calibration, stale evidence, and conflicting outcomes must remain unresolved or explicitly qualified.
6. Ensure low-trust evidence is not discarded automatically: it may still be informative, especially when it is novel or independently corroborated. Trust should affect evidential weight, not erase observations.
7. Make calibration and assessment deterministic under replay and independent of unordered-map iteration or event insertion artefacts.
8. Add focused tests for uncalibrated sources, calibration from verified outcomes, correct/incorrect mixed histories, different source trust levels, repeated same-source observations, correlated sources, ties, reversals, malformed feedback, and restart reconstruction.
9. Trace every caller and persistence pathway before changing APIs. Update documentation with actual semantics and limitations.

**Priority 1 acceptance gate:** Demonstrate that a source's empirically learned reliability changes the *quality/weight/uncertainty* of its evidence in a later assessment; that this effect is based on traceable feedback rather than the incoming confidence field; that repetition/dependence cannot manufacture corroboration; and that the same assessment is reconstructed after restart. The test must also show that conflicting evidence is not automatically erased by a weighted majority.

Do not declare Priority 1 complete because a metric exists, a unit test checks arithmetic, or the assessment merely returns a weighted number.

### Priority 2 — Connect learned knowledge and belief state to decisions

Trace how assessed knowledge, uncertainty, conflict, and memory retrieval reach candidate generation, action selection, planning, and execution. Prove that changing experience changes a later decision for the right reason. Do not insert a hardcoded rule for the test scenario.

### Priority 3 — Strengthen generalisation and transfer

Demonstrate structural transfer across unfamiliar contexts, including negative controls and adversarially similar contexts where transfer should *not* occur. Prevent exact-scenario memorisation and label leakage.

### Priority 4 — Close the developmental feedback loop

Connect decision → action → observed consequence → attribution → prediction/belief/strategy updates → future decision. Prove that the changed behaviour survives restart and is not just a transient score update.

### Priority 5 — Improve evidence-dependence modelling

Distinguish repeated observations, shared-origin sources, genuinely independent corroboration, and contradictory evidence. Avoid treating source-count as a statistical posterior.

## 5. Mandatory builder instructions

- Continue from the current repository and branch state; inspect the actual latest head before editing.
- Work on the active PR/branch unless an explicit reason requires a separate branch. Do not silently switch the base or stack.
- Implement the highest unresolved priority. Do not add unrelated features or change direction because a new idea is easier.
- Before editing, inspect relevant source, callers, tests, journal/replay behaviour, and API contracts.
- Make the smallest coherent architectural change that closes the identified mechanism gap.
- Never replace learning with hand-authored mappings, scenario-specific answers, or fixed response tables.
- Do not remove uncertainty or conflict merely to make tests pass.
- Do not claim persistence without a fresh-process replay test.
- Do not claim transfer without unseen-context tests and leakage controls.
- Do not claim integration because separate unit tests pass.
- Report exact files, commit SHA, implementation changes, known limitations, and tests actually run. Clearly distinguish tests run by CI/another actor from tests run locally.
- Do not merge without explicit owner authorization.

## 6. Mandatory tester instructions

Testers must try to falsify the developmental capability, not merely confirm the happy path.

For Priority 1, include at minimum:

- repeated weak observations from one source versus independent corroboration;
- distinct source identifiers that share one underlying origin;
- source calibration from both correct and incorrect outcomes;
- a source that is initially reliable and later degrades, and one that improves;
- stale calibration versus fresh calibration;
- high-confidence but historically poor source versus lower-confidence but historically accurate source;
- two or more competing values, ties, near-ties, and reversals;
- a source that provides conflicting values over time;
- malformed, missing, duplicated, or untraceable correctness feedback;
- restart/replay equivalence, including no double-scoring on replay;
- downstream assessment/decision impact without a hardcoded scenario response.

Retain exact commit SHA, commands, test output, CI run identifiers, and failures. A green build alone is not proof of learning.

## 7. Mandatory reviewer instructions

Review the mechanism, not the narrative. Independently verify:

- whether source trust and observation quality are separated;
- whether correctness feedback is genuinely grounded and attributable;
- whether feedback can be circular or self-confirming;
- whether source identities and common provenance are modelled honestly;
- whether confidence aggregation is mathematically and semantically defensible;
- whether disputes and uncertainty survive ties, reversals, and restart;
- whether replay is deterministic and idempotent;
- whether the learned assessment actually reaches decisions;
- whether tests prove the claimed behaviour rather than implementation details.

Request changes for hardcoded mappings, false independence, ungrounded source scoring, silent conflict deletion, unpersisted calibration, or claims exceeding the evidence.

## 8. Current PR state and verification boundary

At the time this document was authored, PR #148 was open, draft, unmerged, and reported head `7b9f50e588bb677882a7b8212cd84d41791b8053`. GitHub had reported successful runs for Brain ThreadSanitizer, Native Brain Build, Brain CI, and JARVIS Brain Tests on that head. These are CI-reported statuses; they are not a substitute for independent review or the expanded behavioural acceptance tests above.

PR #148 currently addresses accumulated-evidence conflict handling in the world model and belief dispute synchronization. This work is relevant foundation, but it does not close Priority 1 or establish the complete developmental learning loop.

**This plan remains active until the acceptance gates are met with reproducible evidence.** Update this document when a priority is completed, the active head changes materially, or evidence changes the assessment. Do not silently replace the objective or reorder priorities.


## 9. Implementation progress — 2026-10-30

**Current implementation checkpoint:** PR #148 head `80a17978682ab47dd01e168aef682f678f524394`.

A first bounded Priority 1 code change has been committed:

- `KnowledgeMetric.reliability` now represents incoming observation-quality history only.
- Empirical source calibration has separate `empirical_accuracy` and `calibration_observations` fields.
- `score_source` updates empirical calibration without modifying observation-quality statistics.
- Claims retain an aggregated observation-quality value separately from source calibration.
- `KnowledgeModel::assess` applies calibrated trust to each source's evidence weight only after at least three explicit calibration outcomes; before that it uses a neutral prior.
- Repeated observations from one source do not add additional independent source weight.
- Conflicting values remain disputed even if one side has a higher weighted evidence score.
- The knowledge unit suite was updated for separation, weighting, repetition, and conflict-preservation semantics.

**Important incomplete work — Priority 1 is NOT complete:**

- `score_source` still has no verified production feedback call path.
- The API accepts a boolean outcome and source string; it does not itself prove evaluator independence, outcome provenance, or that feedback refers to a specific claim.
- Calibration is currently in-memory model state reconstructed only if some caller replays scoring calls; a journal event lifecycle has not yet been implemented.
- No fresh-process persistence test for calibration has been run.
- No claim is made that source calibration currently changes live Brain behaviour through ordinary observations.
- The new unit test changes have not been run by this builder in this checkpoint; they require the designated tester/CI to execute on the exact head.

**Next mandatory Priority 1 implementation step:** add a validated, provenance-linked journal feedback event that references a specific prior claim event, records the evaluator identity and correctness outcome, rejects self-evaluation and malformed/duplicate feedback, and rebuilds calibration deterministically during replay. Only after this is implemented and independently tested can the source-calibration pathway be considered operational.

The current code is a model-layer foundation, not a completed operational mechanism. Do not describe Priority 1 as closed.


## 10. Repository write-path troubleshooting — 2026-10-31

The GitHub connector write path is operational. A diagnostic UTF-8 blob creation succeeded. The earlier failed multi-object commit attempt was not evidence of a repository permission outage: the workflow incorrectly assumed the normalized `fetch_commit` response exposed the raw Git tree object. It does not; it returns normalized commit metadata and diff fields. The attempted tree creation therefore lacked a verified base-tree SHA.

**Supported safe write procedure:** use `fetch_file` to obtain the current file blob SHA, then use `update_file` with the exact repository, path, complete new content, commit message, blob SHA, and target branch. For multi-file Git-object writes, obtain a valid base-tree SHA from an endpoint that actually returns it; do not infer it from normalized commit metadata. After any write, fetch the updated file and inspect the PR head SHA before proceeding.

No production code change is implied by this troubleshooting note. The source-calibration feedback lifecycle remains an implementation task and must not be reported as complete until production code, replay tests, restart tests, and CI evidence exist.


## 11. Trusted evaluator boundary — 2026-10-31

A fail-closed host trust boundary has been added to the source-calibration feedback path:

- `Brain` accepts an optional set of trusted knowledge-evaluator identities at construction.
- The feedback API rejects evaluator identities not present in that host-supplied set.
- Journal replay applies the same allowlist check, so feedback from an evaluator not trusted by the current host configuration is not applied.
- The default constructor has an empty allowlist and therefore fails closed; deployments must explicitly provide trusted evaluator identities before calibration feedback can be recorded or replayed.
- Tests configure three trusted evaluator identities, reject an untrusted identity, restore calibration with the same trusted configuration, and verify that replay without the trust configuration does not apply calibration.

**Security boundary and limitation:** the allowlist is a host configuration trust anchor, not cryptographic identity authentication. The application integrating `Brain` must ensure that only authenticated, authorized adjudicators can invoke the feedback API and that its trusted-evaluator configuration is protected. An evaluator name in a journal is still metadata; this change does not provide signed feedback, prove independence, or establish ground truth. Journal tamper resistance remains a separate concern.

**Verification status at this entry:** source and test changes are committed on PR #148. CI for the exact resulting head was queued when checked. Do not treat the implementation as accepted until the focused suite and full relevant CI complete, and an independent reviewer verifies the host integration and replay boundary.


## 12. Priority 1 continuity correction and latest builder checkpoint — 2026-10-31

**Latest builder commit:** `7abdd7ba51da784c33aafa9d4b540e59f17f0a8b`.

The earlier entries in sections 9–11 are historical checkpoints, not descriptions of the current implementation. In particular, section 9's statement that no production feedback path exists was superseded: the current branch contains `Brain::record_knowledge_source_feedback`, a journal event, replay validation, deduplication, host-configured evaluator allowlisting, and a fresh-process restoration test in `knowledge_source_feedback_suite.cpp`.

### Work completed in this checkpoint

- Added a focused regression to `core/cpp/tests/knowledge_memory_phase3_suite.cpp` for a source whose empirical accuracy falls to zero after three negative adjudications.
- The test checks that its evidence weight falls from 0.9 to 0.45 while its observation remains present.
- The same test introduces a conflicting independent claim and verifies the assessment remains `disputed`, exposes no selected candidate, and reports both sides. Low trust reduces evidential weight; it does not erase experience or decide truth.
- The changed test file was fetched again from the repository at the resulting commit and its inserted assertions were verified present.

### Current Priority 1 limitations — explicitly not closed

1. **Evaluator identity:** the allowlist checks a caller-supplied string. It is not caller authentication. The host must enforce the identity boundary; a cryptographically authenticated capability/signature design is not implemented.
2. **Truth and independence:** an authenticated/allowlisted adjudicator assertion is not objective ground truth. The current feedback path does not independently prove the correctness outcome. Multiple distinct source or evaluator strings are not proof of statistical independence or separate underlying provenance.
3. **Journal integrity:** replay validates linkage and configured trust but does not cryptographically authenticate feedback records against journal tampering.
4. **Calibration sample threshold:** the current three-outcome minimum is a conservative activation gate, not a statistically justified universal sample size. It must not be described as proof of accuracy. Calibration evidence may be correlated; current code does not model that dependence.
5. **Downstream effect:** `KnowledgeModel::assess` returns evidence status and weight, but this checkpoint has not established that assessed knowledge changes candidate generation, planning, or action selection in the live brain.
6. **Runtime verification:** this builder has not executed the C++ suite locally. The new test is committed but has no exact-HEAD CI result at the time of this checkpoint.

### Tester handoff — read-only

On exact HEAD `7abdd7ba51da784c33aafa9d4b540e59f17f0a8b`:

- Run `jarvis_knowledge_memory_phase3_suite`, `jarvis_knowledge_source_feedback_suite`, and `jarvis_developmental_brain_integration_suite`.
- Run full CTest and configured ASan/UBSan and ThreadSanitizer workflows.
- Verify the new degraded-source test and the existing improved-source test.
- Attack feedback replay with altered outcomes, forged allowlisted evaluator strings, duplicate/conflicting adjudications, missing trust configuration, and restart.
- Test correlated sources sharing one origin; do not count distinct strings as independent corroboration without provenance.
- Trace whether assessment status/weight actually influences downstream decisions. Report any absence as a gap, not as a passing capability.
- Return exact commands, exact SHA, run IDs, logs, and counterexamples. Do not edit.

### Reviewer handoff — read-only, after tester evidence

On the same exact HEAD:

- Verify the source-quality / empirical-accuracy separation and the new low-trust regression.
- Inspect whether three adjudication outcomes are a justified calibration gate or merely an arbitrary constant.
- Inspect feedback identity, adjudication provenance, replay integrity, and trust-configuration lifecycle.
- Explicitly assess the unsupported independence assumption across source identifiers.
- Trace assessment into decisions and actions; do not equate an API returning a weighted assessment with learned behaviour.
- Confirm that disputed evidence remains unavailable as a selected candidate and that calibration does not erase the underlying experience.
- Return PASS or REVISE with file/line evidence. Do not edit or merge.

**Priority 1 remains open.** This checkpoint strengthens one falsifiable property of the knowledge mechanism; it does not complete source reliability, verification, safe knowledge acquisition, or general intelligence. Continue the existing priority order and developmental objective without redesigning the architecture.


## 13. Priority 1 source-provenance completion work — 2026-10-31

This entry supersedes the earlier identity-only and source-independence limitations in sections 11–12 where the current implementation below provides a stronger mechanism. It does not erase the remaining ground-truth, storage-integrity, statistical-threshold, or downstream-integration limits.

### Implemented on the active PR #148 branch

- Added a host-supplied `KnowledgeProvenanceVerifier` callback. A source's `provenance_id` is used for independence only when the host verifier accepts the paired `provenance_attestation`. The verifier must be deterministic across restarts and authenticate the source-to-origin assertion.
- Added `KnowledgeProvenanceRequest` with source, claim key/value, provenance identifier, and attestation. Missing verifier, missing metadata, invalid attestation, or verifier exception yields unknown provenance; it never grants independent-origin status.
- Distinct source identifiers with the same verified origin contribute at most one origin weight. Evidence with no verified origin is grouped into one unknown-origin bucket and cannot create corroboration. Its best weight is exposed separately as `unverified_evidence_weight` and is excluded from the corroboration threshold. Corroboration now requires at least two distinct host-verified origins plus sufficient verified-origin weight.
- Added explicit `supporting_origins` and `conflicting_origins` to assessments while retaining source counts for auditability.
- Prevented a source's unknown-provenance copy from being counted again when that same source already has verified provenance for the same claim.
- Removed observation-count multiplication from WorldModel fact and relation support. Repetition remains auditable and updates mean quality, but a source cannot manufacture support by repeating a weak claim. Conflict resolution now requires one unique post-conflict alternative whose latest evidence reliability strictly exceeds the strongest competing alternative's mean; equal reliability remains disputed. Facts and relations use the same rule.
- Added source-calibration drift tests (reliable source degrades and later improves) and a competition test where a lower-quality but empirically accurate source outweighs a high-quality but repeatedly incorrect source.
- Added conflict-boundary tests for lower reliability, exact ties, three competing alternatives, repeated reversals, and persistence after restart. A tie remains disputed until one alternative receives strictly stronger fresh evidence.
- Excluded provenance identifiers and attestations from learned world facts and feedback-eligible claim fields. A partial provenance pair is rejected before journal mutation.
- Changed missing observation-quality metadata from the fixed 0.7 fallback to neutral 0.5. Precedence is explicit `evidence_reliability`, then legacy `reliability`, then `confidence`, then neutral 0.5.
- Strengthened the feedback test verifier so its test attestation binds claim sequence, key, value, evaluator, and correctness outcome. Added reverse-order conflicting-adjudication replay coverage.
- Added restart coverage proving that verified provenance reconstructs with the same host verifier and fails closed when the verifier is absent.

### Required exact-head verification

Run these focused suites first, then full CTest and the configured sanitizer workflows:

- `jarvis_knowledge_memory_phase3_suite`
- `jarvis_knowledge_source_feedback_suite`
- `jarvis_developmental_brain_integration_suite`

Adversarial checks must include source-order permutations, two source names sharing one origin, distinct verified origins, invalid/missing origin attestations, mixed verified and unknown evidence from one source, restart with and without the verifier, altered feedback payloads, and conflicting adjudications in both journal orders.

### Remaining boundaries

1. **Host trust root:** the core provides the verifier boundary; the embedding application must supply a real cryptographic verifier and protect its trust configuration. The test callback is only a deterministic test fixture, not production cryptography.
2. **Ground truth:** a valid attestation proves that an authorized evaluator made a claim-specific assertion; it does not prove the assertion objectively true. The host adjudication process must ground correctness in independent evidence.
3. **Journal integrity:** feedback replay is attestation-checked, but the journal as a whole is not cryptographically authenticated against offline deletion, reordering, or other tampering.
4. **Calibration sample gate:** the three-outcome activation minimum remains a provisional conservative gate, not a statistically universal sample-size guarantee.
5. **Downstream behaviour:** whether calibrated knowledge changes planning/action selection remains a separate Priority 2 integration requirement.
6. **Review status:** builder self-review is not independent review. Keep PR #148 draft and unmerged until exact-head CI and an independent reviewer/tester report are available.

**Priority 1 is not closed by this implementation checkpoint alone.** The source-provenance and neutral-default mechanisms are now implemented candidates; exact-head tests and independent adversarial review decide whether they are accepted.

## 14. Feedback replay hardening — 2026-10-31

**Implementation checkpoint:** PR #148, current builder head `9331b51b62f5b3772f6f76c3fb8a7c1dd5a12b9d`. This section records a source-audit correction; it is not an acceptance or completion claim.

- The non-const `Brain::memory()` accessor has been removed. Callers can inspect memory but cannot append journal events through a live `Brain` object while bypassing its validation and synchronization path.
- Added `Brain::import_legacy_memory_event` as the narrow supported import route for passive `observation`, `action_outcome`, and `action_attempt` history. It overwrites the imported source with `legacy_import` and rejects all control-plane event kinds, including feedback and evolution lifecycle events. The integration fixtures now use this route for passive legacy history; raw feedback-journal tampering is performed through a separate `Memory` writer only after the Brain instance is closed.
- The feedback test now simulates offline journal modification through a separate `Memory` instance after the original `Brain` has closed, then verifies fresh-process replay. This keeps the adversarial journal-tampering test without leaving a mutable storage escape hatch in the runtime API.
- Authenticated feedback is deduplicated by claim sequence and key, not by evaluator identity. Multiple trusted evaluator names cannot multiply the calibration count for the same claim.
- Replay scans all feedback records for the same claim. If any independently authenticated evaluators disagree on correctness, all adjudications for that claim are rejected regardless of journal order. Identical authenticated adjudications are applied once.
- The live API rejects a second authenticated adjudication for an already-adjudicated claim, regardless of evaluator. Invalid attestations do not reserve the claim or block a later valid submission.
- The focused feedback test now covers disagreement between different trusted evaluators, forged raw journal records, invalid-record non-poisoning, restart reconstruction, and calibration outcomes attached to distinct observation events rather than several fields from one event.

**Verification boundary:** these changes are committed, but they have not been accepted until all four required CI workflows complete successfully on the exact current HEAD and the source/test changes receive independent review. The host still supplies the actual feedback/provenance verifier; the repository test verifier is only a test fixture. The host must implement authenticated identity, key rotation/revocation, and a deterministic historical-verification policy. This change does not cryptographically protect the journal against offline file replacement, deletion, or reordering.


## 15. Integrated Priority-One audit checkpoint — 2026-10-31

**Integrated validation PR:** #156 — `integration/priority-one-20261031`  
**Code-bearing checkpoint:** `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`  
**PR state:** open, draft, unmerged.

### Additional adversarial corrections

A source-level audit of the combined knowledge, action-learning, and evolution-replay tree found two concrete replay/attribution gaps:

1. **Mismatched evolution rollback target.** During replay, an `evolution_rollback` event checked that its experiment was adopted but did not verify that the event's parameter key matched the parameter key stored on that experiment. A malformed/tampered event could therefore roll back a different adopted parameter while marking the referenced experiment rolled back. Replay now rejects the event before mutation unless the keys match. The integration suite creates two adopted parameters, injects a rollback with a mismatched experiment/key pair, restarts, and verifies neither parameter nor the referenced experiment history is changed.
2. **Feedback attestation omitted claim source.** The host verifier request previously bound claim sequence, key, value, evaluator, and correctness, but not the source whose reliability would be updated. The request now includes the actual source resolved from the referenced claim. The host verifier must bind this field too. A regression attempts to reuse an attestation for one source against a different source and verifies no calibration is applied.

### Exact-head verification

All four required workflows passed on code-bearing HEAD `15d49e5fdeb5723c475922ab78fb92f97c4b3b84`:

- Native Brain Build — PASS.
- Brain CI — PASS, including native and ASan/UBSan jobs.
- Brain ThreadSanitizer — PASS.
- JARVIS Brain Tests — PASS, including brain and sanitizer jobs.
- Both JARVIS CTest-bearing jobs report 73/73 tests passing.

These are exact-head CI results. No local C++ build is claimed.

### Remaining Priority-One acceptance work

Priority One remains **OPEN**. CI success is necessary but not sufficient. The following gates remain:

- Production cryptographic feedback and provenance verification; authenticated evaluator identity; protected trust configuration; key rotation/revocation; and deterministic historical verification across restart. The test verifier is not production cryptography.
- Cryptographic journal integrity against offline deletion, replacement, and reordering.
- Independent ground-truth adjudication. A valid evaluator attestation proves who made an assertion, not that the assertion is objectively true or statistically independent.
- A justified calibration activation/sample policy. The three-outcome minimum is provisional; stale-versus-fresh calibration behaviour still requires explicit adversarial coverage and a justified policy.
- Independent adversarial tester and reviewer clearance.
- The factual source-calibration path still lacks an end-to-end demonstration that calibrated knowledge changes belief/world-model weighting and downstream planning/action selection. The DLT-004 compositional action learner is a separate action-outcome learning path; do not conflate the two.

### Next execution order

1. Obtain independent adversarial tester evidence on the combined PR #156 exact head, including the new rollback-target and feedback-source-binding regressions.
2. Obtain an independent architecture/security review of the combined replay, provenance, evaluator trust, calibration and evidence-dependence boundaries.
3. Resolve all findings. Do not weaken assertions or turn known external integration requirements into implied passes.
4. Close Priority One only when the documented acceptance gate is demonstrated or the owner explicitly accepts a remaining host/storage boundary.
5. Then proceed to Priority Two: connect calibrated factual knowledge, uncertainty and memory retrieval to decisions, planning and action selection.

**Do not merge PR #156 or mark it ready for review without independent clearance and owner authorization.**


## 16. Calibration freshness hardening — 2026-10-31

**Implementation checkpoint:** branch `fix/knowledge-calibration-freshness-20261031`, stacked on the exact PR #158 head `4380fcbbdf4887b8332948083d000483d8f8d622`. This is a focused follow-up; it does not alter PR #156, #157, or #158.

### Change

- Added an explicit `KnowledgeCalibrationPolicy` with a configurable minimum number of adjudicated claims and maximum age measured in persisted brain events.
- Calibration outcomes are retained with their feedback event sequence. During knowledge assessment, only outcomes within the host-configured event-age horizon contribute to source trust.
- Lifetime calibration totals remain available through `KnowledgeMetric` for audit. They no longer imply that old outcomes remain active forever.
- A zero freshness horizon disables calibrated weighting. The default policy is therefore fail-closed: unless the embedding host explicitly chooses a horizon, source calibration does not alter evidence weights.
- The freshness clock is the persisted event sequence, not wall-clock time. This makes expiry deterministic across replay/restart and avoids dependence on machine clock skew. The policy horizon is a host configuration choice, not a hard-coded universal duration.
- Added a regression that proves three fresh adjudications increase evidence weight, ten later events age those outcomes out, the observation remains present at neutral weight, lifetime metrics remain auditable, and restart reconstructs the same stale result.

### Verification still required

- Run the focused `jarvis_knowledge_source_feedback_suite`, full CTest, ASan/UBSan, and ThreadSanitizer on the exact resulting commit.
- Independently review policy semantics, sequence overflow/boundary behavior, replay reconstruction, and the effect of event volume on freshness.
- The event-count horizon is a deterministic freshness mechanism, not a statistically justified universal threshold. The embedding host must select a horizon appropriate to its event rate and use case.
- This does not implement production cryptographic evaluator/provenance identity, protected key lifecycle, objective ground-truth adjudication, or cryptographic whole-journal integrity.
- This does not yet prove that factual calibration changes downstream planning/action selection.

**Priority One remains OPEN.** Do not mark this change accepted until exact-head CI and independent tester/reviewer evidence are available.
