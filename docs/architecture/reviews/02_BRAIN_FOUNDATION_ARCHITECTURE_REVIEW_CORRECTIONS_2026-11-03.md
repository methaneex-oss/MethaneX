# PR #173 Architecture Review Corrections — 2026-11-03

**Status:** Builder corrections submitted; independent re-review pending  
**Reviewed baseline:** PR #173 commit `bd2f6f2d38e874aea015e2cc5de3c1a8d2b0f688`  
**Reviewed document blob:** `46c6a9f761de8d4413117686179f89690357adcb`  
**Corrected branch:** `architecture/brain-foundation-planning-20261103`  
**Governing research baselines:** PR #171 reviewed package HEAD `b05434758ad4fe72815503f89bd5d2990ccb658b`; accepted PR #172 HEAD `d7d676b79dbf3269f7fd3ebdb4363a6df19f255d`.

This record documents the Builder's response to the Independent Review's three blocking findings. It is separate from the main architecture document so that the Reviewer can inspect each correction, rationale and exact evidence without relying on claims in the proposal itself.

## 1. F-01 — Minimum affective processing and global modulation

**Finding:** The reviewed proposal described valuation but did not explicitly allocate foundational affective processing, its cross-capability influence, or the unresolved relationship between SYS-01, SYS-05, SYS-06 and SYS-08.

**Correction made:**

1. Expanded the responsibility heading and definition to explicitly include affective processing as foundational, not wholly deferred.
2. Distinguished minimum affective appraisal from advanced affective sophistication:
   - Initial: evaluate significance in relation to goals, risk, uncertainty and relevant internal conditions.
   - Acquired development: improve differentiation, calibration and context sensitivity, including learned modulation across attention, memory, learning and decision formation.
3. Specified that affective appraisal may influence attention, memory encoding/retrieval, further evaluation and alternative/goal prioritization, while not establishing facts, granting permission or dictating action.
4. Explicitly prohibited fixed emotional and behavioural mappings as substitutes for acquired appraisal.
5. Recorded SYS-06 as proposed and unresolved, not mandatory. Its existence, placement, scope and contracts remain open; no endocrine-inspired implementation was selected.
6. Clarified the SYS-05 and SYS-08 relationships: SYS-05 owns defined operational/homeostatic regulation; SYS-08 supplies compute/storage/network/device/runtime substrate; neither owns Brain affective meaning. If SYS-06 is later justified, its relationships and authority boundaries require separate governance and specification.
7. Added capability acceptance and cross-capability scenarios, including context-sensitive appraisal and operation when SYS-06 is absent.

**Exact corrected architecture references:**
- Section 4.6, lines 236–252: foundational affective appraisal, acquired sophistication, cross-capability interactions, SYS-05/SYS-06/SYS-08 boundaries and anti-hardcoding constraint.
- Section 7, lines 363 and 365: SYS-06 unresolved status and SYS-08 substrate responsibility.
- Section 7, lines 370–372: cognitive state ownership and division of recovery responsibility.
- Section 9, lines 431 and 442: initial versus acquired affective capability and advanced affective development.
- Section 11, line 486: affective capability acceptance criterion.
- Section 11.1, lines 502–504: appraisal scenario, SYS-06-absent scenario and SYS-08 failure scenario.
- Section 12, lines 524, 526–527: proposed minimum affective appraisal, unresolved SYS-06 and SYS-08 boundary decisions.

**Why this resolves the finding:** The Brain now explicitly owns minimum cognitive affective appraisal and its interaction with other cognitive responsibilities. Advanced affective dynamics remain developmental. SYS-06 is not smuggled into the design as a mandatory endocrine subsystem; SYS-05 and SYS-08 retain their distinct operational and substrate responsibilities.

## 2. F-02 — Experience-acquired goal formation

**Finding:** The reviewed proposal covered supplied-goal processing and evaluation but did not clearly establish how the Brain develops the capacity to form candidate goals from experience.

**Correction made:**

1. Separated initial goal processing from experience-acquired goal formation.
2. Initial capacity is limited to receiving, representing, tracking, evaluating and revising supplied goals, constraints and alternatives, while distinguishing supplied goals from internally formed candidate goals and distinguishing goals from intentions, plans, decisions and authorized actions.
3. Defined experience-acquired goal formation as a developmental capacity to generate candidate goals from interpreted experience, changed circumstances, discrepancies between expected and observed outcomes, internal conditions, and consequences of prior goals/actions.
4. Explicitly stated that these are possible sources for candidate formation, not fixed triggers or prescribed objectives.
5. Required candidate goals to be evaluated for evidence, relevance, feasibility, uncertainty, risk, conflicts, constraints and expected consequences; candidates may be revised, deferred, suspended or abandoned.
6. Required lineage for why a candidate goal arose and what experience changed its priority.
7. Distinguished acquired priorities/preferences from preloaded behavioural mappings.
8. Added an acceptance criterion and an end-to-end scenario for traceable candidate-goal formation and revision/abandonment after disconfirming evidence.

**Exact corrected architecture references:**
- Section 4.6, lines 236–243: initial goal processing and experience-acquired candidate-goal formation.
- Section 9, line 431: initial versus experience-acquired goal capability.
- Section 11, line 486: goal-formation acceptance criterion.
- Section 11.1, line 501: candidate-goal formation scenario with lineage, constraints and revision/abandonment.
- Section 12, line 525: proposed architectural decision distinguishing acquired goal formation from supplied-goal processing and external authorization.
- Section 13, line 546: unresolved evidence question for distinguishing genuine acquired goal formation from a hardcoded objective generator.

**Why this resolves the finding:** Goal formation is now an explicit intended developmental capability, not inferred from goal evaluation or user-supplied objectives. The architecture specifies the capacity and evidence obligations without initializing particular goals, motivations, preferences or fixed objective-generation triggers.

## 3. F-03 — SYS-08 embodiment and computational substrate boundary

**Finding:** The reviewed external-system table omitted SYS-08, leaving unclear how cognitive state ownership relates to compute, storage, networking, devices, runtime, persistence and operational recovery.

**Correction made:**

1. Added SYS-08 to the external responsibility table with its substrate availability, constraints, failures and recovery status.
2. Defined Brain requests to the substrate as cognitive persistence/read needs, bounded resource requirements and operational needs through future defined contracts.
3. Preserved the distinction: SYS-01 owns semantic content, provenance, version meaning and cognitive consistency; SYS-08 owns/provides the operational substrate.
4. Distinguished an infrastructure acknowledgement that bytes were stored or a process restarted from a successful cognitive state transition.
5. Divided recovery responsibilities conceptually among SYS-08 (substrate availability/recovery), SYS-05 (permitted lifecycle coordination), SYS-07 (integrity/security assessment) and SYS-01 (validation of recovered cognitive identity, lineage, consistency and epistemic status).
6. Stated that infrastructure failures must not be reinterpreted as external-world events, prediction outcomes, memory absence or learning signals without independent evidence.
7. Added a capability acceptance criterion and failure scenario.
8. Explicitly deferred storage technology, database, runtime topology and infrastructure implementation.

**Exact corrected architecture references:**
- Section 7, line 365: SYS-08 in the external-system responsibility table.
- Section 7, lines 370–372: cognitive/substrate ownership split, persistence semantics and recovery division.
- Section 11, line 489: substrate-boundary acceptance criterion.
- Section 11.1, line 504: storage/runtime interruption scenario.
- Section 12, line 527: proposed SYS-08 responsibility decision.

**Why this resolves the finding:** The Brain remains the authority for the meaning and validity of cognitive state while SYS-08 supplies operational resources and persistence. The architecture does not select a storage or runtime technology or conflate infrastructure health with cognitive evidence.

## 4. Review-to-correction trace

The architecture corrections were applied to the existing PR and existing document, not by replacing the proposal with a new architecture.

| Commit | Change |
|---|---|
| `add9f61dc8ca1dd9301283696f0de47b723f1467` | Addressed affective processing, goal formation and SYS-08 substrate boundary findings in the existing architecture document |
| `db968026037706bc9a745c7f0170489c9d66db99` | Clarified affective and goal capability allocation, including initial/acquired distinction and capability acceptance scenarios |
| Current correction commit | Further clarified SYS-06's conceptual relationship with SYS-01, SYS-05 and SYS-08 without selecting an endocrine-inspired implementation |

The final exact document revision and blob are recorded in the Builder's handoff comment and PR head. Line references above are for that final revision and must be rechecked if the document changes again.

## 5. Scope and integrity check

- Existing PR #173 and its architecture document were revised; no replacement proposal was started.
- PR #171 and PR #172 baselines remain unchanged.
- No runtime source, tests, dependencies or build configuration were changed.
- No runtime tests, builds or benchmarks were run.
- No algorithms, concrete schemas, APIs, databases, frameworks, model providers, runtime/deployment topology or implementation tickets were selected or created.
- No merge or deployment was performed.
- This record does not self-approve the corrections. The Independent Reviewer must independently inspect the exact corrected PR head and issue a new verdict.
- Brain implementation and detailed mechanism engineering remain unauthorized.

**Builder status:** F-01, F-02 and F-03 have been addressed in the architecture proposal. **Independent clearance remains pending.**
