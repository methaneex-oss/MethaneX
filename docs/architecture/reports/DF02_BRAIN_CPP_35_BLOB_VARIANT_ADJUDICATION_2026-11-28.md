# DF-02 Brain.cpp Exact Variant and Translation-Unit Ownership Adjudication — 2026-11-28

**Scope:** exact 35-blob historical cohort for `core/cpp/src/brain.cpp`; method-definition surface, candidate/donor split, CMake registration and owner-tip inventory.  
**Candidate:** frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Evidence:** discovery artifact #14956148301; re-download SHA-256 verified `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Disposition:** method surface and source split established at exact blobs; historical semantic closure remains OPEN. No build/test execution.

## 1. Exact 35-blob inventory

| Blob SHA | Tip count | Extraction group |
|---|---:|---|
| `0f377bf853af866375b35a944862c743c777a4c0` | 1 | Donor-shaped |
| `1e19646037d12a50dac7b33f5960b5fae37504a1` | 3 | Candidate-shaped/intermediate |
| `23080c58545d3f211a708b72952b1898f7c1991e` | 3 | Donor-shaped |
| `286c55279bc873094ee85c23108e5dbca838be0f` | 1 | Donor-shaped |
| `355f08deb5deccdbece14c014e660292339ab185` | 1 | Donor-shaped |
| `357c214596620d074eba58479c7bcf96bf6379a0` | 1 | Donor-shaped |
| `3c9271a8551c1676a3e850cf258463c9b6338016` | 1 | Donor-shaped |
| `3d7e92070ab2cd6a5c40e56cdcdadbea3ae53429` | 1 | Donor-shaped |
| `48c755ce21d5e899366a2e97ec59b5e1a4f82b67` | 5 | Donor-shaped |
| `48f5f26c71ab025ab55bf1a33e6d9b8273b047a5` | 2 | Donor-shaped |
| `4d984c2475933f55212dd3305d5bf8cf67b3906e` | 1 | Donor-shaped |
| `575fc4779d057617f995a4c6a3d3cdfe1fe56812` | 1 | Donor-shaped |
| `59d8212ba03aaffbb27eae1989f61914a8bb66fa` | 1 | Donor-shaped |
| `5b47ec947b89b4568256bd5c714e6a76be0f5271` | 1 | Donor-shaped |
| `65c360a819853e9c919da9b03ac8b9f19f929707` | 1 | Donor-shaped |
| `66ae05afe28c76c04c667213aedfbe26a169e627` | 3 | Donor-shaped |
| `6c80536160ec8c7bc30f30d60d32ac825830c52b` | 1 | Donor-shaped |
| `7af22454ed7dbc3172e57ef0da217c1e7b852453` | 1 | Donor-shaped |
| `8232f9a3ca8dcdbda31dad20c14cc798ab85b2ce` | 2 | Donor-shaped |
| `8d6b9b55f1b9501dc8d789d1b165146e54d95d72` | 1 | Donor-shaped |
| `8e7ca3f10f545483fe3797324ff066c720ea5cb6` | 1 | Unclassified |
| `93a10a5021a5775a3a239037cbb0b58a1e0c67a9` | 2 | Donor-shaped |
| `981fc54e5d8a244c4d7ac1c7802b6ec021c81d78` | 7 | Donor-shaped |
| `a365ea53155c46bfd8798d0266148ac7fcec08b1` | 1 | Donor-shaped |
| `abcd80e21423ce846aa68190e757fab5ce4db849` | 8 | Donor-shaped |
| `b2eb5bbe0714d07fba6cc71f01f33722a5374072` | 1 | Donor-shaped |
| `ba53d1cb2bd542dd93700787f44d949437623167` | 11 | Candidate-shaped/intermediate |
| `bbc3469e6463c40a8957fdb43590bf3a55b36379` | 18 | Donor-shaped |
| `d1f82d8f867a3325dd4cf4cfe27d71a9a30693ea` | 2 | Donor-shaped |
| `dec9e5442b3ca4b81a7879855c6146b2619934cc` | 8 | Donor |
| `e7602b6194e4db59475b9905051b9385cc8cc52a` | 1 | Candidate-shaped/intermediate |
| `e9f3758fcc9c0e89b7280ce376db9033d547682d` | 100 | Candidate |
| `efe8860f1b8cf5a9b5e42d65003b3280f5768ad5` | 18 | Candidate-shaped/intermediate |
| `f7f32937ee38acb94d9f03161247fb6ef0fac8e6` | 1 | Candidate-shaped/intermediate |
| `fbe791ac3a438087542c548f0b37552f3f8a91eb` | 1 | Candidate-shaped/intermediate |

Extraction classification by method-definition pattern: 27 donor-shaped blobs/76 tip rows, seven candidate-shaped blobs/135 tip rows, one unclassified blob/one tip row. This is regex/feature lineage only; it does not establish semantic successor or authority.

## 2. Exact candidate/donor method surface

A method-name extractor that includes constructors and private helpers returned:
- Candidate blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`: 48 unique Brain method names, 50 definition matches (constructor included; overloads).
- Donor blob `dec9e5442b3ca4b81a7879855c6146b2619934cc`: 9 unique names, 9 definition matches.

Excluding the constructor, this reconciles the prior source-lineage count of 47 candidate methods and eight donor methods.

Candidate brain.cpp owns the broad Brain implementation surface: observe/learn, beliefs/predictions, association/causal/decision/planning, action/capability, evolution lifecycle, goals/intent/strategy, reflection, recovery, self-test and snapshot/state. Donor brain.cpp retains the core cycle/replay/learning boundary and adds private experience/affective consolidation helpers. The donor splits public/large API families into other translation units.

Shared exact method names (excluding constructor) are learn, observe, replay and sync_self_state. Candidate-only definition surface includes 43 names under this extractor; donor-only source methods include learn_from_prediction, consolidate_experience, process_affective_experience and valid_affective_learning_source. Exact declarations/definitions and overload signatures must still be AST/compiler reconciled.

## 3. CMake source ownership

Candidate frozen CMake includes brain.cpp, brain_novelty.cpp and the existing 57-source core list. It does not register restored API, action-execution, prediction-context or affective-planning Brain translation units, nor affective/developmental models.

Donor frozen CMake registers brain.cpp plus:
- brain_restored_api.cpp
- brain_action_execution.cpp
- brain_prediction_context.cpp
- brain_affective_planning.cpp
- affective_state.cpp
- affective_learning.cpp
- developmental_learning.cpp

This split is documented in the exact 22-blob core CMake report. The candidate's restored API path is not compiled in its frozen graph; overlapping methods remain in brain.cpp, so adding the unregistered file without a coordinated source/header split risks duplicate definitions.

## 4. Semantic/consumer and test boundaries

The 35-blob path has high lexical-consumer volume (665 candidate symbol-match rows) and 34 exact path-reference candidates. Those matches must be filtered into real declarations, callers, tests, build/workflow uses, comments and false positives; no complete reverse consumer graph is closed here.

Candidate and donor compile ownership differs. Tests and Brain API reports show donor adds lifecycle, affective, contextual prediction, goal-outcome and developmental behavior, but source definition relocation is not itself proof that every consumer/test is correctly wired. Native compilation and CTest at frozen refs were not executed.

## 5. Review lenses

1. **Semantics:** candidate broad implementation and donor translation-unit split differ materially; source-lineage extraction does not establish behavioral equivalence.
2. **Build:** candidate/donor exact source graph inspected; candidate excludes restored API while donor includes split TUs. No build/link/CTest.
3. **Authority:** API mutation, evolution evaluation/adoption, replay and goal outcomes depend on public declarations, journal and validation; ownership boundaries must be reconciled across files.
4. **Capability:** method presence does not establish autonomous cognition or closed-loop behavior.
5. **Hostile:** prior counts are reconciled by excluding constructor; exact AST signatures, consumer edges, full 35-blob semantic diffs and authority/retention remain open.

## 6. Disposition

| Obligation | State |
|---|---|
| 35 exact blobs and tip inventory | Complete for this slice |
| Candidate/donor method-name surface | Compared, regex-only |
| Candidate/donor CMake owner split | Confirmed |
| Historical semantic diffs | Partial |
| AST/signature and declaration-definition graph | Open |
| Reverse consumers/context | Partial |
| Build/CTest | Not run |
| Provenance/authority/retention | Open |
| DF-02 | OPEN |

**Disposition:** Brain.cpp cohort source-inventoried and bounded ownership-adjudicated, not semantically/authority closed. No implementation selected/adopted, alternate retired/deleted, baseline, Stage A or gate clearance.
