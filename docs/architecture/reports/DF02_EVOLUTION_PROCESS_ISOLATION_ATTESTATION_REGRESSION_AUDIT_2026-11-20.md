# DF-02 — Evolution process-isolation attestation regression audit

**Date:** 2026-11-20  
**Candidate snapshot:** `cbc51e2b10f1fc976257653adf773735a2b27d49`  
**Donor snapshot:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`

This report isolates a critical safety-boundary defect in the candidate evolution-experiment path. The process-isolation backend itself exists in both snapshots; the regression is that the candidate runner no longer connects it to a trustworthy attestation path.

## 1. Exact source evidence

| Artifact | Candidate blob | Donor blob |
|---|---|---|
| `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` | `38668879bec3e1cd5d8bcdf884edad819b1573d6` | `eb7f5c23a47054d1e60aa65f28627199f511645d` |
| `core/cpp/src/evolution_experiment_runner.cpp` | `83d3c26e589cd16151818774a81ccb62f9d514fc` | `0545662ea0ef865feb0527207fc4c32ecb50566e` |
| `core/cpp/src/evolution_sandbox.cpp` | `837ab2adb087284fb370b623371693660b47624a` | `364641cf3616db100dd54853d12293341d609116` |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | `53bcd379fb788a3b0c369309c328f70d56f051ba` | `551d0d41b19abbeca425d102ec4c61984dfac0b6` |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | `08888276d875ce5e55f421e828f1bb4f061d1ea5` | `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6` |

## 2. Candidate accepts a callback's self-asserted isolation bit

The candidate `EvolutionSandbox::run` calls the injected `CandidateExecutor` and accepts the returned `SandboxResult.isolated` Boolean. The candidate `EvolutionExperimentRunner::run` then treats that Boolean as sufficient isolation evidence. The candidate test explicitly returns `SandboxResult{started=true, completed=true, isolated=true, fitness=0.86}` from an ordinary in-process callback and expects `Improved` with `candidate_executed=true`.

That is not process isolation. The callback controls the Boolean it is being trusted to prove.

The donor deliberately changes this boundary: after invoking the callback executor, `EvolutionSandbox::run` unconditionally sets `result.isolated = false`. Its comment states that a callback-provided Boolean is not proof of process isolation. The callback remains available for deterministic simulations, but those results cannot pass the default isolation-required safety policy.

## 3. Donor supplies a real process-isolated command path

The donor runner adds `run_isolated_command`, which invokes `ProcessIsolationBackend::run`, checks started/isolated/completed state, timeout, output limit, exit code and output presence, parses one finite numeric fitness value, marks the experiment isolated and creates a private attestation snapshot after evaluation.

The donor `EvolutionExperiment` carries that private snapshot and `has_valid_isolation_attestation()` verifies that the experiment fields still match the values attested after isolated execution. Mutating the candidate fitness after the run invalidates the attestation.

The donor runner suite tests:
- a successful process-isolated command and valid attestation;
- mutation of the evaluated result invalidating attestation;
- a callback that lies about isolation, which remains unattested and is rejected by the default safety gate;
- timeout, output-limit, non-finite fitness and thrown-exception failures.

The candidate runner header has no `run_isolated_command` API. Its suite tests acceptance of the callback-supplied `isolated=true` value instead of testing rejection of a lying callback. The candidate suite has 11 assertions / 80 lines; donor has 17 assertions / 91 lines.

## 4. Implications for adoption

Combined with the prior finding that the candidate `EvolutionExperiment` type has no isolation attestation and candidate `EvolutionSafetyGate::approve` does not inspect `policy.require_isolation`, the candidate path can treat an untrusted callback's Boolean as if it were isolation proof. The controller then has no cryptographically/structurally bound experiment attestation to verify against durable evaluation history.

The required boundary is not “callback says isolated”; it is a trusted process boundary producing a result whose experiment identity, proposal, fitness values and outcome are bound to the attestation and later matched against durable evaluation records.

**Disposition:** critical safety regression, directly demonstrated by candidate and donor tests. No runtime code was changed in this documentation pass.

## 5. Builder decision boundary

Do not simply copy the donor runner. Verify the actual supported platform isolation guarantees and the candidate process backend's policy. Preserve deterministic callback simulations for testing, but ensure they cannot claim process isolation or reach production adoption. Restore an explicit isolated-command path and tamper-evident attestation only as part of a coordinated design covering experiment evaluation, controller validation, adoption journal and recovery tests.

No donor code was copied. No source baseline was selected. DF-02 remains OPEN.
