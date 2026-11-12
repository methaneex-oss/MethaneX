# AI Role Terminology Audit — 2026-11-11

**Status:** Bounded audit completed; terminology corrections prepared on a dedicated branch.  
**Audit baseline:** default branch `main`, commit `8edc7cdfc886537d319d81cea04cdc9f3476044e`.  
**Change branch:** `docs/ai-role-terminology-audit-20261111`.  
**Scope:** Repository-facing role names, workflow display labels, and generic interface comments. This is not an architecture, implementation, model-selection, or provider-migration change.

## 1. Naming standard

Project records identify participants by their function, not by the consumer product or model brand through which a task was performed.

| Project-facing term | Meaning | Boundary |
|---|---|---|
| **Architecture & Engineering Builder** | Responsible for bounded architecture and engineering work authorized by the Project Director | A functional role; not a model identity |
| **Independent Reviewer** | A reviewer expected to challenge a specified revision independently and report evidence-backed findings | Use this role name in assignments, reports, and workflow-facing labels; do not substitute Builder self-review |
| **Blind Fresh Tester** | A separate, context-blind assessment role that tests what a fresh reader/tester can establish from a bounded evidence packet | Not interchangeable with formal Independent Reviewer clearance |
| **Researcher** | Gathers and evaluates research evidence | Does not approve project decisions |
| **Verification Engineer** | Defines or executes bounded verification and records reproducible evidence | Does not grant architecture or project acceptance |
| **GPT-6** | Model identity, only where explicit model attribution is technically relevant and verified | Never use as a substitute for the Builder role |
| **AI assistant / assistant-facing** | Generic language for an assistant-facing interface or interaction | Use unless an interface is deliberately product-specific |

The Project Director retains project decision and acceptance authority. Role labels do not imply authority beyond the documented responsibility.

## 2. Audit method and evidence boundary

The audit used GitHub repository code search on `methaneex-oss/MethaneX` and fetched the relevant files at exact refs. It examined:

- `main` at `8edc7cdfc886537d319d81cea04cdc9f3476044e`;
- `.github/workflows/documentation-foundation-ai-reader.yml`;
- `.github/workflows/brain-foundation-blind-architecture-review.yml`;
- `interfaces/typescript/src/operator_session.ts`;
- selected documentation on the existing PR #192 branch `docs/whole-brain-planning-scope-correction-20261107`: the planning index, outstanding-work register, initial documentation-foundation audit, fresh-reader assessment report, and whole-Brain planning scope correction;
- the PR #192 description, which contained two provider-branded phrases in places where the project role should be named.

This was a bounded terminology audit, not a claim that every historical branch, PR description, issue, artifact, or repository object was exhaustively searched.

## 3. Findings

### 3.1 Generic interface comment used a product name

At the audit baseline, `interfaces/typescript/src/operator_session.ts` described a generic supervised operator session using a consumer-product-specific label. The interface itself is not product-specific. The product reference was therefore unnecessary and made the abstraction appear coupled to a consumer product.

**Disposition:** corrected to “assistant-facing”. No interface behavior, type, runtime boundary, or authorization semantics changed.

### 3.2 Workflow display labels used a model/vendor name as a project role

The two active blind-assessment workflows exposed the model/vendor name in job and step labels and, in the documentation-reader workflow, in the assessment artifact filename/prefix. This conflated the role being performed with the implementation/provider used to execute it.

**Disposition:** changed the visible role labels to **Blind Fresh Tester** and renamed the human-facing assessment output/artifact labels accordingly.

### 3.3 Historical planning records contain model/product attribution

The selected PR #192 planning and evidence documents contain numerous historical references to external model identities, provider attribution, prior review submissions, and conversation provenance. Some of those details explain why a review did or did not qualify, which exact model endpoint was reported by an API, or what evidence was available at a historical decision point.

**Disposition:** not bulk-rewritten in this pass. Historical evidence must not be silently altered in a way that falsifies attribution, obscures the limits of an earlier assessment, or changes the meaning of a prior Project Director decision. The new role standard governs current and future project-facing labels. Where a historical model/provider identifier is necessary to reproduce or qualify an event, it belongs in provenance metadata, not as the participant's project role.

### 3.4 PR metadata used a provider name as a reviewer-role shorthand

The PR #192 description used a provider-branded name in two phrases describing the status and limitations of an earlier review attempt. That wording made the provider appear to be the project role. The underlying historical limitation remains relevant, but the project-facing role is **Independent Reviewer**.

**Disposition:** updated the two phrases in the PR #192 description to use **Independent Reviewer assessment** and neutral wording for the historical attempt's limitations. This does not claim that the earlier attempt was re-performed, qualified, or upgraded. Historical reports and evidence artifacts retain technical attribution where needed to preserve provenance.

The bounded default-branch code search returned no other matching reviewer-brand code result. This is not an exhaustive search of every historical branch, PR, issue, or artifact.

## 4. Changes made on this branch

| Path | Change |
|---|---|
| `.github/workflows/documentation-foundation-ai-reader.yml` | Workflow/job/step labels and assessment artifact naming now use **Blind Fresh Tester** terminology |
| `.github/workflows/brain-foundation-blind-architecture-review.yml` | Workflow title no longer implies a formal Independent Reviewer role; job/step labels, assessment persona, and output filename use **Blind Fresh Tester** |
| `interfaces/typescript/src/operator_session.ts` | Generic product-specific interface comment changed to “assistant-facing” |
| PR #192 description | Two provider-branded role phrases replaced with **Independent Reviewer** role wording; historical limitation preserved |
| This audit | Records the naming standard, findings, scope, changes, and historical-provenance boundary |

## 5. Model and provider provenance is intentionally retained

The workflows still require the configured API model identifier for request routing and response validation. Machine-readable run metadata must continue to record the provider/model values actually reported by the API, along with the target revision, finish reason, and relevant usage metadata.

This is not a project-facing role label. Removing or falsifying these fields would weaken reproducibility and evidence integrity. The workflow's visible name is **Blind Fresh Tester**; its configured model identity remains a technical execution detail.

## 6. Non-changes and authority boundary

This audit did not:

- change architecture, cognitive mechanisms, specifications, or project decisions;
- alter the distinction between a Blind Fresh Tester assessment and a formal Independent Reviewer assessment;
- claim that a blind assessment is an independent review or Project Director acceptance;
- change API providers, model endpoints, credentials, or secrets;
- alter historical reviewer findings, decision records, or evidence artifacts; technical provenance remains where it is necessary to explain past evidence;
- modify PR #173, PR #192, or PR #193 source branches;
- merge a pull request, clear a gate, start implementation, or authorize runtime work.

## 7. Verification required before integration

Before this branch is integrated, verify the diff and workflow syntax, then confirm that:

1. All visible workflow job/step labels use **Blind Fresh Tester**.
2. The two workflow prompts accurately describe the Blind Fresh Tester task and do not claim Project Director authority.
3. Technical provider/model routing and provenance checks remain intact.
4. The generic operator-session comment no longer implies a product-specific integration.
5. No runtime behavior or authorization boundary changed.
6. The PR #192 description uses **Independent Reviewer** as the role name without rewriting historical evidence attribution.

A successful terminology edit is not evidence that either assessment workflow has executed successfully. No workflow run is claimed by this audit.


---

## 8. Post-audit workflow security and diagnostics correction — 2026-11-11

A subsequent Builder review of the exact PR #195 workflow revision found two defects that the original bounded terminology audit had not covered:

1. The manually supplied `target_revision` input was interpolated directly into a Bash `run:` script. This created an avoidable script-injection surface.
2. The response parser did not handle all observed response shapes. It only extracted list content blocks with a `text` member, did not fall back to `message.output_text` or legacy choice text, and joined list blocks with a literal escaped separator rather than actual newlines. It could therefore reject a usable assessment or produce malformed formatting.

### 8.1 Corrections applied

The workflow now:

- validates `TARGET_DOCS_SHA` as a full 40-character lowercase hexadecimal SHA;
- compares the checked-out commit to the environment variable rather than interpolating the input into shell source;
- captures HTTP status and request ID before parsing the response;
- safely extracts string content, text/content blocks, `message.output_text`, and legacy choice text;
- records sanitized response-shape, provider/model, finish-reason, refusal/tool-call, reasoning-presence and usage metadata before deciding whether the assessment is usable;
- saves textual assessment output before completeness and model-identity checks, so an incomplete response remains inspectable;
- requires the expected provider/model, `finish_reason=stop`, no refusal/tool calls, all sections A–H, and at least 1,500 characters;
- excludes the raw response body, API key and reasoning content from evidence artifacts.

### 8.2 Exact revisions and bounded verification

- PR #195 head before the workflow correction: `c2727eaf09222d8cb4884f84ffd2bd0641621d53`.
- Workflow blob before correction: `2217f6629bf65a43460ba645693d31b6ee6bd6fb`.
- Workflow correction commits: `b1ab02e305cbe04952fa109859f92869ab9ae4a9` and `c2727eaf09222d8cb4884f84ffd2bd0641621d53`.
- Resulting workflow blob: `885f9fa7accf825ac1360f5115a81e66d668ad74`.

Static source checks against the resulting blob confirmed the SHA validation, environment-only shell comparison, all response-shape fallbacks, actual newline joining, metadata capture, and saving the response before completeness validation. This is static inspection only: the workflow has **not** been dispatched or executed. No successful Blind Fresh Tester assessment is claimed.

### 8.3 Remaining verification

Before PR #195 integration, verify workflow syntax and run the workflow against a deliberately controlled test revision, including empty content, list content blocks, `output_text`, legacy text, truncated output, wrong provider/model, refusal/tool calls and a valid A–H response. Confirm the artifact contains only the intended sanitized evidence. PR #195 remains a terminology/workflow proposal, open and unmerged; this correction does not merge PR #194, authorize workflow execution, clear DF-09, or change any Project Director decision.

### 8.2 Follow-up correction — target revision metadata environment

A second static pass found that the assessment-request step reads `TARGET_DOCS_SHA` when writing `run_metadata.json`, but the variable was only exported in the preceding packet-assembly step. GitHub Actions step environments are isolated, so the assessment step would otherwise fail with a missing environment variable after receiving the provider response.

**Correction:** exported `TARGET_DOCS_SHA: ${{ inputs.target_revision }}` in the assessment-request step as well. The workflow now passes the exact requested documentation revision to both packet assembly and response metadata. The updated workflow blob is `3cbe2e54fb9500f78b2842801e8371641ee24ddc` in commit `5a813f8febd0a0b0e5e0365439d5182e79833c15`.

**Verification boundary:** static source inspection confirms every `TARGET_DOCS_SHA` reference has the required step-level environment variable. The workflow has not been executed; this is not runtime verification or a Blind Fresh Tester result.


## 9. Final Builder correction — sanitized HTTP failure evidence and PR #194/#195 reconciliation — 2026-11-11

A further exact-source review found that the HTTP-error branch still persisted up to 4,000 characters of the provider response body in `api_error.txt`. That contradicted the stated evidence-minimization boundary: provider error bodies are untrusted and may echo request data. The generic exception path also persisted `str(exc)`, which was not necessary to diagnose the failure and could expose request details.

### 9.1 Correction applied to the consolidated PR #195 workflow

The workflow now reads the HTTP error body only in memory and persists only allowlisted, type-checked, length-bounded metadata: HTTP status, bounded request ID, error type/code, provider and model. It records explicit false flags for raw-response, API-key and reasoning persistence. Generic exceptions persist only the exception class, not the exception message. The raw response body and raw exception message are not written to the evidence artifact.

Exact workflow correction commits:
- `59cc1fcadb1b8669b1bc7703f07cf443469348d6` — initial removal of raw HTTP/generic exception text persistence.
- `cf8dc19cff9997fddd730bec1086c4c3989456b3` — bounds all persisted diagnostic string fields.

Final workflow blob after these writes: `26c9fd6deb07dfed312d58f0ce82ccb3fa01f268`.

### 9.2 PR #194 versus PR #195

Both open draft PRs modify `.github/workflows/documentation-foundation-ai-reader.yml` on separate branches. PR #194 adds response-shape diagnostics and completeness handling but does not include PR #195's full target-SHA shell-injection correction, model/refusal/tool-call validation, Blind Fresh Tester terminology alignment, or the final bounded error-evidence handling.

PR #195 contains the consolidated response extraction paths (string content, text/content blocks, `message.output_text`, and legacy choice text), safe target-SHA handling, role terminology, and the sanitized diagnostic correction above. Its implementation is the preferred consolidated candidate for further static verification. PR #194 should not be merged or cherry-picked alongside PR #195; its useful response-shape behavior is already represented in the PR #195 workflow, while raw provider error-message persistence is intentionally not carried forward.

This is a Builder reconciliation recommendation, not a merge, close, review, or Project Director disposition. Both PRs remain open/draft/unmerged until the authorized disposition is made.

### 9.3 Verification boundary

Static source assertions were re-run against the final workflow blob for full-SHA validation, environment-only shell comparison, response-shape fallbacks, bounded sanitized HTTP diagnostics, omission of raw exception messages, provider/model identity checks, refusal/tool-call checks, finish-reason validation, A–H/1,500-character completeness checks, and unconditional artifact upload. This does not validate GitHub Actions YAML parsing or execute the workflow. No Blind Fresh Tester inference or assessment is claimed.


### 9.4 Follow-up correction — bound successful-response metadata and HTTP error reads

A further Builder pass found that successful-response metadata still copied several provider-controlled fields without type and length bounds. This included provider/model identifiers, response IDs, timestamps, finish-reason values, content-block type labels, reasoning-token counts, and usage values. The HTTP-error branch also read the entire provider error body into memory even though it did not persist the body.

**Correction:** commit `0f74fe99ac953044bc4c285d832205b2da85426d` adds allowlist helpers that:
- retain only bounded strings for provider/model/request/response identifiers and finish-reason labels;
- retain only finite numeric values for timestamps, token counts, and usage fields;
- constrain content-block type labels to short strings;
- cap the HTTP error-body read at 65,536 bytes before parsing the allowlisted error fields;
- continue to exclude raw response bodies and raw exception messages from evidence artifacts.

**Static verification against workflow blob** `1166ce7c66e939f4d6106dba2bbd9756fa96c03a` confirmed the bounded metadata helpers, numeric allowlists, capped HTTP error-body read, absence of raw exception-message persistence, and continued full-SHA/environment-only handling. This remains source inspection only. YAML parsing, GitHub Actions execution, provider behavior, and artifact inspection have not been performed; no workflow runtime pass is claimed.


### 9.5 Additional resource-bound correction

The same pass tightened two edge cases in the metadata hardening:
- Successful provider response bodies are now read with an 8 MiB maximum; oversized responses fail closed instead of being fully buffered and parsed.
- Numeric metadata accepts only finite values within a conservative magnitude bound. Integer values are handled without converting arbitrary-size integers to floating point, avoiding overflow during sanitization.

The final workflow correction is commit `0dfceaaf29c3a93cbc8f52f8ba7bce44ee44adb3`, workflow blob `f4373401f07d8550f39eb9bb8b252eac31f03783`. Static checks establish the presence of these bounds only; they do not replace YAML validation or execution tests.


## 10. Blind architecture workflow hardening — 2026-11-12

A Builder review of the second workflow in this PR found that the earlier terminology-only edit had not carried over the response-safety and evidence-validation protections added to the documentation-reader workflow. The architecture-assessment workflow still persisted raw provider HTTP error text and generic exception messages, had no response-size bound, handled only a narrow subset of response shapes, and did not reject wrong-model, refused, incomplete or structurally truncated assessments.

### 10.1 Correction

The architecture workflow now:

- bounds successful provider response reads to 8 MiB and HTTP-error reads to 64 KiB;
- persists only allowlisted, bounded diagnostic fields for HTTP failures and only the exception class for generic failures;
- never persists raw provider error bodies, raw exception messages, API keys or reasoning fields;
- extracts textual assessment output from string content, text/content blocks, message.output_text and legacy choice text;
- bounds provider/model/request/response identifiers, finish-reason labels, content-block labels and numeric usage metadata;
- saves any returned textual assessment and sanitized run metadata before validation, so an incomplete or misattributed response remains inspectable;
- requires the expected provider/model, finish_reason=stop, no refusal, no tool calls, all required A–K sections and at least 2,000 characters before treating the assessment step as successful.

### 10.2 Exact revision and static checks

- PR #195 head before this correction: 9d0255041c1d3c41c1b6a9f9e373f2bf673184cd.
- Architecture workflow blob before correction: eb87ba8e17a6dee6b992be50a3a95463621559fb.
- Correction commits: d190dc8a90e9643fd7494139b699475638691ba3 and 87087800ba8a24b07066656691fdc0ef16eae6f5.
- Final architecture workflow blob: 8f7f94c87c905c033ac4385ca1a977f30b41478c.
- The workflow-hardening change itself is commit `87087800ba8a24b07066656691fdc0ef16eae6f5`, with final workflow blob `8f7f94c87c905c033ac4385ca1a977f30b41478c`. Subsequent audit-only commits may advance the PR head without changing this workflow blob; always re-fetch the live PR head and the workflow blob before any future review or execution.

Static source assertions against the exact final workflow confirmed full-SHA and label validation, environment-only target handling, response and diagnostic read bounds, all four response extraction paths, bounded metadata, expected provider/model checks, finish/refusal/tool-call validation, A–K section checks, and saving output before validation.

### 10.3 Verification boundary

This is static source verification only. GitHub Actions YAML parsing, workflow execution, provider response-shape tests, artifact inspection and a Blind Fresh Tester assessment have not been performed. The workflow remains unexecuted; no architecture-review verdict, gate clearance or Project Director acceptance is claimed.

## 11. Live revision reconciliation — 2026-11-12

The documentation-reader workflow was subsequently refreshed so its pinned architecture and specification inputs match the then-current proposal heads. This supersedes the earlier reader-workflow blob reference in section 9.5 for current-source identification; it does not invalidate that section's historical description of the preceding correction.

- Refresh commit: `aac0a58fad2638a71dfa8e58b02437258bae148c`.
- Updated documentation-reader workflow blob: `e6d493080d5aa93c695c33d05eab02c1ecf7b1e3`.
- Pinned PR #173 architecture proposal: `7e9481677197cf82df31bbe08984fa5d58644d98`.
- Pinned PR #174 corrected specification proposal: `16a82663d6a421575234b5f8f4ea0c5ad4f735cf`.
- The architecture-assessment workflow remains at blob `8f7f94c87c905c033ac4385ca1a977f30b41478c`; its hardening commit remains `87087800ba8a24b07066656691fdc0ef16eae6f5`.
- PR #195 HEAD at the time of this reconciliation was `aac0a58fad2638a71dfa8e58b02437258bae148c`. This audit-only update advances the branch head after that workflow-refresh commit; re-fetch the live PR head before any later review or execution.

The workflow diff at `aac0a58` changes only the fetched/pinned proposal commit identifiers and their corresponding source labels. It does not change prompt content, response parsing, metadata handling, validation thresholds, permissions or artifact handling.

**Verification boundary:** exact commit diff and resulting file blob were inspected. No YAML parser, GitHub Actions execution, provider call, artifact inspection or Blind Fresh Tester assessment is claimed. The workflow remains a proposal and is not authorized for dispatch by this audit.

## 12. Additional workflow hardening and bounded synthetic verification — 2026-11-12

A further Builder review identified improvements needed before either assessment workflow can be considered ready for an authorized run.

### 12.1 Corrections applied

Both workflows now:

- validate the full 40-character lowercase target SHA and bounded assessment label in a dedicated step **before checkout**, while retaining the later exact-HEAD comparison;
- set `persist-credentials: false` on checkout because neither workflow pushes to the repository;
- explicitly instruct the assessment model to treat repository documents as untrusted evidence and to ignore any instructions or role claims embedded in those documents;
- reject boolean and out-of-range integer values in provider error-code metadata.

The documentation-reader workflow additionally changed its A–H completeness check from substring matching to anchored line-start section matching. A stray inline occurrence of `A.` or `B.` can no longer satisfy the required section check. The validator accepts ordinary section headings and Markdown headings/bold prefixes, while still requiring all eight sections.

### 12.2 Exact revisions

- Reader input/prompt/metadata hardening commit: `5a1b099d0ecac2fb211d1f055ac200b21bc54189`.
- Reader section-regex correction commit: `4fe38c6c0e98ec76bc295757a1390fe6e59a8f39`.
- Architecture workflow input/prompt/metadata hardening commit: `324a8159bbae17dd9b5372ca26c847753a287586`.
- Current documentation-reader workflow blob: `7d202c8c3e8ea29a7b40ec70baafbc75d07a34e2`.
- Current architecture-assessment workflow blob: `96dc2971503af022e4d247d4be07d257aec5d7db`.
- PR #195 HEAD at the time of this update: `324a8159bbae17dd9b5372ca26c847753a287586`. This audit-only update advances the branch after that workflow commit; re-fetch live metadata before further review.

### 12.3 Verification performed

- Re-fetched both exact workflow blobs and ran source assertions for pre-checkout input validation, environment-only shell handling, disabled credential persistence, bounded successful/error response reads, sanitized error handling, response-shape fallbacks, bounded metadata, exact provider/model checks, completion/refusal/tool-call checks, anchored section validation and unconditional evidence-artifact upload.
- Ran a local synthetic logic harness with 31 assertions covering SHA/label validation, metadata bounds, string/list/content/output-text/legacy response extraction, required section presence, rejection of inline-only section markers, wrong provider/model, non-stop completion, refusal and tool-call cases.
- The first edit of the reader section regex was over-escaped. The fetched source exposed that defect; commit `4fe38c6` corrected it, and the synthetic harness was run against the corrected regex.

### 12.4 Verification boundary

The synthetic harness exercises copied response-extraction and validation logic; it is not execution of the workflow's embedded Python script. Exact-source static assertions are not a YAML parser, GitHub Actions execution, provider invocation, artifact inspection or Blind Fresh Tester result. No workflow was dispatched. Both workflows remain open-PR proposals, and no workflow run is authorized by this audit.

## 13. Live PR #174 pin reconciliation and execution boundary — 2026-11-12

A follow-up check compared the PR #174 source commit recorded in Section 11 with the source commit currently pinned by the documentation-reader workflow and the live PR #174 head.

- Section 11's historical source commit: `16a82663d6a421575234b5f8f4ea0c5ad4f735cf`.
- Current documentation-reader workflow pin: `9502989ffae91c00ba0a8568ab5296925fa9f27b`.
- Live PR #174 head at this reconciliation: `9502989ffae91c00ba0a8568ab5296925fa9f27b`.
- Fetched specification blob at both commits: `a1798ee8a1d48284bd0dc6686ce255eacab8a2b7`.
- Both fetched file contents are byte-for-byte identical (71,091 characters).

**Disposition:** this is a commit-identity/history discrepancy, not a specification-content discrepancy. The current workflow pin is correct for the authorized live-head assessment input. Section 11 is retained as a historical snapshot; this addendum supplies the later reconciliation without rewriting history. PR #173's current workflow pin `7e9481677197cf82df31bbe08984fa5d58644d98` also matches its live PR head at this check.

### Controlled execution feasibility

The live documentation-reader workflow at blob `5b58d8250860f10df64947858bae7b729cb8a501` declares only `workflow_dispatch`. The available GitHub connection exposes repository/workflow reads and workflow-run inspection, but no workflow-dispatch action. The attempted read-only run-history check did not find either assessment workflow in the latest 100 repository runs; this is not evidence of execution or success.

GitHub's manual-dispatch constraint also means the workflow file must exist on the repository's default branch before a `workflow_dispatch` event can be run. PR #195 remains unmerged, and the authorization expressly preserves it as a draft. No merge, temporary default-branch integration, trigger expansion, or other repository-state workaround is authorized by this bounded task.

**Current verification status:** static source inspection and the previously recorded synthetic logic harness remain the available evidence. YAML parsing, execution of the embedded workflow scripts inside GitHub Actions, provider invocation, artifact inspection and a Blind Fresh Tester assessment remain unverified. No runtime pass, reviewer verdict beyond the separately recorded PR #195 review, gate clearance or Director acceptance is claimed.

**Next safe execution route:** obtain an authorized execution environment that can run the exact PR #195 workflow revision without integrating it into the default branch, or obtain a separate explicit Director decision authorizing a narrowly scoped, reversible default-branch test arrangement. Until then, report runtime verification as BLOCKED; do not convert synthetic tests or static inspection into an Actions runtime pass.
