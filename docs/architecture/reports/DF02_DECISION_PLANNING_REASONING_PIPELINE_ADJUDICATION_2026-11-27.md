# DF-02 Decision, Planning and Reasoning Pipeline Variant Adjudication — 2026-11-27

**Scope:** candidate/donor decision and planning source, reasoning variants, and exact architecture-test contracts.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor integrates affective/contextual factors and disputed-premise handling; public input/policy validation and inference conflict behavior have gaps. Source/test inspection only.

## 1. Exact refs

| Component | Candidate SHA | Donor SHA |
|---|---|---|
| `decision.cpp` | `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c` | `012025bc2ef66b1b9555b9b9f2b220b49c8d36c4` |
| `planning.cpp` | `aab022b7cbc06f380413395757d590b56a1f3a20` | `9fcc2317e5acf0bfc24865a89eb9a54b80f8a80a` |
| `reasoning.cpp` | `feec78b2e8a1f2b0b58733fd509e4e5a750258fc` | `18bf2facc9f95c6bd2e8d9a559a0e5b1c5ae06e1` |
| decision/planning test | `16934f99898c3ffffcf5ac04a7a031e0845da050` | `3ed85a1acc55f47eb266599d809525ef08ba0b11` |
| reasoning test | candidate test path is alternate | `ceb6d471b3283f4a89fe243ac3c9e79f52f137a2` |

Reasoning source has one additional alternate `9ac7806cf7a68e3abd4a1da56e0d3da44ba5c5da`. Full owner and test-history details remain in the frozen artifact.

## 2. Candidate/donor behavior

- **Decision:** candidate scores utility/value, goal, plan, uncertainty, threat, risk and resource. Donor adds affective valence/arousal/uncertainty/tension/stability, signed expected consequence, urgency, reversibility and safer context modulation. Context-wide bonuses modulate expected value rather than adding a shared score that could make harmful actions pass thresholds. Inputs/action weights are finite-normalized; stable name tie-break.
- **Planning:** donor adds affective utility/reversibility/risk modifiers. It ranks candidate actions and builds a bounded horizon; the plan's summary expected value is a sum of nonnegative action expected values, and risk is accumulated as risk×(1−reversibility), capped at 1.
- **Reasoning:** donor accepts typed/legacy causal-link sides, ignores disputed premises for deduction, propagates minimum premise/link confidence and bounded-depth inference. Contradictory premises are detected by same key/different Scalar values.

## 3. Source-derived gaps

1. **Planning policy finite validation:** action/context values are sanitized, but policy weights are used directly in `score_action`. A caller-supplied NaN/Inf weight can produce nonfinite scores. The stable-sort comparator `score(a) > score(b)` may no longer satisfy strict weak ordering with NaN, so ordering behavior is not defined reliably. No policy validation/fuzz regression located.
2. **Plan-value accounting:** plan summary sums only nonnegative expected values. A negative expected-value action contributes zero rather than its negative value, so a multi-step plan can overstate aggregate expected value. This may be a deliberate benefit-only summary, but the field is named expected value and its contract needs clarity.
3. **Reasoning link strength:** reasoning skips links only when `strength <= 0`; it does not reject nonfinite strength. NaN passes the comparison and `std::clamp(NaN)` remains NaN; `std::min(cause_confidence, NaN)` can return the cause confidence, effectively treating malformed link strength as acceptable evidence. Infinity clamps to 1.0. 
4. **Premise confidence:** disputed premise filtering is present, but confidence values are clamped without explicit finite validation; NaN can propagate into result confidence. 
5. **Inferred conflicts:** multiple causal links can infer different values for the same effect key in a frontier. First link order wins through map insertion; no explicit conflict/dispute generation or order-independent resolution. Duplicate same-key premises with different confidence overwrite in `known`, making confidence input-order-dependent.
6. **Expected value/risk normalization:** plan risk is capped after summation; expected value is not bounded and does not include negative values. Decision/plan score fields use different formulas and should not be interpreted as calibrated probabilities.

## 4. Test contract

Donor decision/planning architecture suite is only 23 lines versus the candidate's 123-line suite; donor's broader coverage is distributed to affective and integration suites, but a full test-suite mapping is not completed. Donor reasoning suite asserts:
- contradictory same-key premises;
- disputed premise does not authorize deduction;
- two-hop inference and confidence propagation;
- bounded max steps;
- typed delimiter-bearing key/string values;
- legacy decoding and malformed V2 rejection.

No inspected reasoning tests cover NaN/Inf link strength, NaN premise confidence, conflicting inferred effects/link order, duplicate-premise confidence ordering, or nonfinite planning-policy weights. No native tests executed.

## 5. Five review lenses

1. **Semantics:** affective decision/planning integration and disputed premise handling compared.
2. **Build/test:** exact donor test source inspected; wider test mapping and execution incomplete.
3. **Integrity:** malformed numerical weights/links and order-dependent conflicts remain.
4. **Cognition:** scores and inference are bounded mechanisms, not calibrated probabilities or causal certainty.
5. **Hostile review:** score names/expected-value summary are qualified; no source preference/acceptance.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor decision/planning/reasoning source | Compared |
| Affective decision/planning delta | Source inspected |
| Reasoning disputed premise/codec behavior | Test source inspected |
| Policy/link/premise nonfinite validation | Gaps identified |
| Conflicting inference order independence | Open |
| Full consumers/authority/retention | Open |
| Native tests | Not performed |
| DF-02 | OPEN |

Decision/planning/reasoning remain **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
