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
