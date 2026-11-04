# Gate A — Workflow Continuity Matrix

**Date:** 2026-11-04  
**Comparison:** Five current-main workflows against the candidate PR #156 integration tree  
**Status:** Static workflow disposition; no workflow execution or CI equivalence claim

| Current-main workflow | Candidate state/evidence | Capability preserved? | Required disposition |
|---|---|---|---|
| `.github/workflows/dlt-002-four-hour.yml` | Exact same blob `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` | Yes, file identity only; runtime pass not established | Unchanged; retain |
| `.github/workflows/jbp-mem-001.yml` | Candidate blob `82cec28819357a26881584b4ceb951c258ea24ac`; main blob `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f` | Partial; candidate lacks `source_ref` input and explicit tested-commit metadata | Adapt reproducibility controls if candidate selected |
| `.github/workflows/jarvis-learning-mechanisms.yml` | Absent in candidate. Main has 35 mechanism/test gates plus integrated changing-environment trial. All 35 target names occur in candidate CMake blob `0251936730f82a7a8c928fa31dfe1d7effc83d91` | Target-name registration only; build/pass equivalence not established | Preserve workflow capability or explicitly replace with equivalent trigger, test set, changing-environment trial, and artifacts |
| `.github/workflows/jbp-brain-int-001.yml` | Absent in candidate. Main runs five integrated suites plus persistence and DLT-002. Candidate JBP-001 overlaps persistence/DLT-002 but not the five integration suites | Partial, not equivalent | Preserve five integrated suites and matching run semantics through an explicit adaptation |
| `.github/workflows/jbp-learning-002.yml` | Absent in candidate. Main runs three independent DLT-002 trials with configurable source ref and seed base. Candidate seed sweep uses same long-run executable with three fixed seeds but lacks source-ref and seed-base controls | Partial, not identical | Preserve independent trials and reproducibility controls; document any deliberate replacement |

## Per-workflow evidence requirements

For each workflow, the final implementation decision must compare:
- event triggers and branch/ref filters;
- source-ref and tested-commit identity;
- runner/environment and dependency setup;
- configure/build commands and target set;
- test arguments, trial count, seeds and changing-environment behavior;
- timeout/retry/failure semantics;
- artifact/log publication and retention;
- permissions and secrets exposure;
- workflow dependencies and required status checks.

## Precision limits

- Presence of 35 target names in candidate CMake is static registration evidence only.
- Same workflow blob is file-identity evidence only, not proof it ran or passed on the candidate.
- A candidate workflow with overlapping commands is not equivalent unless trigger, ref, seed, suite, trial, failure and artifact semantics are also preserved.
- No workflow was edited or executed under the current authorization.

**Disposition:** One exact file match, one reproducibility-control adaptation, and three absent workflows with only partial or target-level overlap. Workflow continuity is not yet closed. Gate A remains NOT CLEARED.
