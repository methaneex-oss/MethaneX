# DF-02 Evolution Test-Contract Adjudication — 2026-11-27

**Scope:** three frozen candidate/donor evolution test suites, exact content only.  
**Candidate:** PR #192 `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** test-contract divergences established; neither implementation selected. The frozen candidate/donor test variants were not executed as those exact refs; six third-lineage alternate test variants passed historical e737cae7 CI.

## Exact blobs reviewed

| Path | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | `3164cbc19bfb056cdccfdd58f0be047226d41a86` | `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | `08888276d875ce5e55f421e828f1bb4f061d1ea5` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | `6acd8aedb7520aebe745b15a2a10c527262f28e0` | `80cac5df347987a9074e1ced43202f8759f797d7` |

All six exact files were fetched from the immutable refs above and read in full for this slice.

## Behavioral contract deltas

### 1. Brain integration / durable evolution lifecycle

Candidate covers a simple fitness-observation → proposal → adoption → canary rollback → restart-to-baseline path. It does not establish, in this suite, that durable evaluation is required before adoption, that the caller's claimed outcome is recomputed, that replayed legacy adoption events without evidence are rejected, or that an unversioned rollback cannot undo a newer adoption.

Donor adds direct scenarios for:
- legacy adoption replay without experiment evidence must not mutate the parameter;
- legacy rollback without experiment identity must not undo a newer adoption;
- durable evaluation is recorded before adoption and history records the order;
- direct convenience adoption without experiment evidence is rejected;
- missing evaluation, equal-fitness, subthreshold and mismatched-evaluation cases fail closed;
- experiment identity and evaluation evidence are checked through adoption;
- canary evidence accumulation, persistence, rollback and replay behavior;
- replay of evaluation/adoption/rollback is idempotent in the covered cases.

**Finding:** donor tests specify materially stronger authority, replay and lifecycle contracts. This does not establish donor code correctness or complete coverage of persistence failure/crash cases.

### 2. Experiment runner / isolation trust

Candidate's callback fixtures test success, callback-reported isolation failure, timeout, output-limit, non-finite fitness and thrown exception. In its success case, a callback-returned isolation boolean is accepted by the sandbox contract.

Donor replaces the success case with a process-isolated command invocation and verifies that a valid attestation exists and that mutating fitness invalidates it. It also explicitly demonstrates that a callback can lie about isolation: callback execution may return an Improved result, but remains non-isolated, has no valid attestation, and fails the default safety gate. Timeout, output-limit, non-finite fitness and exception rejection remain covered.

**Finding:** donor test contract distinguishes successful evaluation from trusted isolation evidence. Missing in both suites: adversarial OS sandbox validation, resource-limit enforcement, executable identity/allowlisting, platform coverage, process crash/cleanup tests and native test execution in this audit.

### 3. Canary controller / journal replay

Candidate covers evaluation, adoption, three observation samples, rollback, restored baseline and a rollback history record.

Donor additionally checks explicit adoption-journal state and ordered Evaluated/Adopted history, preview/observation separation, experiment identity matching, repeated canary evidence across observations, and replay idempotency for evaluation, adoption and rollback, with journal state transitions Pending → Adopted → RolledBack.

**Finding:** donor tests make replay/idempotency and journal state first-class contracts. These scenarios are identified from test source; they have not been executed here.

## Disposition matrix

| Contract area | Frozen candidate evidence | Donor evidence | Audit disposition |
|---|---|---|---|
| Basic adoption and rollback | Present | Present | Equivalent only at this narrow happy-path level; not full semantic equivalence |
| Evaluation-before-adoption | Not asserted by candidate suite | Explicit assertions | Material candidate test gap |
| Evaluation validation | Limited integration fixture | Missing, equal, subthreshold, mismatch checks | Material candidate test gap |
| Isolation trust | Callback boolean fixture | Process attestation + callback distrust | Material security-contract divergence |
| Attestation mutation | Not covered | Explicit invalidation assertion | Candidate test gap |
| Legacy journal replay protection | Not covered | Legacy adoption/rollback protection | Candidate test gap |
| Idempotent replay | Not covered in candidate suite | Evaluation/adoption/rollback replay | Candidate test gap |
| Canary evidence accumulation | Basic 3-sample path | Persistence and identity-aware scenarios | Material coverage divergence |
| OS sandbox robustness | Not demonstrated | Not demonstrated by source test alone | Open test obligation |

## Required verification before semantic closure

1. Trace each donor-only assertion scenario to production implementation and the exact journal schema/transition.
2. Identify alternate historical blobs containing or changing each scenario; map owners and exact refs.
3. Check all test targets and their CTest registration at the frozen candidate/donor CMake refs.
4. Run candidate and selected implementation tests on an authorized native runner; report failures, not just build status.
5. Add persistence failure injection and process-isolation adversarial tests where required by the safety contract.
6. Record branch authority, provenance, retention disposition and reverse-consumer impacts. These remain separate from technical merit.

## Boundary

This is source-level test-contract adjudication for three exact files, not a runtime result, independent review, complete 159-path/544-blob semantic closure, source-baseline decision, donor adoption, retirement, DF-02 closure, gate acceptance, or Stage A authorization. No runtime/source files were modified.

 
## Third-lineage alternate evolution tests and historical CI — 2026-11-28

The e737cae7f907696ef787a4e85b0dee3a739d71b1 branch does not use either the frozen candidate or frozen donor source blob for six common evolution CTest names. It uses these third-lineage alternate test blobs:
| CTest | Test source blob | Lines | Assertions |
|---|---|---:|---:|
| #49 jarvis_evolution_adoption_journal_suite | ad3c58179cc150d303f5bcbbfa50beb40a1327c6 | 109 | 53 |
| #44 jarvis_evolution_brain_integration_suite | b065a301397c83bcb460d43fa36421a7bebc9060 | 445 | 105 |
| #43 jarvis_evolution_canary_controller_suite | 4b867af52e11a15e9d867a35cdefbf9c83333a2a | 128 | 36 |
| #37 jarvis_evolution_experiment_coordinator_suite | 04507a590b23d64bc03bb94d3c3d76c87092305d | 101 | 17 |
| #38 jarvis_evolution_experiment_runner_suite | 3338273fe972292c1ea25035ba45fed1be3da378 | 262 | 43 |
| #46 jarvis_evolution_opportunity_orchestration_suite | a4ece67094aa89f659254e01f226af49ae02f91e | 155 | 26 |

All six tests passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; each of the five jobs reports 71/71. These are execution results for the alternate e737 test blobs, not the frozen candidate or donor blobs in the first table.

The six alternate variants exercise adoption-journal replay, Brain integration, canary state/rollback, coordinator orchestration, process-isolated runner attestation and opportunity orchestration. Their existence demonstrates a third historical lineage, not authority to replace either frozen variant. The six test source SHAs are distinct from both candidate and donor SHAs; the CMake report records the exact three-way identity comparison.

No implementation or test source was changed. The frozen candidate/donor test variants still require exact native execution and independent semantic review. No baseline decision, donor adoption or retirement is implied.
