# DF-02 — Causal feedback and typed persistence gap

**Date:** 2026-11-20  
**Candidate source baseline:** PR #192 base `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor source baseline:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

> **Scope:** This is a capability-gap comparison between the pre-PR-#97 candidate and the unmerged donor line, not a claim that candidate code previously integrated these donor mechanisms and later lost them.

## 1. Candidate causal model never tests an existing hypothesis against the new outcome

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/causal_model.hpp` | `f740bdf222b3309b13f0c2f541c97448fc05da3e` | `a6bf02cf75c6f55fa47120c772aad9c77fa40cf1` |
| `core/cpp/src/causal_model.cpp` | `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` | `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c` |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | `d520025258805b02c1b3fbb2dbebe32e01562fbf` | `0d31349857e85a019467e9864bbe6625a6ecdef7` |

The candidate exposes only `observe_transition`. It adds a causal link on co-occurrence with strength 0.55 and strengthens it on repeated matching transitions. It has no `observe_outcome` API and does not evaluate the existing causal model against the newly observed outcome before learning from that same transition.

The donor adds `observe_outcome(before, after)` and calls it at the beginning of `observe_transition`. It simulates the previous model against the new observation, compares predicted values with actual beliefs, and weakens the relevant causal links when predictions fail. It records contradictory observations rather than deleting the hypothesis, allowing repeated counterexamples to overturn stale or conditional knowledge gradually. A new co-occurrence begins at strength 0.40, below the default prediction threshold; repeated matching experience is required before the link becomes predictive.

The donor phase-5 test explicitly asserts that one observation produces no prediction and repeated evidence does. It also checks contradiction counts and weakened associations. The candidate suite predicts after one observed transition and does not test counterexample-driven weakening. The suite is 46 donor assertions versus 12 candidate assertions.

**Finding:** candidate causal learning is predominantly positive co-occurrence strengthening. It does not have the donor's explicit negative-evidence path for weakening stale causal hypotheses. This makes it harder for the candidate model to revise causal beliefs when observed consequences contradict previous predictions.

## 2. Candidate scalar codec is ambiguous; donor adds a typed, length-prefixed codec

| Artifact | Candidate | Donor |
|---|---|---|
| `core/cpp/include/jarvis/core/causal_link_codec.hpp` | absent | `a6286281e4b22564a39e02a7e38a778bb81042f0` |
| `core/cpp/src/causal_model.cpp` | `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` | `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c` |

The candidate encodes a causal side as `key=value` without a type tag or length prefix. Its decoder splits at the first `=` and infers type from the payload text. Consequently:
- keys containing `=` are truncated or misparsed;
- string values such as `true`, `null` or `42` can be decoded as Boolean, null or integer instead of the original string;
- values/keys containing delimiters cannot be represented unambiguously.

The donor adds `causal_link_codec.hpp` with a versioned, type-tagged, length-prefixed format. It preserves delimiters and marker strings in keys and values, retains the Scalar variant type, validates payload boundaries and supports backward decoding of the old format.

**Finding:** candidate causal-link identity/value serialization is not type-safe or delimiter-safe. This is a persistence/replay integrity gap: decoded causal links can change key or Scalar type after round-trip.

## 3. Evidence and design boundary

The donor's initial link strength and update rates are fixed parameters. The capability gap is the feedback contract—old hypotheses are tested against new outcomes and contradictory evidence can weaken them—not automatic endorsement of the donor's exact constants. Those values should be justified and tested against learning stability, not copied as semantic rules.

No runtime or CMake files were changed. No donor code was copied. DF-02 remains OPEN pending full semantic/dependency/ownership and source-baseline adjudication.
