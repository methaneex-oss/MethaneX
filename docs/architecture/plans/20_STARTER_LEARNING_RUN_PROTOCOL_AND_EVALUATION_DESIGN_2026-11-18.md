# Starter Learning Run Protocol and Evaluation Design — 2026-11-18

**Status:** Non-operative planning artifact; proposed for review and Project Director disposition  
**Planning branch:** `plan/brain-implementation-roadmap-20261103` (PR #175)  
**Governing planning inputs:** PR #175 kickoff WP-00–WP-08; parallel-planning supplement; capability-to-scenario matrix  
**Governing principle:** **Engineer the mechanisms; let behavior be acquired through experience.**

## 1. Purpose

Turn WP-08 into a concrete, reviewable design for the first controlled learning runs. The target is not a finished assistant, broad autonomy, or a preloaded repertoire. It is evidence that an integrated set of existing and/or later approved mechanisms can acquire a bounded competency from experience and that this change persists and affects later behavior.

This protocol is planning only. It does not select an implementation baseline, donor, algorithm, model, framework, storage technology, schema, API or deployment topology. It does not authorize source changes, runtime builds, tests, training, or Stage A.

## 2. Learning claim to be tested

The minimum claim under test is:

> Given attributable experiences and an initially measured capability, the system forms and evaluates candidate updates through the appropriate mechanism owners; an accepted update persists across reconstruction and produces a measurable, justified change on later relevant experiences, without causing unacceptable degradation on unrelated or previously mastered cases.

The claim is deliberately narrower than general learning or intelligence. A passing result supports only the named capability, task distribution, conditions and tested revision.

## 3. Experimental phases

### R0 — Protocol and fixture integrity

- Freeze task definitions, scoring rules, exposure limits, hold-out partition and stopping rules before the first run.
- Separate training examples, validation examples and sealed evaluation examples by identity and provenance.
- Ensure fixtures do not contain answer labels or hidden target state that the system can read as ordinary experience.
- Record the exact software revision, configuration, environment, input corpus, randomization seed where applicable, and evaluator version for every run.
- Verify that reset/reconstruction procedures produce the intended starting state.

**Exit evidence:** an independently reproducible protocol package and proof that evaluation examples are not available to the learning path.

### R1 — Pre-training baseline

- Run the task suite before training and record per-case outcomes, uncertainty, evidence lineage, prediction quality where applicable, retrieval usefulness and failure classifications.
- Include positive, negative, ambiguous, contradictory, delayed-feedback and missing-evidence cases.
- Record both successful and failed behavior; do not tune the baseline after seeing sealed evaluation outcomes.
- Establish repeatability bounds so ordinary variance is not misreported as learning.

**Exit evidence:** frozen baseline results, per-case traceability and an explicit list of known limitations.

### R2 — Controlled experience exposure

Use staged batches rather than a single large undifferentiated corpus:

1. **Orientation batch:** simple, low-ambiguity experiences to establish the intake, representation and continuity path.
2. **Variation batch:** the same underlying task family under changed context, order, wording or relevant conditions.
3. **Counterevidence batch:** experiences that challenge an earlier interpretation or prediction.
4. **Delayed-outcome batch:** outcomes that arrive later or remain incomplete, requiring the system to preserve unresolved status.
5. **Conflicting-source batch:** attributable sources that disagree, requiring provenance and uncertainty to remain visible.
6. **Recovery batch:** interrupted, duplicated, malformed or partially unavailable experience delivery, testing continuity and recovery rather than rewarding false certainty.

The curriculum must not tell the system which belief, emotion, goal, causal relation or action to adopt. It supplies experiences and verifiable outcomes; the system must form and justify candidate changes through its mechanisms.

**Exit evidence:** exposure ledger, complete provenance, owner-decision records, rejected as well as accepted candidate updates, and no silent fixture leakage.

### R3 — Immediate post-exposure evaluation

- Re-run the baseline cases using the same scoring protocol.
- Compare per-case and aggregate outcomes; preserve uncertainty and confidence calibration rather than reporting accuracy alone.
- Inspect whether relevant memory was retrieved and actually consumed by downstream reasoning or prediction.
- Trace each accepted persistent update to its source experiences, affected state owner, approval decision and expected scope.
- Check whether unsupported generalization, contradiction collapse or deterministic stimulus-response shortcuts appeared.

**Exit evidence:** attributable before/after comparison and trace-level explanation of observed changes.

### R4 — Persistence and reconstruction

- End the run and reconstruct the system using the declared persistence/recovery procedure.
- Verify that accepted changes survive reconstruction and that rejected or incomplete candidates do not become authoritative state.
- Verify event lineage, owner-state consistency, dependency freshness and absence of incoherent partial multi-owner updates.
- Repeat selected post-training cases after reconstruction.

**Exit evidence:** reconstruction record, state-integrity checks and post-restart behavioral equivalence within declared tolerances.

### R5 — Sealed transfer and regression evaluation

Use evaluation cases withheld from all training and tuning.

- **Near transfer:** related tasks with changed surface form or context.
- **Compositional transfer:** combinations of previously encountered factors not presented together during training.
- **Boundary tests:** unrelated tasks where learned changes should not be applied.
- **Contradiction tests:** new evidence that should qualify, revise or invalidate a previously supported conclusion.
- **Negative transfer tests:** cases where overgeneralization would make performance worse.
- **Regression tests:** previously reliable capabilities and external-authority boundaries.

**Exit evidence:** sealed evaluation results, per-case transfer classification, negative-transfer analysis and regression disposition.

### R6 — Longitudinal replication

Repeat the exposure/evaluation cycle with a fresh experience sequence and independently reconstructed starting state. This checks whether the result is reproducible rather than a one-off artifact of ordering, fixtures or transient state.

**Exit evidence:** replicated effect with disclosed variance and no unexplained divergence in state lineage.

## 4. Measurement framework

Final metric definitions and thresholds must be selected during contract freeze, before results are observed. The evaluation report must include at least:

| Dimension | What is measured | Failure signal |
|---|---|---|
| Task competence | Correctness or utility on the defined task family | No improvement, unstable improvement or metric gaming |
| Prediction quality | Quality of predictions against resolved outcomes, including calibration where applicable | Better point accuracy with worse calibration or unresolved attribution |
| Evidence use | Whether relevant retrieved evidence materially affects downstream inference | Memory retrieved but ignored, or irrelevant memory dominates |
| Epistemic discipline | Preservation of uncertainty, provenance, alternatives and contradiction | Unsupported certainty or collapse of competing claims |
| Learning traceability | Link from experience to candidate, owner decision, persistent update and later effect | Unattributed or unauthorized state change |
| Persistence | Survival and validity after reconstruction | Lost, duplicated, corrupted or partially applied updates |
| Transfer | Improvement on sealed related cases | No transfer or unjustified broad generalization |
| Retention/regression | Preservation of unrelated and previously reliable capabilities | Catastrophic forgetting, interference or authority-boundary regression |
| Recovery | Behavior under delayed, missing, malformed and interrupted inputs | False outcome attribution or incoherent recovery |

No single aggregate score can conceal a critical failure in provenance, persistence, state ownership, recovery, or external authorization.

## 5. Controls against false learning claims

The run must be rejected as evidence of learning if any of the following occurs:

- desired answers, labels or target state are embedded in training fixtures in a way the system can directly read;
- evaluation cases leak into training, prompt construction, tuning or manual correction;
- a developer manually changes authoritative state between baseline and post-training without recording it as an intervention;
- the system reports a successful action without independently verified execution/consequence evidence;
- a transient cache or workspace projection is mistaken for durable state;
- prediction error directly mutates another mechanism's authoritative state without that owner's approval;
- a single success is presented as general competence;
- only aggregate accuracy is reported while uncertainty, negative transfer, failures or regression are omitted.

All interventions, resets, exclusions and evaluator changes must be logged.

## 6. Required trace for one claimed learned change

For each representative claimed change, the evidence package must reconstruct this chain:

1. Original experience identity, source, time, context and uncertainty.
2. Representation produced and distinction between observation and interpretation.
3. Memory retention and retrieval record, including applicability context.
4. Relevant belief/prediction or inference before outcome.
5. Observed outcome and its verification/attribution status.
6. Candidate update and its supporting/contradicting evidence.
7. Affected state owner(s), evaluation and approval/rejection decision.
8. Persistent state transition and recovery/reconstruction validation.
9. Later case where the changed state was relevant and materially influenced behavior.
10. Sealed evaluation showing the scope and limits of the effect.

If any link is absent, the report must narrow the claim accordingly.

## 7. Stop, containment and rollback criteria

Stop a run and preserve evidence if there is unauthorized state mutation, corrupted provenance, cross-owner partial commit, inability to reconstruct state, fixture leakage, unexplained evaluator drift, false execution/consequence attribution, or a material external-authority boundary violation.

A candidate update that causes negative transfer, unstable behavior or regression must be eligible for owner-controlled containment or reversal under the approved recovery contract. The evaluation must verify that containment itself does not destroy unrelated valid state.

Concrete rollback mechanisms and implementation details remain for the relevant state owners and approved architecture; this document does not prescribe them.

## 8. Required deliverables before a run can be authorized

- Frozen protocol, task-family definitions and sealed evaluation partition.
- Exact approved source baseline and reproducible environment manifest.
- Accepted architecture/specification revisions and owner-boundary map.
- Per-work-package contracts and integration dependencies.
- Baseline, post-exposure, reconstruction, transfer and regression report templates.
- Explicit thresholds, stop rules, intervention log and independent evaluation plan.
- Project Director authorization for the specific runtime/training execution.

## 9. Current disposition

This protocol makes WP-08 more concrete and gives implementation planning a testable first learning objective. It remains non-operative. Gate A is NOT CLEARED; Gate B capability acceptance is NOT PASSED; no implementation baseline or donor has been selected; the Documentation Foundation is not yet accepted; runtime implementation and starter-training execution remain unauthorized.

**Next planning action:** reconcile this protocol against the exact final accepted architecture/specification and scenario set, then obtain independent challenge and Project Director disposition before converting any work package into executable work.
