# DF-02 Memory–Learning–Evolution Persistence Integration Variant Adjudication — 2026-11-27

**Scope:** twelve exact versions of the donor-only `core/cpp/tests/memory_learning_evolution_persistence_suite.cpp` path, including the frozen donor, and exact test-CMake registration.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor and alternate test variants are inventoried; the frozen donor variant was source-inspected but not executed, while a distinct historical alternate variant passed CTest #45 in five e737cae7 CI jobs. Candidate build registration is absent. No path/authority closure.

## 1. Exact variant inventory

The artifact contains 12 distinct test blobs; the frozen candidate has no blob for this path.

| Blob SHA | Role | Tips | Representative branch | Lines |
|---|---|---:|---|---:|
| `98e6598f60912714234f2dfabfbe52fa5eb77044` | Donor | 36 | ci/priority-one-provenance-validation20261031 | 208 |
| `15ba379e5e272603cea5cda4a345375e29ce9da8` | Alternate | 1 | fix/evolution-lifecycle-ready20261029 | 224 |
| `1fd1a8d0efbe3d29ba485fc56353e25c5d507e45` | Alternate | 3 | fix/evolution-lifecycle-final-review20261029 | 226 |
| `2eea6d78d2586276ccb982828feb9d36583a4f01` | Alternate | 8 | fix/causal-key-value-codec20261028 | 199 |
| `5d578360fce5815707b3becd6b7e4df4115c2fd5` | Alternate | 3 | feat/prediction-developmental-validation20261030 | 246 |
| `b4f885a485f40cacb313cfe20340e8c1538269a9` | Alternate | 2 | fix/evolution-lifecycle-trust-final20261029 | 216 |
| `bf09eb116345d7b5ae1e23a7fcb35fdfccfd92fc` | Alternate | 5 | fix/evolution-authenticated-replay20261029 | 244 |
| `c8e545205ef1b96561998da5690d8974e03477b4` | Alternate | 1 | fix/evolution-lifecycle-ci-tests20261029 | 237 |
| `e46a29a888d77cff79ba20c444a234196d1e4d89` | Alternate | 1 | fix/evolution-lifecycle-verified-final20261029 | 230 |
| `e8971b1096c3ea89f468488ed6a4e0bffd3a8ce3` | Alternate | 1 | fix/evolution-lifecycle-trust20261029 | 214 |
| `fa2e5403bfad46fd4f1c0b2eb3561bcaecd044d6` | Alternate | 1 | fix/evolution-evaluation-lifecycle-ci20261029 | 225 |
| `fd4ac31042b6f7141ba3e9dcddf3c5fc38cc5df0` | Alternate | 1 | fix/evolution-lifecycle-review20261029 | 251 |

All exact contents are in the hash-verified discovery artifact. Owner branches/tip counts are provenance, not authority, semantic ancestry or independent review. Variants differ in evaluation/isolation attestation, learning, strategy, context and replay coverage; they are not one monotonic test revision.

## 2. Donor test contract

The donor suite SHA `98e6598f60912714234f2dfabfbe52fa5eb77044` uses explicit diagnostic checks (not `assert`) and a temporary journal. It exercises the integrated path:

1. Register an evolution parameter and record a prediction; prediction error feedback updates learning/adaptation and evolution-parameter evidence.
2. In an explicit context, execute six successful/verified `stable-action` interactions with observed positive consequence and six failed `unreliable-action` interactions.
3. Confirm developmental strategies record positive versus negative evidence and that subsequent decision scores favor the stable action.
4. Feed fitness observations into the registered evolution parameter and require a proposal.
5. Construct an experiment, invoke the process-isolation runner to create isolation evidence, record evaluation, adopt the experiment, and verify parameter value changes.
6. Verify before reconstruction that prediction resolution and action-outcome records are in memory/journal.
7. Construct a new Brain instance on the same journal path (forces file replay, but remains in the same OS process) and verify adopted parameter/observation count, positive and negative strategies, changed decision, adopted history, resolved prediction and action-outcome records survive reload.

The test combines experience-driven decision behavior and controlled evolution adoption in one persistence/replay path. It does not hardcode a chosen action as the learning result; it asserts the evidence changes later decision scores.

## 3. Build/test reachability

Candidate test CMake blob `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` has no target/reference for this suite. Donor test CMake blob `cbfd1fde52fffa6eeac025da2b7ddcb5ab493261` registers both executable `jarvis_memory_learning_evolution_persistence_suite` and CTest entry. This confirms donor build/test reachability only. No compile or test execution in this audit.

The suite's process-isolated evaluator uses a command fixture and the repository runner; it is not an independent external evaluator, and it does not prove OS sandbox robustness. Its restart is reconstruction in the same process, not a separate process-level crash/recovery test.

## 4. Five review lenses

1. **Semantic:** cross-mechanism prediction feedback → learned action consequences → proposal/evaluation/adoption → journal replay asserted.
2. **Build/test:** candidate target absent; donor target and CTest registration confirmed. Test source inspected only.
3. **Security/trust:** evaluation uses process-isolation attestation through the configured runner, but fixture command and environment; trust/failure semantics are not exhaustively adversarially validated.
4. **Cognition/capability:** positive/negative experience changes action scores and survives reconstruction; bounded fixture evidence, not general adaptive competence.
5. **Hostile review:** explicitly distinguished new-object replay from OS-process restart, test source from test execution, and candidate absence from authority to adopt donor.

## 5. Open obligations / disposition

| Item | State |
|---|---|
| 12 exact test variants inventoried | Complete for this slice |
| Donor cross-mechanism persistence contract inspected | Complete for source slice |
| Candidate absence / donor CMake registration | Confirmed |
| Test execution, separate-process crash/recovery, fault injection | Open |
| Production consumer/implementation and journal failure paths | Open |
| Owner/provenance/retention/authority | Open |
| DF-02 | OPEN |

**Disposition:** this donor-only suite is valuable integration evidence in source form, but not an accepted candidate test or selected implementation. No adoption/retirement/deletion decision; DF-02 and Foundation gates remain open; Stage A is not authorized.

 
## Exact alternate test variant and historical execution evidence — 2026-11-28

The earlier donor test blob 98e6598f60912714234f2dfabfbe52fa5eb77044 was **not** the source blob executed by the e737cae7 historical CI. The branch's exact file was fetched and SHA-verified:
- Executed alternate test blob: 5d578360fce5815707b3becd6b7e4df4115c2fd5 (246 lines; 25 explicit check() calls, not C assert expressions).
- It is one of the twelve inventoried variants (branch owner feat/prediction-developmental-validation20261030).
- The CMake registration is the same donor test-CMake blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261; CTest name jarvis_memory_learning_evolution_persistence_suite is test #45.
- The frozen candidate CMake does not register this suite.

The executed alternate test contract:
1. Records a prediction and verifies prediction-error feedback updates the same registered evolution parameter's evidence statistics.
2. Executes six successful/verified stable-action interactions and six failed/unreliable-action interactions in a separate context; verifies positive/negative developmental strategies and later decision-score preference.
3. Requires accumulated evidence to produce an evolution proposal, records evaluation through the configured isolated runner, adopts it, and verifies the parameter value changes.
4. Reconstructs a new Brain instance from the same journal and verifies adopted parameter value/observation count, positive and negative strategies, changed decision, adopted history, resolved prediction and action-outcome records survive replay.

The exact test #45 passed in all five post-fix e737cae7 test jobs:
- Brain CI #1826 native-brain job 123987534801;
- Brain CI #1826 sanitizer job 123987535203;
- JARVIS Brain Tests #975 brain job 123987535124;
- JARVIS Brain Tests #975 sanitizer job 123987534874;
- Brain ThreadSanitizer #957 job 123987535201.

Each corresponding log explicitly reports test #45 Passed; each complete job reports 71/71. This execution evidence applies to alternate blob 5d578360, not donor blob 98e6598f and not current PR #203. The test reconstructs a new Brain in the same OS process using the same journal path; it is not a process crash/restart test. Its isolated evaluator is a controlled fixture, not an independent external evaluator.

The donor test source remains a separate variant and must not be described as executed. No runtime source was changed or adopted; candidate absence and alternate test success do not create baseline authority. DF-02 remains OPEN.
