# DF-02 Causal-Link Typed Codec Compatibility Adjudication — 2026-11-27

**Scope:** donor-only `causal_link_codec.hpp`, its CausalModel integration and test coverage.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor introduces typed length-prefixed encoding for causal key/value sides and legacy decoding. It is not a frozen-candidate file and has no dedicated codec test. Source-only.

## 1. Exact ownership

The discovery artifact records one blob for `core/cpp/include/jarvis/core/causal_link_codec.hpp`:
- donor `a6286281e4b22564a39e02a7e38a778bb81042f0` (57 tips, branch `ci/priority-one-provenance-validation20261031`);
- no candidate blob/path at frozen PR #192 SHA.

CausalModel donor source `b7e1e6e6aeb929f09af33b9d17c80a6eed34948c` uses the codec for cause/effect keys and decodes effects for prediction. Candidate source `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` uses the prior string-encoded representation. The codec is a donor-added component, not an accepted baseline.

## 2. Codec behavior

V2 encoding is `@2|key-length|key|type-tag|payload-length|payload`, preserving keys/string values containing delimiters and distinguishing monostate, bool, string, int64 and double. Decoder checks lengths, tag and complete payload; V1 legacy `key=value` decoding remains.

This is a material representation improvement over ambiguous delimiter/type inference. It is reversible for ordinary nonempty keys and finite scalar values under a consistent locale.

## 3. Source-derived edge cases

- **Empty key:** encoder emits key length zero, but V2 decoder rejects `key_size == 0`; round-trip is not symmetric. Model inputs should either reject empty keys or codec should support them.
- **Legacy prefix collision:** decoder selects V2 whenever bytes begin `@2|`. A legacy encoded key/value string beginning with that prefix can be misclassified as V2 and fail decoding, rather than falling back to legacy. Compatibility is therefore not collision-free for every old record.
- **Non-finite doubles:** encoder and V2 decoder accept textual NaN/Inf; codec does not independently reject them. CausalModel/public belief input validation must define whether such values are valid.
- **Locale:** floating serialization uses default stream locale and parsing uses `std::stod` locale; stable cross-locale persistence is not explicitly enforced with classic locale.
- **Legacy type ambiguity:** V1 string values resembling null/boolean/numeric are decoded as those types. This is inherent loss in the old format and cannot be repaired without contextual schema/migration evidence.

## 4. Test evidence

The inspected phase-5 association/causal suite exercises transition learning, simulation, Brain replay and contextual prediction. No dedicated codec unit test was found for round-trip all Scalar types, delimiter-containing keys/string values, empty keys, `@2|` legacy collision, nonfinite doubles, malformed length/tag/payload or locale behavior. Tests were not executed.

## 5. Five review lenses

1. **Semantic:** typed encoding and length boundaries materially improve representation integrity.
2. **Build/test:** donor header is included through CausalModel; direct codec test coverage not located.
3. **Integrity:** empty-key asymmetry, legacy prefix collision and nonfinite acceptance are open.
4. **Cognition:** typed cause/effect values improve prediction fidelity but do not make learned links causal truth.
5. **Hostile review:** donor-added file is not baseline/authority; legacy migration risks are explicit.

## 6. Disposition

| Item | State |
|---|---|
| Exact donor codec blob | Verified |
| Candidate absence | Verified in frozen artifact |
| Typed/length-prefix behavior | Source inspected |
| Edge cases | Identified; no regression tests |
| Full codec consumer/owner/retention | Open |
| DF-02 | OPEN |

Codec remains **OPEN / NO AUTHORITY DECISION**. No adoption/retirement/deletion; no DF-02 closure, Foundation clearance or Stage A authorization.
