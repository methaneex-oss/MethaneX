# Test / Verification Evidence Report — [Capability or Change]

**Status:** Planned / not run / passed / failed / blocked / inconclusive  
**Test owner:** [Identity / role]  
**Date:** YYYY-MM-DD  
**Repository:** owner/repository  
**Branch:** [Branch]  
**Tested commit:** [Full immutable SHA]  
**Related PR / issue:** [Link]  
**Requirement / scenario IDs:** [Exact identifiers and source specification revision]

## 1. Objective and scope

[What behavior or invariant is being verified? State what this test does not establish.]

## 2. Test environment

| Field | Value |
|---|---|
| OS / image | [Exact version] |
| Compiler / toolchain | [Exact version] |
| Runtime | [Exact version] |
| Dependencies | [Lockfile / versions / image digest] |
| Build configuration | [Flags, target, preset] |
| Hardware / execution environment | [Relevant details] |
| Environment differences | [Differences from expected environment] |

## 3. Test selection

| Test ID / name | Source path | Registered target / suite | Requirement covered |
|---|---|---|---|
| [ID] | [Path] | [Target] | [Requirement/scenario] |

Distinguish test source, test registration, test selection and actual execution.

## 4. Commands executed

Record exact commands, working directory, relevant environment variables (excluding secrets), and whether each command completed.

```text
[Exact command]
```

## 5. Results

| Test / command | Expected result | Observed result | Status | Evidence |
|---|---|---|---|---|
| [Name] | [Expectation] | [Observed output] | Pass / Fail / Skip / Blocked | [Log/artifact link] |

Include totals and explain skipped, flaky, quarantined or non-deterministic tests. Attach or link raw logs and reports where available.

## 6. Failures and anomalies

[For each failure, provide the exact error, first causal failure if known, reproduction conditions, relevant logs, and whether it is a test defect, environment issue or product defect. Do not guess at root cause.]

## 7. Coverage and interpretation

- **Verified:** [Specific behaviors/invariants demonstrated.]
- **Not verified:** [Adjacent behavior, scenarios or integrations not tested.]
- **Inconclusive:** [Evidence insufficient to decide.]
- **Regression risk:** [Relevant untested boundaries.]

Passing tests do not by themselves prove complete subsystem integration, general learning capability, production readiness or gate acceptance.

## 8. Reproducibility

[Steps for an independent person to reproduce the exact run, including artifact locations and any data/setup prerequisites.]

## 9. Limitations and provenance

[Record missing logs, incomplete runs, inaccessible artifacts, unpinned dependencies, untested platforms and other limits.]

**Authority boundary:** Test execution and this report do not themselves authorize implementation, deployment, gate clearance or acceptance of the capability. Record the decision separately.

---
**End of test evidence report.**
