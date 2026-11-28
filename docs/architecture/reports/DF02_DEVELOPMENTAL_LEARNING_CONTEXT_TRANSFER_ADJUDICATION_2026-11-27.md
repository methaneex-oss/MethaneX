# DF-02 Developmental Learning Context Similarity and Strategy-Transfer Adjudication — 2026-11-27

**Scope:** donor-only `developmental_learning.cpp`, exact candidate-absent/source variants, donor learning and Brain-integration test contracts.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds context-sensitive strategy/association learning, bounded numeric/categorical transfer, negation/schema guards, confidence-weighted signed utility and deterministic ranking. This source path is donor-added; candidate path absent. Historical e737 alternate-branch tests #50, #60, #65–#68 passed; current candidate CTest not run.

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

 
## Donor-only developmental environment suite and historical CI execution — 2026-11-28

The previous source-only disposition is updated with exact test reachability and historical execution evidence. The following test/source blobs were fetched at e737cae7f907696ef787a4e85b0dee3a739d71b1 and match the donor blobs:
- developmental_learning.cpp: dbf5f43271dfa0a3c57236e2faa82eb88d15490d (445 lines);
- developmental_learning_suite.cpp: 8e94932b40c109f1c73470418d85ca2020a2e198 (301 lines);
- developmental_brain_integration_suite.cpp: 760162dd6d1e669162e0bf22223a437491f5e262 (1,139 lines);
- developmental_training_environment_suite.cpp: 62a0ee4f8ec966e48a45848217ba7a6d6e96196f (356 lines / 59 assert expressions);
- developmental_world_integration_suite.cpp: 4290fcfde741f1be9a4a69adc70699ade6fe7922 (198 lines).

Donor CMake blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 registers these donor-only tests:
- CTest #50 jarvis_developmental_learning_suite;
- CTest #60 jarvis_developmental_brain_integration_suite;
- CTest #65 jarvis_developmental_training_environment_suite;
- CTest #66 jarvis_developmental_environment_suite;
- CTest #67 jarvis_developmental_world_suite;
- CTest #68 jarvis_developmental_world_integration_suite.

All six passed in the post-fix historical e737cae7 CI. Exact execution was confirmed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer, and Brain ThreadSanitizer #957; each job reports 71/71 tests passed. Candidate CMake blob dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 does not register these six tests, and the corresponding donor-only paths are absent from the frozen candidate where recorded in the inventory.

### Developmental training environment semantics

The 59-assert suite defines a deterministic world that offers both actions but does not choose for the Brain. The Brain must choose, execute only the selected one-step action, receive the observed consequence, and update future choices. The suite checks:
- executor outage and failed execution produce no observed world consequence and must not create a route preference;
- negative route outcomes update attention/strategy while keeping the action model executable for later learning;
- a strategy learned in one navigation context initially transfers to a related context, then contradictory outcomes revise only the local context;
- the original context retains its useful strategy, the exception persists across restart/replay, and a third related context can still receive bounded transfer;
- an unrelated task context does not inherit navigation preference;
- environment/task/step labels remain episodic context, not fabricated world facts.

This is strong behavioral evidence for context-bounded adaptation in a controlled environment. It is not a general training engine or proof of open-world semantic understanding: the environment, action set, transitions and observations are synthetic and predefined. The tests show that the system can change later decisions from consequences in this fixture, not that it can autonomously discover tasks or generalize safely across arbitrary domains.

The 71-test pass evidence belongs to historical branch e737cae7, not current PR #203 and not the frozen PR #97 donor HEAD c1da222. No runtime source was changed or adopted. DF-02 remains OPEN; candidate absence and donor test success do not grant baseline authority.
