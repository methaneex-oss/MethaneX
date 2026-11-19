# JARVIS Capability-to-Acceptance-Scenario Traceability Matrix — 2026-11-18

**Document status:** Non-operative planning artifact; prepared under the 2026-11-17 Project Director exception for bounded planning work in parallel with Documentation Foundation closeout.  
**Repository:** `methaneex-oss/MethaneX`  
**Planning branch:** `plan/brain-implementation-roadmap-20261103`  
**Planning source HEAD before this addition:** `a01899b4e3b3ee9c6e5e3d83fedd0f22ce2b3891` (PR #175)  
**Scenario sources:** (1) historical accepted PR #174 planning baseline `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`, file `docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md`, blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1` (34 scenarios); (2) current corrected PR #174 proposal `c34472354e4122fc1d78dc25bf45d81f1eb4dc69`, same file, blob `cfdda9e6e7070cd5533b076e9bd77c2904694a32` (54 scenarios). Exact §9 comparison confirms scenarios 1–34 are textually identical; scenarios 35–54 are additions in the current proposal.  
**Architecture context:** PR #173 current proposal HEAD `a96af5b18d3a1d580ff56cff6191240893bceeb5`; the latest recorded Independent Reviewer assessment is PARTIALLY CLEAR against an earlier exact revision.  
**Authority:** Scenarios 1–34 are accepted only within the historical PR #174 baseline at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`. Scenarios 35–54 are additional requirements in the current corrected proposal and remain proposed/unaccepted pending exact-revision review and Project Director disposition. The scenario owner, increment and evidence mappings in this matrix are non-operative Builder planning classifications, not a new approval of the current proposal, not proof of scenario passage, and not implementation authorization.

---

## 1. Purpose and controlling interpretation

This matrix provides a capability-oriented verification map for the 54 scenarios in the current PR #174 proposal while preserving their distinct authority histories. It is intended to prevent scenario coverage from being mistaken for module coverage: a scenario passes only when the relevant cross-mechanism behavior and its evidence are demonstrated.

**Scenario authority reconciliation:** The historical accepted PR #174 planning baseline at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` contains 34 scenarios. The current corrected proposal at `c34472354e4122fc1d78dc25bf45d81f1eb4dc69` contains 54. A direct comparison of the exact §9 scenario text confirms that IDs 1–34 are textually identical across the two revisions; IDs 35–54 are additional scenarios in the current proposal. Therefore, IDs 1–34 retain their historical accepted-baseline status, while IDs 35–54 remain proposed/unaccepted. This scenario-text equality does not mean the entire specification documents are identical or resolve the F-02/F-03 gaps recorded against the historical baseline. The current corrected specification still requires its own exact-revision review and Project Director disposition.

The owner, increment and evidence-class assignments below were cross-checked against the current proposed specification. They remain Builder planning classifications, not a change to accepted ownership authority.

The planning increments referenced below are defined in `17_PARALLEL_NON_OPERATIVE_IMPLEMENTATION_PLANNING_SUPPLEMENT_2026-11-17.md`:
- **I0** — contract and authority readiness.
- **I1** — evidence, memory and continuity spine.
- **I2** — representation, belief revision and memory-supported reasoning.
- **I3** — causal hypotheses and prediction lifecycle.
- **I4** — attention, appraisal and metacognitive regulation.
- **I5** — experience-grounded goals, intent, planning and decisions.
- **I6** — cross-mechanism learning and developmental adaptation.
- **I7** — integrated Brain verification and controlled starter-training readiness.

These are planning groupings, not an implementation order or authorization to activate work packages.

## 2. Scenario traceability matrix

| Scenario | Required observable capability (condensed from the source scenario) | Primary owners | Integrated increment(s) | Minimum evidence class |
|---:|---|---|---|---|
| 1 | Retain competing interpretations; update relative support without rewriting acquisition | BM-01, BM-02, BM-04 | I1, I2 | Ambiguity + later evidence + immutable acquisition lineage |
| 2 | Preserve observation/interpretation/belief distinctions through persistence and reconstruction | BM-01, BM-02, BM-03, BM-04, BM-11 | I1, I2 | Persist/reconstruct; provenance and epistemic-status audit |
| 3 | Classify provider failure as capability failure, not external-event evidence | BM-01, BM-10, BM-11; provider capability boundary (SYS-08 only when substrate/network failure is evidenced) | I1, I7 | Injected provider failure; capability-unavailable status preserved; external-event truth remains unresolved |
| 4 | Retrieved prior episode materially changes later inference with traceable influence | BM-03, BM-12, BM-02 | I1, I2 | Paired inference with/without relevant memory; lineage comparison |
| 5 | Retrieved but irrelevant episode does not gain authority from retrieval alone | BM-03, BM-06, BM-12, BM-04 | I2, I4 | Relevant/irrelevant retrieval contrast; no unsupported premise use |
| 6 | Working-context eviction does not erase durable episodic history | BM-03, BM-06, BM-11 | I1, I4 | Eviction + durable retrieval after reconstruction |
| 7 | Contradictory evidence revises/qualifies belief and invalidates dependent state while retaining lineage | BM-04, BM-05, BM-08, BM-11 | I2, I3, I5 | Contradiction injection; owner revision + dependency invalidation trace |
| 8 | Repeated co-occurrence does not automatically become a universal causal rule | BM-05, BM-04, BM-12 | I2, I3 | Confounding/counterexample set; causal-status restraint |
| 9 | Similar predictions resolve independently | BM-05, BM-11 | I3 | Two prediction identities; independent resolution records |
| 10 | Late outcome resolves the correct prediction using event time and explicit conditions | BM-01, BM-05, BM-11 | I1, I3 | Delayed/out-of-order outcomes; event-time and resolution-condition audit |
| 11 | Cancelled action or failed sensor is not treated as verified external outcome | BM-01, BM-05, BM-11; external execution owner | I1, I3, I7 | Cancellation/sensor-failure cases; no fabricated outcome |
| 12 | Competing contexts can be prioritized and resumed without losing constraints/provenance | BM-06, BM-03, BM-11 | I1, I4 | Context switching/interruption; resumed constraint and lineage comparison |
| 13 | Same event receives different appraisal significance under different goals/conditions without fixed stimulus-emotion mapping | BM-07, BM-06, BM-08 | I4, I5 | Controlled context/goal contrast; appraisal provenance; no fixed mapping |
| 14 | Appraisal modulates attention/evaluation but does not directly command action | BM-07, BM-06, BM-08; SYS governance boundary | I4, I5, I7 | Appraisal variation; action authority remains independently gated |
| 15 | Process supplied goal without claiming internal origin | BM-08, BM-01, BM-11 | I5 | Supplied-goal provenance and origin classification |
| 16 | Form candidate goal from novel experience with inspectable evidence/reasoning lineage | BM-08, BM-01, BM-02, BM-03, BM-12 | I2, I5 | Novel episode; candidate-goal lineage and origin |
| 17 | Revise/defer/abandon candidate goal when later evidence defeats its premise | BM-08, BM-04, BM-05, BM-11 | I3, I5 | Defeated-premise injection; explicit candidate lifecycle transition |
| 18 | Governance denial blocks execution while preserving intent and denial as distinct records | BM-08; SYS governance/security/execution owners | I5, I7 | Denial path; intent unchanged and no execution claim |
| 19 | Reject/rollback candidate that improves acquisition context but regresses relevant counterexample | BM-09 plus affected state owners | I6, I7 | Paired acquisition/counterexample evaluation; rejection or rollback evidence |
| 20 | Persist candidate change through reconstruction and demonstrate changed later behavior | BM-09, affected behavior/state owner(s), BM-03, BM-11 | I1, I6, I7 | Pre/post behavior at the receiving owner; restart/reconstruction; causal attribution to the accepted candidate |
| 21 | Transfer learned change to justified related context without indiscriminate unrelated transfer | BM-09, BM-02, BM-03, BM-05 | I2, I3, I6, I7 | Held-out related and unrelated contexts; positive/negative transfer |
| 22 | Report numeric parameter improvement only as narrow adaptation, not broad learning | BM-09, BM-10 | I6, I7 | Claim-to-evidence calibration; explicit scope of demonstrated change |
| 23 | Belief change stales dependent plan; reconsider before use | BM-04, BM-08, BM-11 | I2, I5 | Version change; stale-plan detection before consequential use |
| 24 | Reconcile concurrent updates without silently discarding evidence | BM-11; owner of the conflicted authoritative state (BM-01–BM-12, context-dependent); BM-09 when learning updates participate | I1, I2, I6 | Concurrent conflicting proposals at the actual state owner; complete conflict and disposition history |
| 25 | Partial persistence failure cannot be reported as completed state transition | BM-11 and affected authoritative state owner(s); SYS-08 substrate / SYS-01 cognitive-validity boundary; BM-03/BM-09 where their state is involved | I1, I6, I7 | Failure injection at persistence boundary; distinguish substrate acknowledgement from validated cognitive transition; incomplete status and recovery |
| 26 | After interruption/reconstruction validate identity, lineage, consistency and pending work before resuming | BM-03, BM-10, BM-11; SYS-01 cognitive-state validation after reconstruction (SYS-08 substrate boundary where applicable) | I1, I4, I7 | Interrupt/restart; validate cognitive state separately from substrate availability; recovery checklist and pending-work reconciliation |
| 27 | BM-12 derives from sufficient premises with exact premise/inference lineage; owner evaluates conclusion | BM-12, BM-04, BM-05, BM-08 | I2, I3, I5 | Valid derivation; premise IDs/versions; provisional status and owner disposition |
| 28 | Empty/incomplete premises produce unresolved result, not substantive inference success | BM-12, BM-10 | I2, I7 | Empty/incomplete premise negative tests; explicit insufficiency |
| 29 | Contradictory premises remain a conflict; no silent winner or unqualified conclusion | BM-12, BM-04 | I2 | Contradictory premise set; conflict-preserving inference record |
| 30 | Memory changes conclusion only when relevant; reasoning identifies memory provenance and influence | BM-03, BM-12, BM-02 | I1, I2 | Relevant/irrelevant memory contrast; premise-to-conclusion lineage |
| 31 | Defeated assumption qualifies/withdraws conclusion while preserving prior lineage | BM-12, BM-05, BM-04, BM-11 | I2, I3 | Assumption defeat; targeted invalidation and preserved reasoning history |
| 32 | Counterexample/revised belief invalidates affected generalization and triggers targeted reevaluation | BM-12, BM-04, BM-05, BM-11 | I2, I3 | Counterexample; affected/unaffected knowledge comparison |
| 33 | Preserve plausible alternatives when evidence does not discriminate; do not manufacture certainty | BM-12, BM-02, BM-04, BM-08 | I2, I5 | Underdetermined evidence; alternatives and uncertainty retained |
| 34 | Reject stale, false or out-of-scope premises as verified fact despite valid derivation | BM-12, BM-04, BM-05, BM-10 | I2, I3, I7 | Stale/false/out-of-scope premise challenge; downstream-use rejection |
| 35 | Interpret same ambiguous utterance by task/conversation context, not fixed phrase mapping | BM-01, BM-02, BM-06, BM-08, BM-12 | I2, I4, I5 | Same utterance/different contexts; evidence-backed interpretation contrast |
| 36 | Preserve materially different intended outcomes and clarify before consequential commitment | BM-02, BM-08, BM-10, BM-11 | I2, I5 | Ambiguous-intent challenge; no commitment before clarification |
| 37 | Resolve indirect/incomplete request using prior turns/referents while separating literal and inferred intent | BM-02, BM-03, BM-08, BM-12 | I1, I2, I5 | Multi-turn referent test; literal/inferred content separation |
| 38 | Operator correction revises interpretation, preserves original utterance and reevaluates dependencies | BM-01, BM-02, BM-08, BM-11 | I1, I2, I5 | Correction sequence; immutable original + revised interpretation + stale dependents |
| 39 | Quoted/reported imperative is not silently treated as current operator instruction | BM-01, BM-02, BM-08; SYS authorization boundary | I2, I5, I7 | Quoted-instruction adversarial case; no unauthorized action request |
| 40 | Correctly inferred operator intent still cannot bypass authorization/execution governance | BM-08; SYS governance/security/execution owners | I5, I7 | Correct-intent + denied/unauthorized action case; no execution bypass |
| 41 | Provisional uncertain conclusion is evaluated as candidate claim, not silently committed as certain | BM-12, BM-04 | I2 | Provisional reasoning artifact; BM-04 acceptance/qualification/rejection record |
| 42 | Competing explanations both influence planning or trigger discriminating evidence request | BM-12, BM-08, BM-02, BM-06 | I2, I5 | Two-hypothesis planning comparison; no first-result-only consumption |
| 43 | Explanatory conclusion routed to BM-05 remains causal hypothesis pending evidence | BM-12, BM-05, BM-04 | I2, I3 | Routing and status transition audit; no premature causal promotion |
| 44 | Changed premise/assumption stales dependent conclusions and derived state with targeted reconsideration | BM-11 plus affected owners BM-04/05/08/12 | I1, I2, I3, I5 | Dependency graph/version mutation; bounded invalidation set |
| 45 | Downstream owner may qualify/reject reasoning result; rationale and original reasoning episode remain inspectable | BM-12 and receiving owner BM-04/05/08 | I2, I3, I5 | Accept/qualify/reject paths; preserved inference and owner disposition |
| 46 | Logging/delivery without relevant downstream evaluation fails integration acceptance | BM-11, BM-12, receiving owner | I0, I2, I3, I5 | End-to-end consumption evidence; delivery-only negative control |
| 47 | Accepted reasoning result materially changes qualified owner computation/state with exact artifact/version linkage | BM-12 and receiving owner BM-04/05/08 | I2, I3, I5 | Before/after owner computation; exact inference and owner-state versions |
| 48 | Previously accepted result is invalidated by changed premise/evidence; each affected owner records recompute/qualify/withdraw/retain rationale | BM-11, BM-12, BM-04/05/08 | I1, I2, I3, I5 | Invalidation propagation; per-owner disposition; unaffected-state preservation |
| 49 | Distinguish question/suggestion/assertion/instruction/commitment using linguistic and contextual evidence, not surface wording alone | BM-01, BM-02, BM-08, BM-12 | I2, I5 | Speech-act contrast set across contexts; confidence/uncertainty lineage |
| 50 | Attribute speaker, addressee and represented participant correctly in multi-participant interaction | BM-01, BM-02, BM-03, BM-08 | I1, I2, I5 | Multi-speaker attribution test; no operator misattribution |
| 51 | Distinguish explicit commitment from inferred possible commitment; clarify/defer material ambiguity | BM-02, BM-08, BM-10 | I2, I5 | Explicit/inferred commitment contrast; uncertainty and clarification evidence |
| 52 | Track commitment lifecycle across interactions with owner, scope, conditions, provenance and traceable revision/withdrawal/dispute/fulfillment | BM-03, BM-08, BM-11 | I1, I5, I6 | Longitudinal lifecycle; immutable event history and current disposition |
| 53 | Question/suggestion/assertion/quote/hypothetical does not become accepted instruction or commitment merely from imperative/future wording | BM-01, BM-02, BM-08; SYS authorization boundary | I2, I5, I7 | Adversarial speech-act set; no false instruction/commitment creation |
| 54 | External participant commitment is not fulfilled until attributable outcome supports fulfillment | BM-01, BM-03, BM-08, BM-11; external outcome owner | I1, I5, I7 | Attributable outcome evidence; absence-of-update negative control |
 
## 3. Cross-scenario acceptance rules

1. **No component-only pass.** A mechanism's unit test or isolated API does not pass a scenario whose expected behavior crosses owner boundaries.
2. **Provenance survives every transition.** For each derived artifact, retain enough identity/version/source/temporal/context information to reconstruct why it exists and which upstream evidence it used.
3. **Negative controls are mandatory.** Scenarios that prohibit a false promotion, silent overwrite, unsupported inference, unauthorized action or false completion require explicit negative-path evidence.
4. **Persistence means reconstruction.** A value visible before shutdown is not proof of persistence. Reconstruct and validate the owner-managed state and dependent-work status.
5. **Learning means later effect.** For scenarios 19–22, demonstrate attributable pre/post change, persistence, relevant transfer and regression controls; do not infer broad learning from parameter movement.
6. **Delivery is not integration.** For scenarios 44–48, record downstream receipt, owner evaluation, disposition and any material owner-state/computation change.
7. **External consequence requires attribution.** For scenarios 3, 11, 18, 39, 40, 53 and 54, keep Brain interpretation/intent separate from system permission, execution and verified external outcome.
8. **Scope and uncertainty are first-class.** A valid inference over stale, incomplete, contradicted or out-of-scope premises is not a verified conclusion.
9. **Targeted invalidation, not global reset.** When one premise changes, invalidate and reevaluate dependent artifacts while preserving unrelated authoritative state.
10. **No forced total sequence.** The matrix describes dependency obligations, not a mandatory serial pipeline. Work may be parallelized only after owner contracts and dependency versions are stable.

## 4. Planning gaps exposed by this matrix

The current planning supplement already describes integrated increments, work-package structure and a verification portfolio. This matrix makes four further planning obligations explicit:

- **Scenario 35–40 and 49–54 are not merely “language handling.”** They cross experience provenance, contextual representation, memory, intent/commitment ownership, multi-participant attribution and external authorization/outcome boundaries. They must not be isolated into a thin NLP ticket.
- **Scenarios 41–48 impose a substantive BM-12 integration gate.** A reasoning artifact being logged, emitted or delivered is insufficient. The consuming owner must evaluate it, preserve disposition, and demonstrate material downstream computation/state change when acceptance is claimed.
- **Scenarios 23–26 and 44–48 require dependency-aware lifecycle evidence.** Staleness, partial writes, concurrency, reconstruction and owner-specific recovery need explicit integrated failure cases, not only happy-path unit tests.
- **Scenarios 19–22 require longitudinal learning proof.** Persistence, held-out transfer, unrelated-context restraint and regression/rollback must be designed as one evidence package.

These are planning findings from the current proposed specification. They are not a claim that the existing implementation has been inspected against all 54 scenarios, nor a judgment that the current PR #174 proposal is accepted.

## 5. Owner-boundary cross-check — 2026-11-18

The Builder cross-checked the 54 scenario owner mappings against the BM-01–BM-12 ownership definitions and the current proposed specification's system-boundary and failure semantics at exact PR #174 HEAD `c34472354e4122fc1d78dc25bf45d81f1eb4dc69` (specification blob `cfdda9e6e7070cd5533b076e9bd77c2904694a32`). This is a bounded planning consistency check, not independent review, scenario execution or implementation evidence.

Five rows were clarified to avoid assigning ownership more narrowly or more broadly than the specification supports:

- **Scenario 3:** provider unavailability is a capability failure; it is not automatically a SYS-08 substrate failure. SYS-08 applies only when network/runtime substrate evidence establishes that cause.
- **Scenario 20:** a persisted learning candidate must be shown to affect the receiving mechanism's later behavior. BM-09/BM-03/BM-11 evidence alone cannot substitute for an observable downstream owner-state or behavior change.
- **Scenario 24:** the owner of the conflicted authoritative state is scenario-dependent. BM-11 coordinates conflict handling; BM-09 participates where learning updates are involved. BM-04 is not the universal owner of every authoritative state.
- **Scenario 25:** partial persistence failure crosses both SYS-08 substrate availability and SYS-01 cognitive validity. An infrastructure acknowledgement cannot by itself prove the semantic transition completed; the affected cognitive state owner remains responsible for its state.
- **Scenario 26:** restart/reconstruction must separately establish substrate availability (SYS-08, where relevant) and validate recovered cognitive state (SYS-01), with BM-03/BM-10/BM-11 retaining their respective memory, monitoring and coordination responsibilities.

These clarifications do not change the proposed increments or acceptance authority. No scenario is marked passed, no gate is cleared, and no implementation work package is activated.

---

## 6. Decisions and gates still reserved

- PR #173 architecture review/acceptance, CF-26 and CF-27 remain unresolved.
- PR #174 current corrected proposal requires exact-revision independent review and Project Director disposition.
- PR #175 Gate A remains NOT CLEARED; no implementation source baseline is selected.
- PR #175 Gate B static traceability is documented, but mechanism capability acceptance has NOT PASSED.
- PR #192 Documentation Foundation remains unaccepted. The latest recorded Independent Reviewer verdict is PARTIALLY CLEAR against historical HEAD `beb4d5a174a1dd613878f89132e97b5e6052c7d3`; it does not assess the current successor. Live PR #192 metadata is open/non-draft/unmerged at HEAD `711ce19e360bb5d4a7c91e9d94092466bb344f89` with 47 changed paths. Current disposition: DF-02 OPEN; DF-06 NOT MET; DF-09 NOT MET; DF-10 REOPENED pending a new terminal inventory successor; DF-11 WAIVED; DF-12 PENDING — Project Director only; Stage A HELD.
- No implementation work package is activated by this matrix. No runtime source change, test/build execution, algorithm/provider/schema/API selection, donor adoption, source-baseline selection, merge, Stage A or deployment is authorized.

---

**Final status:** Non-operative planning traceability artifact. It maps all 54 scenarios in the current proposed PR #174 specification to capability increments and minimum evidence classes, while distinguishing the 34 scenario statements accepted in the exact historical baseline from the 20 additional proposed scenarios. No scenario is claimed passed. The matrix does not accept the current proposal, clear Gate A/B, or authorize implementation.
