# Nemotron Blind Fresh-Reader Rerun — Operator Runbook — 2026-11-10

**Purpose:** Run one new blind fresh-reader assessment against the final corrected PR #192 documentation revision.  
**Model:** `nvidia/nemotron-3.5-super-vl:free` via OpenRouter.  
**Workflow:** [Documentation Foundation — Blind AI Fresh-Reader Assessment](https://github.com/methaneex-oss/MethaneX/actions/workflows/documentation-foundation-ai-reader.yml)  
**Secret required:** repository Actions secret `OPENROUTER_API_KEY` (already configured for the previous successful run; do not paste the key into this file, chat, workflow inputs or logs).

## 1. Workflow readiness

The reusable workflow on `main` has been parameterized to accept an exact `target_revision` input rather than assessing a hard-coded historical SHA. Workflow update commits:

- `12ced8bf445309fcad0422194febcc7002e9621f` — parameterize exact target revision.
- `3b43ac1c5f6c7a9c070505a5d621e8e96645aa9e` — correct dispatch input YAML.
- `2fb25e968dd102bc20e5e41ef93726232ff88321` — fix the missing `os` import in the packet-assembly step.
- `f1ec646b2a4e0b9d3207c37883139c4708a1f7b2` — enforce exact Nemotron provider/model identity, require `finish_reason=stop` (missing values fail), reject refusal/tool-call responses, and record the validated assessment label in run metadata.
- `d7bb3b8f267a86b7f156a70716db6c143fdbbaa8` — pass the validated assessment label into the API-request step's environment.
- `8c530e8588c77f475af788ba97396bea8e6b712e` — include the exact PR #173/#174 decision-evidence extract and both accepted/current PR #174 specification revisions in the blind packet.
- `003c040187a6cd5a4307f08b36686d31f98f6bfc` — strengthen the reader rubric to test historical-snapshot handling, provenance classes, accepted/current revision distinctions, PR #191 graph interpretation and identifier glossary usability.

The workflow:
- checks out the exact supplied commit SHA;
- verifies that the checked-out HEAD equals the supplied SHA;
- builds a blind packet from the current repository entry points, the decision-evidence extract, and both the accepted and current status-clarified PR #174 specification revisions;
- excludes Builder audit/self-review/remediation and prior reviewer reports from the reader packet;
- invokes the NVIDIA Nemotron model through OpenRouter using the configured repository secret;
- disables reasoning output to preserve the completion budget;
- preserves the exact prompt, packet, manifest, raw assessment and sanitized run metadata;
- uploads evidence as a GitHub Actions artifact even when the assessment step fails.

The workflow timeout is 20 minutes. It does not create paid compute, GPU infrastructure, endpoints or scheduled jobs. The model endpoint previously reported zero cost; actual provider/account terms remain subject to OpenRouter's current service behavior.

## 2. How to launch

1. Open the workflow link above.
2. Select **Run workflow**.
3. Set branch/ref to `main` (the workflow definition is on `main`).
4. In **target_revision**, paste the exact current HEAD SHA shown at the top of PR #192. Do not use a branch name.
5. Keep assessment label as `post-review-corrections`.
6. Start the workflow once. Do not launch duplicate runs while one is queued or running.

The exact SHA must be copied from PR #192 after the Builder has finished all documentation changes intended for this reader test. Do not use the SHA recorded in this runbook as the target; the runbook is committed before the run and therefore cannot contain its own final resulting SHA.

## 3. Verify that Nemotron actually ran

Open the new workflow run and verify:

- The workflow run was created by `workflow_dispatch`.
- The checkout/verification step reports the exact target SHA.
- The packet assembly step succeeds and produces a manifest.
- The Nemotron API step completes with non-empty text and exactly `finish_reason=stop`; missing, null, truncated or other finish reasons fail the job.
- The workflow itself enforces exact provider `Nvidia` and model `nvidia/nemotron-3.5-super-vl:free`; missing or different identity fails the job after preserving the response and sanitized metadata.
- The supplied assessment label is validated and recorded in `run_metadata.json`; it does not alter the blind reader packet.
- The evidence artifact is uploaded.

A green workflow alone is not sufficient if the model response is empty, truncated, refused, or the wrong model/provider was returned. The workflow now fails closed for provider/model mismatch and for every completion reason other than the exact value `stop` (including a missing value); these are enforced checks, not merely operator inspection instructions. If the API fails, inspect the bounded diagnostic artifact; do not paste credentials into logs.

## 4. Retrieve and preserve the result

Download the workflow artifact. It should contain:

- `assessment_prompt.md`
- `reader_packet.md`
- `packet_manifest.json`
- `nemotron_assessment.md`
- `run_metadata.json`

The raw `nemotron_assessment.md` must remain unedited. Record the run ID, artifact ID, exact target SHA, model/provider, finish reason, token usage, completion timestamp and artifact SHA-256 in the repository evidence report.

## 5. Acceptance rubric

The assessment must be scored against the supplied packet, not for fluency. Require exact path/heading evidence. The result must be:

- **CLEAR** only if all critical project identity, scope, authority, phase, navigation, provenance and safety-boundary questions are answered correctly, with no material contradiction or unsupported inference.
- **PARTIALLY CLEAR** if one or more material misunderstandings or unresolved reader traps remain.
- **NOT CLEAR** if the reader cannot reliably establish the project's identity, current phase, authority boundary or safe next steps.

The repeat assessment is AI fresh-reader evidence. It is not a human session, formal independent review, Project Director decision, or gate acceptance. A CLEAR result may close the reader-comprehension criterion only after the Builder records the exact evidence and reconciles it with Grok's independent review.

## 6. What happens next

After the assessment:
1. The Builder records the exact run evidence and raw output in the PR #192 documentation branch.
2. Any material new reader finding is corrected or explicitly left open with a reason.
3. Grok performs the independent review of the then-current exact PR #192 HEAD using [GROK_INDEPENDENT_REVIEW_REQUEST_2026-11-10.md](GROK_INDEPENDENT_REVIEW_REQUEST_2026-11-10.md).
4. The Builder responds to Grok's findings directly in repository/PR records. The user is not a message relay.
5. Only after both evidence streams are reconciled is the exact-revision package submitted for Project Director decision.

**Authority boundary:** This workflow assesses documentation comprehension only. It cannot authorize Stage A, runtime implementation, PR integration, merge, rebase, retargeting, cherry-picking or final documentation-foundation acceptance. Stage A remains HELD; runtime implementation remains NOT AUTHORIZED.


## 7. Second-run outcome and corrective packet changes — 2026-11-10

The second run, [#42879721340](https://github.com/methaneex-oss/MethaneX/actions/runs/42879721340), assessed exact PR #192 revision `4a670636baf787ad4b1774bd306544c135868a04` and returned **PARTIALLY CLEAR (22/32)**. Artifact ID: `13793841106`. The execution passed strict provider/model identity and `finish_reason=stop` validation, but DF-09 comprehension acceptance did not pass.

The next packet version adds the repository-fetched PR #173/#174 decision evidence extract, both the accepted PR #174 baseline and current status-corrected revision, a controlling-current-status/historical-snapshot explanation, and an identifier glossary. The rubric now explicitly tests provenance classes, historical snapshot interpretation, PR #191 ancestry comparisons, and the provisional portal's non-authority status.

The Builder must finish the documentation corrections, verify the exact PR #192 HEAD and packet contents, and only then launch one new run. A CLEAR result is required; a green workflow or high numeric score alone is not enough.
