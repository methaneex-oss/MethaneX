# DF-02 Process-Isolation Child Lifecycle and Enforced-Control Adjudication — 2026-11-27

**Scope:** frozen donor `ProcessIsolationBackend::run` child/parent lifecycle, limit enforcement and tests; supplements the process-isolation variant report.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** process isolation provides process separation, timeout/output bounds and opt-in controls. Child cleanup and limit-enforcement evidence have concrete gaps. Source/test inspection only.

## 1. Exact refs

- Donor `core/cpp/src/process_isolation.cpp`: `8bb621fc986b4957f079bfdf99f4a1038949bc72`.
- Donor header: `a85f71694c446a430291025ac4fe033e18a59549`.
- Donor test: `6539da294b55e537ed28c08f3f72aff5f6b869e2`.

## 2. Enforced behavior

Backend creates pipe/forks, redirects stdout/stderr, attempts process-group setup, applies requested Linux network namespace/no-new-privileges/seccomp and optional privilege/filesystem controls, sets address-space/CPU/file-size limits, changes working directory, execs, and parent polls output/time deadline. Required isolation controls fail closed with exit 125. On timeout/output cap it sends SIGKILL to process group and child.

Default policy does **not** require network namespace, filesystem isolation or privilege drop; only no-new-privileges is required on Linux. `isolated=true` means child process created, not a complete sandbox certificate.

## 3. Concrete gaps

- **Descendant leak on normal exit:** parent breaks polling as soon as direct child is reaped. It does not terminate/wait for the process group on successful completion. A command that spawns a background child and exits can leave that descendant running. Process-group setup `setpgid` result is ignored, so group cleanup on timeout/output cap is not guaranteed if setup fails.
- **Resource-control enforcement:** `setrlimit(RLIMIT_AS/CPU/FSIZE)` return values are ignored. Limits can fail while result still reaches `completed=true`; the backend does not report which controls were actually applied. No NPROC/NOFILE/core-size limits or descendant accounting.
- **Environment/filesystem:** environment is inherited; PATH resolution uses `execvp` for names without slash. Working directory is not a filesystem sandbox unless optional chroot is required; command can access permitted host filesystem. No executable allowlist/hash or environment sanitization.
- **Network:** network namespace and syscall filter are optional. The filter blocks listed socket/send/receive calls but is not a comprehensive network sandbox and does not cover every network syscall; preexisting descriptors can be inherited. Platform controls differ (Apple rejects some requirements; Windows unsupported).
- **Fork safety:** vector argv is prepared before fork, but child still invokes C++ string operations and reads object state before exec. This is not fully reduced to async-signal-safe post-fork operations in a multithreaded process.
- **Result semantics:** `started/isolated/completed` only describe direct child/process boundary and exit result; no descendant-quiescence, actual resource-limit certificate or filesystem/network proof is returned.

These are source-derived risks; no adversarial reproduction was run.

## 4. Test evidence and gaps

Donor test checks successful output, output cap, timeout, required network namespace behavior and socket creation blocked by requested syscall filter. It does not test child/grandchild survival after normal exit, process-group setup failure, setrlimit failure, inherited descriptors, environment/PATH, network bypass syscalls, filesystem access, CPU/memory enforcement or platform matrix. Tests not executed.

## 5. Five review lenses

1. **Semantics:** timeout/output kill path and opt-in controls compared.
2. **Build/test:** source and test inspected; no native run.
3. **Security:** descendant lifecycle, incomplete controls and inherited environment/descriptors remain.
4. **Capability:** isolated process is not equivalent to hermetic sandbox.
5. **Hostile review:** `isolated` Boolean qualified; no safety certification claimed.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Exact donor backend/test | Verified |
| Timeout/output control | Source/test inspected |
| Normal-exit descendant cleanup | Gap |
| Process-group setup/enforcement | Gap |
| Resource-limit result evidence | Gap |
| Environment/FS/network hardening | Open |
| Adversarial/platform tests | Open |
| Native execution | Not performed |
| DF-02 | OPEN |

Process isolation remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
