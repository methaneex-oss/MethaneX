# PR #174 Follow-on Review Corrections — F-02 and F-03 — 2026-11-11

## 1. Status and provenance limitation

**Target PR:** #174  
**Branch:** `spec/brain-mechanism-specification-20261103`  
**Parent accepted planning baseline:** `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Current pre-correction PR head:** `be46b3858102c31022128522c4b3506aad4dff8a`  
**Current specification blob before correction:** `b366564b3f68e674ae5f5f9fc5a6c90d8b4f454d`

The original follow-on review is now available to the Builder as the seven-page document `PR174_Independent_Technical_ReReview_Builder_Handoff.docx`, supplied by the Project Director on 2026-11-14. The Project Director confirmed that the historical shared-conversation URL opened and displayed the original review. The report records the reviewed PR #174 HEAD as `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, the historical accepted planning baseline. It does not review the current corrected proposal at `9502989ffae91c00ba0a8568ab5296925fa9f27b` or the Builder correction commit now being prepared. The report's document does not identify the reviewer by model/person; this record therefore does not attribute it to xAI or claim a qualifying independent-review identity based solely on the filename/title.

The exact finding titles and acceptance criteria below are taken from the supplied report. The report states F-02 is HIGH / confirmed and F-03 is MEDIUM / confirmed specification weakness. Its scope is specification-level with bounded source verification; it explicitly does not claim runtime correctness, runtime tests, or implementation authorization.

- **F-02 — Missing explicit contextual language and operator-intent grounding (HIGH):** specify contextual utterance/communicative-intent interpretation, reference resolution, speech-act distinctions, speaker/participant attribution, commitment ownership and lifecycle, explicit versus inferred intent, uncertainty/clarification, direct versus quoted/untrusted content, and interaction continuity.
- **F-03 — Downstream reasoning integration is not sufficiently enforceable (MEDIUM):** make material downstream influence an observable acceptance obligation; require BM-04 to evaluate candidate claims, BM-05 to receive relevant implications without surrendering prediction ownership, BM-08 to use qualified reasoning where relevant, invalidated conclusions to trigger reconsideration, and rejected/unsupported conclusions not to silently influence downstream decisions.

This report addresses those known requirements conservatively. It does not claim that the missing original report has been recovered or that every original acceptance criterion is known.

## 2. F-02 — Contextual language and operator-intent grounding

### 2.1 Gap addressed

The prior BM-02 specification already requires multiple interpretations, contextual assumptions, evidence lineage and uncertainty. However, it does not explicitly define contextual language/utterance interpretation and operator-intent hypothesis formation as a first-class responsibility within that mechanism. The absence of explicit treatment leaves room for an implementation to collapse language into literal text matching or fixed phrase-to-intent rules.

### 2.2 Correction

BM-02 remains the owner of interpreted representations. No additional independent cognitive authority is introduced.

BM-02 must distinguish at least these conceptual layers where applicable:

1. **Acquired utterance/evidence:** the original content and its source, role, time and acquisition context.
2. **Literal/semantic interpretation:** candidate meanings supported by linguistic content.
3. **Reference and discourse interpretation:** candidate resolution of pronouns, ellipsis, deixis, shared entities, prior turns and conversational state.
4. **Pragmatic interpretation:** candidate communicative function or operator-intent hypothesis, with supporting and contradicting contextual evidence.
5. **Uncertainty and alternatives:** unresolved readings, assumptions, confidence meaning and conditions that would discriminate among them.

These are conceptual distinctions, not a mandatory fixed taxonomy or five separate models. They must not be collapsed into a deterministic phrase-to-intent table.

### 2.3 Required behavior

- Interpret an utterance in relation to its acquisition context, speaker/source role, relevant conversation history, active task, shared referents and current state.
- Distinguish what was literally said from what the system infers the speaker intends.
- Treat operator intent as a provisional, evidence-bearing hypothesis, not a fact merely because a phrase resembles a familiar command.
- Preserve multiple plausible readings when context does not discriminate among them.
- Use clarification when ambiguity materially changes the interpretation, requested outcome or downstream consequence.
- Incorporate corrections and later context as new evidence; revise the interpretation without rewriting the original utterance.
- Preserve provenance and uncertainty when a language model or other interpretation provider contributes a candidate reading.
- Treat quoted, reported, hypothetical or untrusted text as content to interpret, not automatically as an instruction from the current operator.
- Keep inferred intent separate from authority: understanding that an operator wants an action does not grant permission to perform it.

### 2.4 Ownership and interaction

- BM-01 preserves the original utterance/evidence and acquisition context.
- BM-02 owns contextual linguistic, referential and pragmatic interpretations and their alternatives.
- BM-03 supplies relevant conversational/episodic context with retrieval provenance.
- BM-06 supplies active context and may allocate further interpretation when ambiguity or importance warrants it.
- BM-12 reasons over the candidate interpretations, context and assumptions without converting a conclusion into an accepted belief.
- BM-08 owns the resulting goal/request/intent state after evaluating the qualified interpretation.
- Governance remains separate from cognitive intent and continues to authorize or deny consequential action.

### 2.5 Acceptance scenarios added

- **L1 — Context-dependent reference:** the same pronoun or abbreviated phrase has different referents in two contexts; the interpretation follows the evidence-bearing context rather than a fixed phrase mapping.
- **L2 — Ambiguous operator intent:** one utterance supports two materially different intended outcomes; both remain candidates and clarification is requested before consequential commitment.
- **L3 — Indirect request:** an indirect or incomplete utterance is interpreted using relevant prior turns and task context, while literal content and inferred intent remain distinguishable.
- **L4 — Correction:** the operator corrects an interpretation; the original utterance remains immutable, the interpretation is revised, and downstream dependencies are reconsidered.
- **L5 — Quoted/untrusted content:** text that contains imperative language but is quoted or attributed to another source is not silently treated as an instruction from the current operator.
- **L6 — Authority separation:** a correctly inferred operator intent still cannot bypass the external authorization boundary.

## 3. F-03 — Reasoning results must materially influence downstream cognition

### 3.1 Gap addressed

The current BM-12 specification already defines provisional conclusions, premise/assumption lineage, uncertainty, alternatives, contradictions and owner-specific boundaries. Section 6.3 also describes BM-04, BM-05 and BM-08 consuming qualified reasoning results. The correction makes this a mandatory, testable downstream contract rather than an interaction description that could be implemented as one-way publication or logging only.

### 3.2 Correction

A material BM-12 result must be published as a structured, provenance-bearing reasoning outcome. At minimum it must carry:

- reasoning objective and intended scope;
- conclusion or explicit unresolved result;
- epistemic status and uncertainty/support meaning;
- premise and assumption lineage;
- relevant alternatives, contradictions and counterexamples;
- evidence provenance and temporal/contextual limits;
- dependency versions and invalidation conditions;
- owner(s) to which the result is routed for evaluation;
- consumer disposition: accepted for use, qualified, rejected, deferred, or returned for more evidence.

A downstream consumer must demonstrate what it did with the reasoning result. A message delivered, event emitted, record stored or callback invoked is not evidence of integration.

### 3.3 Required consumer behavior

- **BM-04:** evaluates candidate claims for belief commitment/revision; it may accept, qualify, dispute, defer or reject a candidate. BM-12 never commits the belief.
- **BM-05:** evaluates relevant reasoning implications for association/causal hypotheses and scoped predictions; it retains the reasoning result's uncertainty and does not treat explanation as verified causality.
- **BM-06:** may use the reasoning result to adjust focus or request further processing, with the reason and uncertainty retained.
- **BM-08:** may use qualified conclusions and alternatives in candidate-goal, plan and decision evaluation; unresolved alternatives must remain visible where they materially affect the choice.
- **BM-10:** monitors omitted evidence, overreach, contradiction and calibration and may request re-reasoning.
- **BM-11:** tracks dependencies and marks affected derived state stale when a premise, assumption, context or upstream owner-state version changes.
- **BM-09:** may evaluate reasoning-strategy changes only against later outcomes, counterexamples, transfer and regression evidence.

No consumer may silently promote a provisional conclusion to an accepted fact, suppress a material alternative, or bypass its own state-ownership and governance responsibilities.

### 3.4 Acceptance scenarios added

- **R1 — Qualified result affects belief evaluation:** a provisional conclusion with explicit uncertainty is delivered to BM-04; BM-04 records a qualified candidate and does not silently commit it as certain.
- **R2 — Alternatives affect planning:** two materially different explanations remain plausible; BM-08 evaluates the downstream plan against both or requests discriminating evidence rather than consuming only the first result.
- **R3 — Causal boundary:** an explanatory conclusion is routed to BM-05; BM-05 retains it as a causal hypothesis until appropriate evidence and prediction/outcome evaluation support stronger status.
- **R4 — Dependency invalidation:** a premise or assumption changes; BM-11 marks dependent reasoning conclusions and downstream state stale and triggers targeted reconsideration.
- **R5 — Consumer rejection:** a downstream owner rejects or qualifies a reasoning result; the disposition and rationale are retained and the reasoning episode remains inspectable.
- **R6 — No downstream integration:** a result is only logged and no relevant owner changes, evaluates or explicitly rejects it; the integration acceptance test fails.

## 4. Verification and scope

The new L1–L6 and R1–R6 scenarios supplement the existing foundational scenarios. They are specification-level acceptance obligations, not claims that runtime behavior or tests already exist.

The corrections are deliberately mechanism-level. They do not choose a language model, provider, algorithm, prompt format, schema, API, database, transport or deployment topology. They do not introduce hardcoded phrase-to-intent mappings or fixed learned goals.

## 5. Independent re-review and acceptance status

**Builder correction status:** F-02 and F-03 have explicit specification-level responses and additional acceptance scenarios in this correction pass.

**Independent status:** NOT RECHECKED. The original report's exact reviewed SHA and full acceptance criteria remain unavailable. The Independent Reviewer must inspect the exact corrected PR #174 revision, challenge these reconstructed responses, and state whether they satisfy the original findings or identify any additional conditions.

**Project Director status:** no new acceptance decision is implied. The earlier acceptance of PR #174 at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` remains a planning-baseline decision only. This correction revision must be separately reviewed and explicitly dispositioned before any implementation reliance.

No runtime code, tests, dependencies, build configuration, merge, rebase, retarget, deployment or implementation authorization is included.


## 6. Reconciliation against the recovered secondary finding record — 2026-11-11

The repository's `PR_174_FOLLOW_ON_REVIEW_PROVENANCE_RECOVERY_2026-11-06.md` preserves more detailed secondary recovery than was reflected in the initial correction summary. It records the finding titles, severity and requirement themes, while explicitly stating that the original reviewer report, complete rationale and inline annotations remain unavailable.

The recovered requirement themes are now mapped as follows:

| Recovered F-02 theme | Corrected specification response |
|---|---|
| Contextual intent | BM-02 §4.2 and scenarios 35–38 |
| Reference grounding | BM-02 discourse/reference interpretation and scenarios 35–37 |
| Speech-act and source attribution | BM-02 now explicitly distinguishes communicative-function hypotheses and attributes utterances/embedded claims to source/speaker where evidence permits |
| Uncertainty and clarification | BM-02 preserves alternatives and requires clarification when ambiguity is material |
| Trusted/untrusted content | BM-02 preserves quoted/reported source boundaries and does not elevate untrusted imperatives to operator instructions |
| Continuity across interaction | BM-02 now preserves active referents, unresolved interpretations, corrections and context across turns/interruptions, with temporal/provenance limits |
| Authority separation | BM-02 keeps inferred intent separate from authorization |

| Recovered F-03 theme | Corrected specification response |
|---|---|
| Material influence on authoritative downstream computation | BM-12 requires accepted reasoning results to retain an explicit dependency in the consuming owner's authoritative computation/state transition and to record the resulting owner-state/decision version |
| Explicit invalidation | BM-12 and BM-11 dependency tracking require affected downstream versions to be reconsidered when premises/assumptions change |
| Explicit rejection | BM-12 requires a recorded consumer disposition and rationale; silent discard is prohibited |
| End-to-end traceability | Scenarios 47–48 require exact reasoning artifact/version and resulting downstream state/decision version, plus invalidation/recomputation evidence |

The additional scenarios 47–48 supplement the existing 35–46 set. They are specification acceptance obligations, not evidence that runtime behavior has been implemented or tested.

**Builder reconciliation:** the earlier correction pass covered much of the recovered substance but did not explicitly name speech-act/source attribution, discourse continuity, or a traceable downstream state-version effect for accepted reasoning. Those omissions are now corrected in the current specification proposal.

**Status remains:** Builder correction submitted; Independent Reviewer re-review and Project Director disposition are outstanding. The original report and exact original reviewed SHA remain unavailable. This report is not a verbatim reconstruction and does not claim independent clearance or implementation authorization.


## 7. Reconciliation against the full 2026-11-14 independent technical re-review

The supplied report is the controlling source for the exact F-02/F-03 acceptance criteria. It identifies the historical PR #174 review target as `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, which is the accepted planning baseline. The corrected proposal was at `9502989ffae91c00ba0a8568ab5296925fa9f27b` when the Builder began this reconciliation. The report therefore establishes the findings against the historical baseline; it does not provide a verdict on the later corrected proposal.

### 7.1 F-02 exact obligations and Builder reconciliation

| Independent finding obligation | Current specification response |
|---|---|
| Contextual interpretation of utterances and communicative intent | BM-02 §4.2 and §9.I/K; interpretation is evidence- and context-sensitive, not phrase-table driven |
| Reference resolution across conversation, entities and memory | BM-02 inputs/requirements; BM-03 supplies retrieved context; scenarios 35–38 |
| Distinguish questions, instructions, suggestions, assertions and commitments | BM-02 requirement 14; scenarios 49 and 53 |
| Identify speaker and participant whose intent/commitment is represented | BM-02 requirement 15; BM-08 operational ownership; scenario 50 |
| Track commitment ownership and lifecycle across interactions | BM-02 requirements 17–19; BM-08 requirements 11–13; scenarios 51, 52 and 54 |
| Separate explicit intent from inferred intent | BM-02 requirements 16–17; scenario 51 |
| Preserve uncertainty and clarify/defer materially ambiguous intent | BM-02 requirements 16–17; scenario 36 and 51 |
| Distinguish direct operator instructions from quoted/retrieved/untrusted content | BM-02 requirement 13; scenarios 39 and 53 |
| Preserve conversational/task continuity | BM-02 requirement 18; BM-03 history; scenarios 38 and 52 |

### 7.2 F-03 exact obligations and Builder reconciliation

| Independent finding obligation | Current specification response |
|---|---|
| BM-04 evaluates and accepts, qualifies, disputes, rejects or defers candidate claims | BM-04 requirements 9–10; scenario 41 |
| BM-05 receives relevant implications without surrendering prediction/causal ownership | BM-05 requirements 11–12; scenario 43 |
| BM-08 uses qualified reasoning in relevant planning/decision work | BM-08 interaction contract and BM-12 routing; scenarios 42 and 47 |
| Invalidated conclusions trigger reconsideration of dependent computation | BM-11 dependency rules; BM-12 requirements 10, 16–17; scenario 48 |
| Rejected/unsupported conclusions do not silently influence downstream decisions | BM-12 requirements 14–17; Section 5.5 consumer contract; scenarios 45–48 |
| Prove material downstream effect rather than delivery/logging | Section 5.5; BM-04/BM-05/BM-08 consumer requirements; scenario 47 |

### 7.3 Remaining verification boundary

The Builder has translated the report's specification obligations into the current PR #174 proposal and added explicit acceptance scenarios. This is a Builder reconciliation, not independent confirmation that the correction is sufficient. The designated Independent Reviewer must inspect the exact corrected PR #174 HEAD, verify the mapping and identify any remaining gap. The report's bounded source-level observations are not runtime tests; no runtime implementation or test authorization is implied.

**Current Builder disposition:** F-02 and F-03 have been addressed at the specification-edit level in the current correction pass. They are **SUBMITTED FOR FRESH INDEPENDENT RE-REVIEW**, not independently cleared and not Director-accepted.
