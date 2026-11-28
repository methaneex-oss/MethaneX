# DF-02 Process-Isolation Variant Adjudication — 2026-11-27

**Scope:** exact candidate/donor and 13 historical alternate blobs for `core/cpp/src/process_isolation.cpp`, plus exact public header, runner, and test-contract evidence.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 frozen HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** semantic and trust-boundary differences mapped for this cohort; path remains OPEN. Frozen candidate/donor exact backend refs were not executed; a third-lineage e737 backend/header variant passed historical CI tests.

## 1. Exact content inventory and owner grouping

The frozen discovery artifact (workflow 45470173876, artifact 14956148301, SHA-256 `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`) identifies 15 distinct blobs for this path: candidate, donor, and 13 alternates. All 15 source contents were present in the artifact's `consumer_blob_sources.jsonl` and fetched/inspected. The artifact owner rows report 193 unique tip-presence records for the path; these are refs/tips, not 193 independent implementations.

| Blob SHA | Role | Tips | Owner branches (representative exact names) |
|---|---|---:|---|
| `eac7a12fafe36b6c5f463ad0a41caa3bb835a61c` | Candidate | 135 | architecture/brain-foundation-planning-20261103; chore/agent-engineering-workbench; chore/reset-engineering-agent-layer; other 132 refs |
| `8bb621fc986b4957f079bfdf99f4a1038949bc72` | Donor | 33 | ci/priority-one-provenance-validation-20261031; ci/priority-one-validation-20261031; docs/brain-constitution-planning-readiness-2026… |
| `0bccc6f8b54840a48bea08836099ad39f47a6a37` | Alternate | 1 | fix/evolution-lifecycle-review-20261029 |
| `152f67f2ad88434a511721dc6602b1c6ac60f84f` | Alternate | 1 | fix/trusted-evolution-lifecycle-20261029 |
| `2f56f418e6933d33ad6e1eb240f39238d6db2ac9` | Alternate | 1 | fix/evolution-lifecycle-ci-tests-20261029 |
| `43d4d50e8148d063fcc2ab4e3a8679243dbb2c2e` | Alternate | 1 | fix/evolution-evaluation-lifecycle-20261029 |
| `6da14fe42046346ec932ff3872a2469ef6a608f3` | Alternate | 6 | feat/prediction-developmental-validation-20261030; fix/evolution-authenticated-evidence-20261030; fix/evolution-authenticated-replay |
| `85f06a858194215de889597ce60f7c7e1922fc6f` | Alternate | 2 | fix/evolution-evaluation-lifecycle-ci-20261029; fix/evolution-lifecycle-trust-20261029 |
| `8c8019f1d3701cceb210baac6a2ffb11e28956d3` | Alternate | 1 | fix/evolution-trustworthy-lifecycle-20261029 |
| `9592030cd4f8b3b1c3ab465b06adbd2ff5ba83e9` | Alternate | 1 | fix/evolution-isolation-review-remediation-20261029 |
| `96c62072ba1d4523633c8bed80123288d4ac2dfd` | Alternate | 2 | feat/evolution-adoption-journal; feat/evolution-isolation-hardening |
| `98ddc6ffbfb93b24404c8ba507df54d9e17099b1` | Alternate | 1 | fix/evolution-executable-path-fd-isolation-20261029 |
| `a38de0ef4b28006c1f71ff79ff33c23a79451a89` | Alternate | 2 | fix/evolution-lifecycle-trust-final-20261029; fix/evolution-lifecycle-verified-20261029 |
| `f1d172156db612724460bc95d634e9aa6201d1ca` | Alternate | 5 | fix/evolution-lifecycle-final-review-20261029; fix/evolution-lifecycle-ready-20261029; fix/evolution-lifecycle-reviewed-20261029; other 2 refs |
| `fc64cd30b1ee06371c7e7a7fd72c9f0fb5d2cb85` | Alternate | 1 | fix/process-isolation-path-fd-20261029 |

**Lineage caution:** owner branch/tip metadata establishes where exact blobs were observed, not authorial intent, authority to retain/merge, or semantic parentage. Branch-tip count must not be interpreted as independent review or implementation maturity.

## 2. Candidate/donor source comparison

The frozen candidate and donor have the same core isolation-control architecture and public header blob (`a85f71694c446a430291025ac4fe033e18a59549`):

- Unix process launch via `fork`, process-group setup, stdout/stderr capture through a pipe, deadline polling, timeout and output-cap termination, and `waitpid` reaping.
- Linux optional network namespace (`unshare(CLONE_NEWNET)`), no-new-privileges, a seccomp filter denying a set of networking syscalls, optional UID/GID drop, optional `chroot`, and RLIMIT address-space/CPU/file-size controls.
- Requested unavailable controls fail the child path with exit 125. Non-Unix/Apple targets return unsupported; Apple rejects the Linux-only requested controls.
- The public configuration makes these controls opt-in; default values do not require network namespace, filesystem isolation, privilege drop or syscall filter. The default no-new-privileges flag is true, but platform-specific handling differs.

Material candidate/donor deltas:

1. **Pre-fork argv preparation:** donor constructs the argv vector before `fork`; candidate allocates and fills the vector inside the child. Donor's comment identifies the async-signal-safety/deadlock hazard of allocation after fork from a multithreaded parent. This is a real robustness correction, not a change in evaluation policy.
2. **Executable invocation:** donor uses `execv` for executable strings containing a slash and `execvp` only for bare names; candidate calls `execvp` for all paths. The donor split avoids PATH lookup for path-qualified executable names. This is a modest but relevant executable-resolution change.
3. **Isolation result semantics:** both implementations set `result.isolated = true` after fork, before the child proves that requested controls succeeded; failure of required controls is reflected in child exit 125 and incomplete execution. Therefore the result field is not an independent attestation that every configured control was enforced. Downstream code must require completed/zero-exit and validated evidence; the boolean alone is insufficient.
4. **Resource limits:** both implementations call `setrlimit` for memory, CPU and file size, but ignore the return values. The source does not prove those limits were applied successfully. When a caller treats these as mandatory safety limits, this is a contract gap.
5. **Scope of network restrictions:** the seccomp filter covers a listed set of socket-related syscalls and returns ALLOW for others; it is not by itself a complete network-denial proof. The network namespace and syscall filter are separate optional controls. Enforcement requires environment-specific validation.
6. **Process containment:** both establish a child process group and kill the group/child on timeout or output overflow, but no inspected test establishes containment of hostile descendants, race-resistant cleanup, descriptor inheritance, or all termination paths.

The candidate/donor source is otherwise near-identical in the core command-run path. Do not infer that donor adoption is necessary for this file; the pre-fork allocation and executable-resolution deltas are concrete, but this exact comparison alone does not establish a complete preferred owner.

## 3. Historical alternate families — exact-content distinctions

All 13 alternates retain the basic fork/pipe/process-group/deadline/output-cap/reap mechanism. Feature extraction and focused source inspection separate these semantic changes:

- **Pre-fork argv preparation:** donor and multiple late lifecycle alternatives contain the pre-fork preparation correction; candidate and some earlier alternatives construct argv after fork.
- **Path resolution before filesystem changes:** blob `98ddc6ffbfb93b24404c8ba507df54d9e17099b1` on `fix/evolution-executable-path-fd-isolation-20261029` resolves path-containing executables with `realpath` before the child changes working directory/chroot, reducing the risk that a relative executable path resolves to a different file than the trusted runner fingerprinted. This is a specific behavior delta; filesystem races and identity pinning still require analysis.
- **File-descriptor hygiene:** the same later variant includes a Linux `close_range`-guarded path before exec (where available); other versions differ in descriptor cleanup. The actual guarantees depend on platform/kernel and fallback behavior.
- **Trusted evaluator path:** blob `152f67f2ad88434a511721dc6602b1c6ac60f84f` adds the Linux-only callable-evaluator process path, using the inherited repository-owned procedure rather than parsing arbitrary command stdout as evaluator authority. It fails closed on non-Linux and refuses callable filesystem isolation because no chroot contract is provided. It also applies RLIMITs, but source-level presence is not proof that every call succeeded.
- **Evaluator/executable trust:** some variants add trusted evaluator registration, executable fingerprinting, evidence/attestation and allowlist handling in related runner contracts. These concepts are not all owned by `process_isolation.cpp`; cross-file semantics must be reconciled with `evolution_experiment_runner.cpp`, `evolution_experiment.hpp`, coordinator/controller and the journal before a path-level disposition.
- **Sanitizer-aware control:** the path-FD variant contains sanitizer build guards around a child control, making behavior configuration-dependent. This needs CI matrix evidence; source inspection cannot establish that all sanitizer/platform combinations work.

This classification groups exact versions by material mechanism. It is not a full line-by-line semantic closure of every alternate: owner-tip histories, all source diffs, and retention/authority decisions remain open.

## 4. Exact cross-file test and registration evidence

The frozen candidate and donor process-isolation test sources are not byte-identical; the main suite differs in its configured memory limit. The syscall suite is byte-identical:

- `process_isolation_suite.cpp`: `78b764368de4d427c3196b26b57255edc422bf50`.
- `process_isolation_syscall_suite.cpp`: `cd347d277c84376c3a90ce4d95b31b4dbafde583`.

The suite asserts basic command success/output, output-cap rejection, timeout rejection, strict requested-control behavior, and (Linux) a socket-creation denial. It does **not** establish:
- privilege-drop or filesystem/chroot behavior;
- whether each RLIMIT actually applied;
- executable resolution/fingerprint races or FD leakage;
- descendant/process-group containment and cleanup;
- process crash, signal, cancellation, concurrency or host-resource exhaustion behavior;
- network bypass via untested syscalls or pre-existing inherited descriptors;
- cross-platform behavior beyond compile-time branches.

Candidate and donor register the same two process-isolation test targets in CMake. Both files are compiled into targets in the reported native-build workflow evidence, but CTest was not run. The CMake registration is reachability, not behavioral proof.

## 5. Consumer and dependency boundary

The source is consumed by the evolution runner's isolated-command path; the runner owns command-output parsing and the experiment-level attestation contract. The callable evaluator path also interacts with the experiment runner and trusted evaluator policy. This separation matters:

- `ProcessIsolationResult.isolated` is a backend result bit, not cryptographic attestation or a full sandbox certificate.
- `EvolutionExperimentRunner::run` accepts callback fixture results for the generic sandbox path but donor explicitly leaves callback runs untrusted/non-isolated.
- `run_isolated_command` requires backend result status, parses finite fitness output, sets experiment isolation state, and attests the result in the donor contract. That attestation is bound/validated at the experiment layer and must be reviewed alongside identity/evaluation/adoption.
- Process isolation by itself does not guarantee safe model mutation. Journal/controller evidence requirements are the separate authority gate.

The exact candidate/donor runner source blobs are respectively `83d3c26e589cd16151818774a81ccb62f9d514fc` and `0545662ea0ef865feb0527207fc4c32ecb50566e`. The corresponding runner test source blobs are `08888276d875ce5e55f421e828f1bb4f061d1ea5` and `307fe75b42f804d9bb2b0e8199df1e9cf773e3c6`. Those exact test-contract differences are already separately recorded in `DF02_EVOLUTION_TEST_CONTRACT_ADJUDICATION_2026-11-27.md`; this report cross-links rather than duplicates them.

## 6. Five review lenses — bounded cohort

1. **Semantics:** process creation, optional controls, result/attestation distinctions, executable-resolution behavior and runner trust boundary were compared at exact blobs. Material deltas identified; no closure.
2. **Build/test reachability:** production source and two test executables are CMake-registered at both frozen refs; exact candidate/donor test blobs match. Build workflow evidence exists for configure/build at a later documentation PR SHA, but no CTest execution. No independent build for every alternate.
3. **Security/trust:** false assurance risks include optional controls, ignored RLIMIT errors, incomplete syscall list, boolean isolation field set before control verification, descriptor inheritance and path/fingerprint race. These are source-review concerns requiring adversarial tests and threat-model decisions.
4. **Capability realism:** this is a useful bounded execution mechanism, not a general-purpose OS sandbox, container, VM, or secure untrusted-code service. Its practical protection depends on host privileges, kernel, platform, limits, executable trust and controls selected.
5. **Hostile review:** no donor preference inferred from version date; no source implementation changed; tests not mislabeled as executed; no baseline/adoption/retirement decision made.

## 7. Open obligations and disposition

| Obligation | State |
|---|---|
| Exact 15-blob content inventory and role counts | Completed for this slice; fetched artifact SHA verified |
| Candidate/donor source and public API comparison | Completed for bounded comparison |
| Historical alternates semantic grouping | Partial; key mechanisms grouped, all-owner lineage/authority not adjudicated |
| Reverse consumers/context | Partial; runner linkage inspected, full exact-context match table not closed |
| Test and CMake reachability | Source/registration confirmed; tests NOT RUN |
| OS sandbox threat model and adversarial tests | Open |
| RLIMIT enforcement and failure handling | Open |
| FD/descendant/process cleanup and path-race tests | Open |
| Platform/kernel matrix | Open |
| Provenance/retention/authority | Open |
| DF-02 / full 159-path ledger | OPEN |

**Disposition:** `core/cpp/src/process_isolation.cpp` remains **OPEN / NO AUTHORITY DECISION**. No implementation selected, adopted, retired or deleted. This evidence slice does not close DF-02, any Foundation gate, or authorize Stage A.

 
## Third-lineage e737 backend/header and historical CI — 2026-11-28

The e737cae7 branch does not use frozen donor backend blob 8bb621fc... or frozen donor header a85f7169... . It uses:
- process_isolation.cpp alternate blob 6da14fe42046346ec932ff3872a2469ef6a608f3 (282 lines);
- process_isolation.hpp alternate blob b0a44fb2dc25db5f6335893ecd93187513ec0e46 (67 lines);
- process_isolation_suite.cpp donor blob 6539da294b55e537ed28c08f3f72aff5f6b869e2 (46 lines / 8 assertions);
- process_isolation_syscall_suite.cpp shared blob cd347d277c84376c3a90ce4d95b31b4dbafde583 (16 lines / 1 assertion).

The e737 backend/header pair adds:
- sanitizer-aware RLIMIT_AS handling: RLIMIT_AS is skipped in ASan/TSan builds because instrumentation reserves large virtual address ranges; normal-build RLIMIT_AS, RLIMIT_CPU and RLIMIT_FSIZE failures exit 125;
- result.isolated remains false until the child exits, then is set when started and exit_code !=125, separating required-control failure from ordinary workload failure;
- default require_network_syscall_block changes from false to true;
- ProcessIsolationCommand adds evaluation_procedure_id, expected_executable_fingerprint and trial_index fields for trusted evaluator linkage.

The alternate still ignores setpgid and dup2 return values. In sanitizer builds, the memory address-space limit is intentionally not enforced but the result does not expose a distinct "memory limit skipped" capability state. The isolation bit is still inferred from exit_code !=125, so it does not prove that every ancillary control (for example process-group setup) succeeded. The basic process-isolation test does not assert RLIMIT failure behavior, sanitizer limit policy, the new command identity fields, or result.isolated semantics.

Historical e737 CI evidence:
- CTest #47 jarvis_process_isolation_suite passed;
- CTest #48 jarvis_process_isolation_syscall_suite passed;
- both tests passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; all five jobs report 71/71.
- e737 parent CMake is alternate blob 33197f92141a241ff0546af1bf81fbf177a1f3ab (64-source graph + OpenSSL Crypto), with donor test CMake cbfd1fde52fffa6eeac025da2b7ddcb5ab493261.

Test-source correction:
- Candidate process_isolation_suite.cpp blob 78b764368de4d427c3196b26b57255edc422bf50 and donor/e737 blob 6539da294b55e537ed28c08f3f72aff5f6b869e2 are both 46 lines / 8 assertions; they differ only in configured memory limit (candidate 64 MiB, donor/e737 256 MiB).
- process_isolation_syscall_suite.cpp blob cd347d277c84376c3a90ce4d95b31b4dbafde583 is identical across candidate/donor/e737.

The e737 CI result is for alternate backend/header 6da14/b0a44 plus donor main test and shared syscall test. It is not a pass result for frozen candidate backend eac7a12... or frozen donor backend 8bb621..., and does not close the descendant cleanup, unchecked setpgid/dup2, RLIMIT certification, path/FD race, inherited descriptor, platform or adversarial test gaps.

 
### Self-review correction: alternate isolation-result semantics are not fully tested

The 8-assert process_isolation_suite does assert isolated=true for successful execution, timeout and a child whose socket syscall is denied. It does not assert isolated=false when a required control fails with exit 125, and it does not inject setrlimit failures or verify the sanitizer-specific RLIMIT_AS skip. The statement above that the suite does not assert result.isolated semantics is therefore narrowed: it checks positive isolation results, but not the critical false-on-required-control-failure branch or whether every configured control was actually applied.
