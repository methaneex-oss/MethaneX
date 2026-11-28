# DF-02 Association, Contextual Generalization and Causal-Hypothesis Adjudication — 2026-11-27

**Scope:** exact candidate/donor association model, causal model and phase-5 behavioral test contract.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds contradiction-aware co-change learning, contextual graph inference, shared-context concept candidates, generalized matches and prediction feedback; causal model maintains transition-derived hypotheses. Public model methods lack finite-value validation. Historical e737 donor association/causal test #24 passed in five CI jobs; current candidate CTest not run.

## 1. Exact inventory

Association source: candidate `b378d4237527dfbb4c65f43545f7f0fc7c42669b` (131 tips, 82 lines), donor `80bc2e94d8cab4e5a48ead18ba9efcad4ed785b6` (76 tips, 289 lines), alternate `a79219a7d91866bf91131876f2b761db60ff8e7c` (1 tip).

Causal source: candidate `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` (131 tips, 127 lines), donor `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c` (31 tips, 148 lines), alternates `15edd729640b58851e9c655d080e6a5e3aab5195`, `3b30eac1dfc681087c309e338077f636a393d7b6`, `8b884ed11a1a019d0e52bf7f35b0295edcc912b0`.

Association/causal phase-5 tests: candidate `d520025258805b02c1b3fbb2dbebe32e01562fbf` (131 tips, 56 lines), donor `0d31349857e85a019467e9864bbe6625a6ecdef7` (49 tips, 160 lines), alternates `410ea4b2cbb59c52c89456483b999a8a78784d2e`, `9099323d43b5af16d09c9356a239692fab5e136a`, `f1a60917a95ab2cd921d081b8c75b8540689608d`. Header and owner lineage are in the frozen discovery artifact.

## 2. Association-model behavior delta

Candidate associates changed beliefs with other beliefs in the after-state, including unchanged context; evidence is bounded by transition reliability and unchanged-belief confidence. Candidate lacks donor's contextual graph inference and feedback APIs.

Donor:
- identifies changed/present keys; weakens an existing association when exactly one endpoint changed (contradictory context), reducing strength/confidence and incrementing contradiction count;
- forms new/update associations between co-changed beliefs using transition reliability;
- exposes multi-hop contextual inference with hop decay and deterministic ranking;
- generates concept candidates from shared neighbors and generalized concept matches based on shared contextual neighbors/similarity;
- applies prediction feedback to existing concept-member associations, strengthening successful predictions and weakening failed ones with bounded updates.

These mechanisms establish association/co-change hypotheses and structural analogy. They do not independently establish causality or semantic concept identity.

## 3. Causal-model semantics and evidence limit

Donor `CausalModel::observe_transition` first evaluates existing hypotheses against the new outcome, weakening mismatched one-step predictions when their encoded cause is present. It then creates cause/effect links from changed belief key/value to other after-state belief key/value; first observation creates strength 0.40, repeat evidence strengthens with diminishing returns. Simulation follows links at strength ≥0.5 with depth cap 8 and confidence decay.

The test demonstrates a link is not predicted after one matching transition but becomes predicted after repeated matching transitions, bounded simulation depth, contextual association, Brain replay, concept formation, prediction-feedback strengthening/weakening. It uses synthetic repeated transitions and no intervention/control.

**Interpretation:** the model is learning directional temporal co-change hypotheses from supplied state transitions. It has no inspected intervention design, confounder control, randomized treatment, counterfactual identification or causal discovery guarantees. “Causal” outputs must remain hypotheses, not established causal effects.

## 4. Validation gap

Public `AssociationModel::observe` clamps `observation_reliability` but does not first reject non-finite values; `std::clamp(NaN)` can propagate NaN into strength/confidence. `apply_prediction_feedback` similarly clamps evidence without finite validation and can poison association values. Public inputs can also include malformed/duplicate/empty belief keys and non-finite belief confidence.

`CausalModel::observe_transition` does not validate belief keys/value uniqueness or reliability because it receives only before/after beliefs; exact key/value transitions are encoded into links. The Brain ingestion path may constrain some data, but these public model APIs do not independently enforce the domain.

The donor test suite checks low-reliability evidence, contradiction weakening, multi-hop contextual inference, concept candidates, contextual prediction and feedback. It does not inject NaN/infinity, duplicate/empty keys, adversarial sequence ordering, confounded transitions, interventions or false-causal negative controls. No tests were executed.

## 5. Five review lenses

1. **Semantic:** donor contextual/concept/feedback expansion and contradiction updates compared; causal direction is based on state-transition co-occurrence.
2. **Build/test:** phase-5 source assertions inspected; no native build/CTest.
3. **Integrity:** non-finite public input validation gap can corrupt model weights; replay reconstructs derived state but does not authenticate causal truth.
4. **Cognition:** structural analogy and prediction feedback are mechanisms; tests are synthetic and do not demonstrate generalization or causal identification.
5. **Hostile review:** association and causality labels qualified; no acceptance or source selection.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Association candidate/donor/alternate blobs | Inventoried |
| Causal model candidate/donor/alternates | Inventoried |
| Phase-5 test variants | Inventoried |
| Context/concept/feedback behavior | Source/test inspected |
| Finite/invalid input validation | Gap identified |
| Causal identification/negative controls | Open |
| Full owner/consumer/authority/retention | Open |
| Native tests | Historical e737 test #24 passed in five jobs; current candidate CTest not run |
| DF-02 | OPEN |

Association and causal-learning paths remain **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Historical execution of exact donor association/causal suite — 2026-11-28

The e737cae7f907696ef787a4e85b0dee3a739d71b1 alternate branch contains the exact frozen donor source/test blobs:
- association_model.cpp 80bc2e94d8cab4e5a48ead18ba9efcad4ed785b6 (290 lines);
- causal_model.cpp b7e1e6e6aeb929f09af33b9d17c80a6eed34948c (149 lines);
- association_causality_phase5_suite.cpp 0d31349857e85a019467e9864bbe6625a6ecdef7 (161 lines / 46 assert expressions);
- donor tests/CMakeLists.txt cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 registers it as CTest #24.

CTest #24 passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; all five jobs report 71/71. The frozen candidate test blob d520025258805b02c1b3fbb2dbebe32e01562fbf is 56 lines and does not contain the donor's contextual inference/feedback/causal hypothesis assertions.

This confirms the donor association/causal test contract executes on the historical e737 branch. It does not validate causal identification: the suite uses repeated synthetic state transitions and no intervention, randomized control, confounder handling or counterfactual negative control. The public-model non-finite-input validation gap remains untested. This is not current PR #203 CTest evidence or a baseline decision.
