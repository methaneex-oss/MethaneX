# DF-02 Native CI, Persistence Soaks and Learning-Trial Workflow Adjudication — 2026-11-27

**Scope:** frozen donor CI and manual learning/persistence workflow configuration, exact test commands, evidence artifacts and trust boundaries.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** workflows specify useful CI/soak/probe evidence, but no run at the frozen donor SHA is available in the current connector. Source inspection only.

## 1. Exact workflow refs

| Workflow | Blob SHA |
|---|---|
| `.github/workflows/brain-ci.yml` | `74182cd073ef4b1eec77f78800f96c337545007e` |
| `.github/workflows/jarvis-core.yml` | `60e6ec17ad6078bc8ad767c8375540629de0f143` |
| `.github/workflows/jbp-mem-001.yml` | `82cec28819357a26881584b4ceb951c258ea24ac` |
| `.github/workflows/jarvis-learning-seed-sweep.yml` | `f40a859a9b6b4f8138cd14df9fa09ad362f3515c` |
| `.github/workflows/jarvis-brain-probe-001.yml` | `812a0fdbb706ca4e12a9b31efc4f1e2af0a6e483` |
| `.github/workflows/dlt-001-long-run.yml` | `1706d3b41552f43f0e3b172b61da092f8fc053d7` |
| `.github/workflows/dlt-002-overnight-validation.yml` | `7ac465a333a2191cdc76e488bcafac4a8fe08802` |
| `.github/workflows/dlt-002-four-hour.yml` | `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` |

## 2. CI coverage

- **Brain CI:** path-filtered PR/push plus manual; Release configure/build/full CTest (30s per test) and Debug ASan+UBSan configure/build/full CTest (60s). Read-only contents permission. This is the strongest configured general CI workflow.
- **JARVIS Core Verification:** Debug configure/build/full CTest; no explicit workflow permissions and no test timeout.
- **Core CMake:** Release test executables explicitly keep assertions enabled (per separate CMake audit).

No current execution at frozen donor SHA is available. Previously recorded build-only workflow evidence is at older SHA and did not run CTest.

## 3. Persistence/learning trials

- **JBP MEM-001:** manual 30-minute soak, memory acceptance suites, separate-process train/verify persistence each iteration, 5-minute checkpoints, 90-day artifact. A failed step aborts due `set -e`; summary is emitted only on completed path. It is a bounded memory/persistence trial, not all-system validation.
- **JBP-001:** manual 5–30 minute probe; cross-process DLT persistence gate, six-phase partial-observation/noisy-outcome challenge, phase and resolved-prediction evidence checks, artifacts. It uses the DLT-002 executable; focused probe, not broad autonomy proof.
- **DLT-001:** manual or push on trial source; 2-hour, 60-second checkpoints, acceptance CTest gate, artifacts.
- **DLT-002 overnight:** manual only, 330-minute fixed-seed challenge, overwrite guard, six-phase smoke, persistence gate, artifacts.
- **DLT-002 four-hour:** manual, 1–240 minute full-suite/persistence soak; full CTest and separate-process train/verify each loop.
- **DLT-002 multi-seed sweep:** three independent seeds in parallel; manual duration choices 10–30 minutes, plus push trigger on trial/workflow file changes (push uses fallback 10 minutes). Metrics compare learner with two fixed-action baselines. It explicitly states the control is not a matched brain with learning disabled.

## 4. Evaluation and evidence limits

- Trials use a synthetic, changing environment with partial observation and outcome noise. They demonstrate behavior in that designed environment only; external-world transfer, autonomous perception/goal discovery and real action adapters are not established.
- The multi-seed sweep summary reports percentages but does not impose a pass/fail improvement threshold for the learner over the best fixed policy. Seed results are artifacts, not automatic statistical acceptance.
- JBP/DLT artifacts have 90-day retention; they are evidence of run outputs, not durable long-term source-of-truth.
- DLT-002 overnight metadata contains a fixed historical WAT finish-window string; it is descriptive metadata and not scheduling enforcement.
- Workflow action references use tags (checkout v4/v6, upload-artifact v4), not commit-pinned SHAs.
- `jarvis-core.yml` omits explicit token permissions; its effective permissions depend on repository defaults.
- The general Brain CI has no job-level timeout; individual CTest timeout is set.
- No workflow run was dispatched or executed in this audit.

## 5. Five review lenses

1. **Build/test:** Release and sanitizer CI are configured; soak/probe acceptance tests specified.
2. **Evidence:** trial metadata/checkpoints/CSV/artifacts exist by workflow design.
3. **Security/supply chain:** most workflows use read-only permissions; one core workflow lacks explicit permissions; actions are tag-pinned rather than immutable SHA.
4. **Capability:** synthetic trial results are scoped; no general autonomous capability is claimed.
5. **Hostile review:** older build-only evidence is not conflated with current CI or CTest; experiment results are not acceptance.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Eight exact workflow sources | Inspected |
| General CI configure/build/CTest | Configured |
| Sanitizer suite | Configured |
| Manual persistence/learning probes | Configured |
| Current donor SHA execution | Not available |
| Multi-seed statistical pass criterion | Gap |
| Action pinning/permissions/timeouts | Open hardening |
| Independent reviewer evidence | Blocked |
| DF-02 | OPEN |

Workflow adjudication remains **OPEN / NO AUTHORITY DECISION**. No DF-02 closure, Foundation clearance or Stage A authorization.
