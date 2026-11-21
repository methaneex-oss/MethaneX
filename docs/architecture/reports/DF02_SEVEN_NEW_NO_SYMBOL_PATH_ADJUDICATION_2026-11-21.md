# DF02 — Seven-Path Exact Ownership Reconciliation and Prior-Report Correction
## 2026-11-21

**Status:** Builder evidence addendum. No runtime source, tests, CMake, or architecture were changed. No source baseline was selected and no donor adoption was authorized.

## 1. Relationship to existing DF02 reports

These seven paths are not newly discovered across the whole DF02 record. They were already discussed as other-ref-only paths in DF02_COMPILED_CONSUMER_AND_ALTERNATE_BRANCH_ADJUDICATION_2026-11-20.md. The EngineeringTaskLedger was also examined in DF02_ENGINEERING_AGENT_DELIVERY_AND_TASK_LEDGER_GAP_2026-11-21.md, and several of the paths appear in the 35-path candidate-absent adjudication.

The earlier 41-path no-symbol supplement did not include these seven. This report therefore closes the cross-report accounting for the 48-path no-symbol set and adds evidence unavailable to those earlier reports: an exact branch-tip-to-blob join from the 2026-11-21 all-ref scan. It also corrects the interpretation of ExperienceMemory: the helper is not integrated into the donor Brain, but the donor Brain does implement sequence-safe prediction identity directly.

## 2. Exact scan provenance

- Repository: methaneex-oss/MethaneX
- Candidate PR #192 source snapshot: 19c1c168fdbdab58ed9732cd250d2ae4624936eb
- Candidate branch: docs/whole-brain-planning-scope-correction-20261107
- Donor PR #97 HEAD: c1da222e6c94aeb3f2ad000392c21fe4fc81ab25
- b627 source line: integration/priority-one-memory-bool-hardening at b627dcc6a0ec849386425c785ba567ff2d2198dc
- Divergent Gate-A line: fix/gate-a-d1-d2 at a37add18babf8afc2e9c12ca0449a2ee84ecd60d
- Scanner branch commit: b8a594ea514ff44cadb5342986c68b1eac6e22ed
- Workflow run: 44931803411
- Artifact: 14717933378
- Artifact SHA-256: 189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f

The scan covered 254 branch refs and 213 unique branch tips. It produced 798 path/blob ownership rows, 1,938 exact path-reference rows, 1,226 consumer-blob/path/category occurrences, 1,415 text blobs, and 40,041 lexical candidate rows. The 48 no-symbol paths divide into 28 absent, 19 divergent, and one identical. The earlier 41-path supplement plus the seven paths reconciled here account for all 48; this does not close the separate 76 divergent lexical-consumer paths.

## 3. Exact branch/blob ownership for the seven paths

| Path | Candidate/main | PR #97 donor | b627 source line | Exact ownership summary |
|---|---|---|---|---|
| core/cpp/include/jarvis/core/experience_memory.hpp | Absent | 28cce354eb9db7e8ca292746fd14649debb7ab04 | Same donor blob | One version across 77 unique tips, including PR #97, b627, Gate-A and the brain-constitution documentation line |
| core/cpp/src/brain_affective_planning.cpp | Absent | 2a9406257c23f3a66a64071842be7d6448799406 | Same donor blob | One version across 76 tips, including PR #97, b627, Gate-A and the brain-constitution documentation line |
| core/cpp/src/brain_prediction_context.cpp | Absent | b3ceff150f3fe8223dc3f76f4c298ac264d72dae | Same later donor-line blob | Two versions exist: a1038030fae59123b4aa58b1ef2c1b19140898e7 on one tip, and b3ceff150f3fe8223dc3f76f4c298ac264d72dae on 76 tips; PR #97 and b627 use the latter |
| core/cpp/tests/affective_planning_suite.cpp | Absent | 32e5f04cfb6e4764cb205744266375367228bedf | Same donor blob | One version across 76 tips, including PR #97 and b627 |
| core/cpp/tests/association_causality_phase5_suite.cpp | d520025258805b02c1b3fbb2dbebe32e01562fbf | 0d31349857e85a019467e9864bbe6625a6ecdef7 | Later variant 9099323d43b5af16d09c9356a239692fab5e136a | Five exact versions: candidate 131 tips, donor 49, b627/Gate-A 26, plus two one-tip variants |
| core/cpp/tests/reasoning_architecture_suite.cpp | a7119afd091e045d6294aa1b15c20de349ed6a1c | ceb6d471b3283f4a89fe243ac3c9e79f52f137a2 | Same donor blob | Three exact versions: candidate 135 tips, donor/b627 57, and another variant 29c0ad53213785122abecd7aaf3d5b89cafabee2 on 20 tips |
| engineering/cpp/include/jarvis/engineering/task_ledger.hpp | Absent | 95d3f2e42be742f9e75aed8e55ea389723534a64 | Same donor blob | One version across 76 tips, including PR #97, b627 and Gate-A |

This table is a direct branch-to-blob mapping. It supersedes the earlier statement in the 76-path dispersion report that the scan did not join branch names/tips to exact blob SHAs. It does not, by itself, decide which branch version should become the source baseline.

## 4. Semantic corrections and cross-report dispositions

### 4.1 ExperienceMemory is not the integrated donor Brain memory

The ExperienceMemory header and its test are standalone. The donor Brain header does not include the helper, and the main Brain execution path does not instantiate it. The helper's test verifies its own per-sequence/per-key index behavior; it is not evidence that the Brain uses that class.

The important behavioral difference is elsewhere:
- The donor Brain stores prediction records in a sequence-preserving vector and resolves an individual prediction by sequence.
- The current candidate Brain stores predictions in an unordered map keyed by semantic key and resolves by that key.
- Repeated unresolved predictions for the same semantic key can therefore collapse onto one candidate map entry.

**Correct disposition:** Do not adopt ExperienceMemory as a second Brain memory subsystem. Preserve the sequence-safe prediction-identity requirement and evaluate implementing it in the current Brain architecture after source-baseline selection. The real candidate gap is prediction identity/collision behavior, not the absence of the standalone header.

### 4.2 Affective planning and contextual prediction are integrated donor Brain paths

brain_affective_planning.cpp and brain_prediction_context.cpp are compiled donor sources called by Brain methods. They are not merely orphaned declarations. The donor line's affective-planning suite is registered in CTest. The candidate has no same-path implementation or equivalent Brain method contract in the inspected main source tree.

These are genuine donor capability candidates, but their fixed appraisal, transfer and scoring parameters remain subject to calibration and counterexample evaluation. Their existence does not make them approved for automatic porting.

### 4.3 Association and reasoning suites have multiple owners, not one donor/candidate pair

The candidate association suite has 12 assertions versus 46 in the PR #97 donor suite, as already recorded in the compiled-consumer report. The b627/Gate-A branch uses a third, later blob (9099323d...), not the donor blob. Its semantics must be read from that exact version rather than assumed identical to PR #97.

The candidate reasoning suite has 19 assertions versus 33 in the donor suite. The b627 branch uses the donor-identical reasoning-suite blob; a separate 20-tip cluster contains another version. The supporting cognitive contracts report already documents the disputed-evidence and typed-codec behavior. This addendum supplies exact ownership, not a second independent claim about the same assertions.

### 4.4 EngineeringTaskLedger is an engineering orchestration primitive

The task ledger is integrated into the b627 EngineeringCoordinator through dispatch_tracked, but it is not Brain memory and does not constitute a complete multi-agent LLM builder. The candidate main coordinator lacks this durable tracked-dispatch path. The focused engineering-agent report documents the ledger, message bus, task/result contract, and CMake/test differences.

One test-scope qualification is added: the task-ledger suite constructs multiple ledger instances and exercises concurrent/stale transitions in one test process. It does not spawn independent operating-system processes. The implementation uses OS file locks, but the existing test is not a cross-process stress test.

## 5. Source-line and authority conclusion

The b627 branch contains all 159 donor paths (139 byte-identical to the PR #97 donor and 20 later variants) and has exact-head 74/74 CTest, ThreadSanitizer and native-build evidence. It remains an unmerged draft source line. The current main and PR #192 documentation branch have the same C++ core/engineering source tree; PR #192 remains documentation-only. PR #97 is a large divergent draft and is not mergeable as-is. The separate Gate-A branch is divergent and lacks exact-head CI evidence.

The 48 no-symbol paths are now accounted for across the earlier 41-path supplement and the seven paths reconciled here. DF02 remains OPEN: the 76 divergent lexical-consumer paths still require semantic successor/duplicate-owner decisions, and source-baseline/adoption/retirement authority remains with the Project Director. No code, CMake, test, runtime or branch-history change was made by this report.