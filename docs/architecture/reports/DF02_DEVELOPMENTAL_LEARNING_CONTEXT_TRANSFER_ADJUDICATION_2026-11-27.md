# DF-02 Developmental Learning Context Similarity and Strategy-Transfer Adjudication — 2026-11-27

**Scope:** donor-only `developmental_learning.cpp`, exact candidate-absent/source variants, donor learning and Brain-integration test contracts.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds context-sensitive strategy/association learning, bounded numeric/categorical transfer, negation/schema guards, confidence-weighted signed utility and deterministic ranking. This source path is donor-added; candidate path absent. Source/test inspection only.

## 1. Exact ownership and test inventory

Six source blobs for `core/cpp/src/developmental_learning.cpp`; no candidate blob:
- donor `dbf5f43271dfa0a3c57236e2faa82eb88d15490d` (38 tips; 444 lines);
- alternates `b06634c7563dc2cb338008ba145073bc6a21bfd9` (1), `bfe2db73a2722c421e6616d1caa20606f4f86098` (17), `c9a34d562fa1a20641530daba81bfdc1f3621fee` (19), `cf18d273dd67a85279bf6172a787752d29951995` (1), `e9d98374e583b8afcf0674fe2c25d0d57ef3bc6f` (1).

Donor learning suite `8e94932b40c109f1c73470418d85ca2020a2e198` (75 tips, 300 lines); no candidate test version. Donor Brain integration suite `760162dd6d1e669162e0bf22223a437491f5e262` (32 tips, 1138 lines), with eight historical variants. The exact content/branch metadata is in the frozen discovery artifact.

## 2. Learning and transfer semantics

The donor implementation:
- uses reliability-weighted learning rate from prediction error, reward magnitude, salience, novelty and affective significance; non-finite signal components are neutralized and reliability zero stops learning;
- stores signed reward/utility targets; prediction error controls update magnitude, not outcome valence;
- updates strategy value and confidence separately, and scores exact/related strategies by signed utility × confidence × context similarity;
- uses deterministic lexical tie-breaking for unordered-map iteration;
- compares contexts with token overlap, hierarchy/prefix structure, numeric log-scale bands, and inferred feature schema/value components;
- blocks transfer when negation polarity differs, inferred schemas differ, or featureless observation contexts are non-identical;
- supports related strategy retrieval and consolidation/retention.

This is a bounded heuristic generalization mechanism. Context similarity is not a semantic model: categorical similarity is token Jaccard, numeric bands are logarithmic, and the negation guard is a fixed token list. A similarity score cannot prove context equivalence.

## 3. Exact test contract

The donor learning suite checks reliability scaling, signed outcomes, strategy value/confidence, exact/related-context selection, context similarity/negation and consolidation. The 1138-line Brain integration suite trains from action-consequence evidence, verifies learned action choice in the same and related numeric contexts, reconstruction persistence, evidence-confidence selection, malformed affective-learning rejection/source binding, generic evidence consolidation, and precedence of developmental strategy over a conflicting episodic fallback.

The suite is synthetic/callback-driven. No tests were executed. Coverage gaps include malformed/duplicate keys, context/action identity delimiter collisions, adversarial token/negation language, numeric boundary/zero-band behavior, non-finite context descriptors, context-schema fuzzing, and semantic transfer false positives across unrelated values sharing tokens.

## 4. Source-derived identity and transfer risks

- Association/strategy map IDs concatenate `left + '\x1f' + right` and `context + '\x1f' + action`. If user-supplied keys/context/action contain the separator, distinct tuples can collide. The inputs are not escaped or length-prefixed at this layer.
- Token Jaccard can transfer between unrelated categorical values sharing descriptive tokens. It is an approximate heuristic; tests do not quantify false-transfer rates.
- Numeric-band similarity treats adjacent scale bands as 0.5 and may transfer at the default threshold. Boundary effects and zero/nonfinite descriptors require explicit contracts.
- Negation mismatch is a conservative fixed lexical guard, not language understanding; different negation phrases or modality can evade it.
- Featureless inferred contexts are deliberately exact-only, which reduces false transfer but also suppresses generalization in those contexts.

These are source-level risks, not executed reproductions.

## 5. Five review lenses

1. **Semantic:** signed reward and confidence separated; context similarity and transfer heuristics mapped.
2. **Build/test:** donor source and integration tests inspected; candidate path absent; no native execution.
3. **Integrity:** identity concatenation collision and unvalidated context inputs remain.
4. **Cognition:** experience can change action choice and persist; related-context transfer is bounded heuristic, not broad semantic understanding.
5. **Hostile review:** candidate absence is not assumed to mean all capability absent elsewhere; no source selection or adoption.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Six exact source blobs | Inventoried |
| Donor learning/Brain integration test contracts | Inspected |
| Candidate source/test path absent | Confirmed in frozen artifact |
| Context/key collision and false-transfer edge cases | Open |
| Fuzz/adversarial tests and native execution | Not performed |
| Full consumer/authority/provenance/retention | Open |
| DF-02 | OPEN |

Developmental learning remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
