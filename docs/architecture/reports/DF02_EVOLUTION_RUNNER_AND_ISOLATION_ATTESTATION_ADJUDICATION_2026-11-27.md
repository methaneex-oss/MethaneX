# DF-02 Evolution Experiment Runner and Isolation-Attestation Contract Adjudication — 2026-11-27

**Scope:** frozen candidate/donor runner, experiment safety gate, attestation data model and runner tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor closes callback-isolation trust and adds command parsing/attestation, but the attestation is a private field snapshot, not cryptographic provenance; backend isolation is still a reported boolean. Additional source gaps identified. No tests executed.

## 1. Exact refs

| File | Candidate SHA | Donor SHA |
|---|---|---|
| runner source | `83d3c26e589cd16151818774a81ccb62f9d514fc` | `0545662ea0ef865feb0527207fc4c32ecb50566e` |
| runner header | `38668879bec3e1cd5d8bcdf884edad819b1573d6` | `eb7f5c23a47054d1e60aa65f28627199f511645d` |
| safety gate source | `6c930ebbe69ad92fe155e3c169e3e996442f22cf` | `5a4669de9296958eacc77534bad87ce7c30ae52d` |
| experiment header | same frozen experiment header as donor comparison | `551d0d41b19abbeca425d102ec4c61984dfac0b6` |
| runner test | `08888276d875ce5e55f421e828f1bb4f061d1ea5` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` |

Historical source/test version inventories are in the frozen discovery artifact and the related coordinator/process-isolation adjudications.

## 2. Candidate/donor delta

Candidate callback runner trusts `SandboxResult.isolated` from the sandbox callback and accepts it when all other result flags and finite fitness pass. Candidate safety gate checks Improved, finite baseline/candidate, confidence threshold and regression limit, but does not recompute minimum-improvement threshold or require an isolation attestation.

Donor:
- treats callback-run results as non-isolated regardless of the callback's Boolean claim;
- adds `run_isolated_command` through `ProcessIsolationBackend`;
- validates started, isolated, completed, no timeout/output cap, zero exit code, nonempty output, and parses exactly one finite numeric fitness (only trailing whitespace allowed);
- sets candidate-executed/isolation flags and attests only after a valid evaluated result;
- safety gate validates finite/ranged confidence and policy values, requires valid isolation attestation when policy requires isolation, recomputes strict measured gain over minimum-improvement and maximum regression.

The experiment attestation is a private snapshot binding ID, proposal, baseline/candidate fitness, threshold, confidence, outcome, executed and isolated flags. Mutating bound fields invalidates it. It is not a cryptographic signature, sandbox identity credential, keyed MAC, or independently verifiable execution record.

## 3. Remaining safety contract gaps

- **Attestation authenticity:** private attestation prevents ordinary callers from directly setting the flag, but Brain/controller replay code is a friend and can re-attest reconstructed event fields. Replay authority is separately documented. The snapshot proves no external process/control was actually isolated.
- **Backend isolation bit:** `ProcessIsolationBackend` sets `isolated` after a process boundary, before all optional controls are verified. The runner consumes this boolean; required-control failures return invalid, but optional limits/filter success is not captured as a detailed control-result certificate. See the process-isolation report.
- **Fitness range:** runner accepts any finite numeric output; safety gate checks finiteness and gain but not a declared metric range. Coordinator summary clamps trial scores to [-1,1], but direct experiment APIs do not necessarily pass through summary. If fitness is contractually [-1,1], direct runner/controller path lacks range enforcement.
- **Execution requirement with isolation disabled:** safety gate's `candidate_executed` is implied by a valid attestation only when `require_isolation=true`; with isolation policy disabled, the gate does not independently require `candidate_executed`. Simulation/test policies may intentionally relax isolation, but should not relax proof that an evaluation actually ran.
- **No artifact binding:** attestation binds numeric experiment fields, not executable digest, command/argv, environment, sandbox controls, output hash, test/evaluator identity, or independent evaluator provenance.

## 4. Test contract

Donor runner suite tests:
- successful isolated command output parsing and valid attestation;
- mutation of candidate fitness invalidates attestation;
- callback falsely claiming isolation remains non-isolated and fails strict gate;
- timeout, output-limit, nonfinite fitness and callback exception produce Invalid/not executed.

The suite uses a local command fixture; it does not test executable identity pinning, path race, environment isolation, controls enabled/disabled/failure, output injection, out-of-range fitness, execution-disabled policy, replay forgery or platform-specific isolation. Source inspected; tests not executed.

## 5. Five review lenses

1. **Semantics:** donor strict gate recomputes outcome; callback isolation is distrusted.
2. **Build/test:** runner source/test inspected, no native execution.
3. **Trust/security:** field snapshot is integrity binding, not cryptographic provenance; backend bool remains coarse.
4. **Evaluation:** metric range, command identity and independent evaluator binding remain undefined/open.
5. **Hostile review:** attestation terminology is qualified; replay-created attestation and weak backend result are not called proof.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor runner and safety gate | Compared |
| Callback isolation distrust | Confirmed donor behavior |
| Attestation mutation binding | Source/test inspected |
| Attestation provenance/authenticity | Gap |
| Fitness range/executed requirement | Gap/contract open |
| OS isolation-control evidence | Open |
| Regression/fault/platform tests | Open |
| Native tests | Not performed |
| DF-02 | OPEN |

Runner/safety-gate cohort remains **OPEN / NO AUTHORITY DECISION**. No implementation selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
