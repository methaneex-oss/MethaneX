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
- selected documentation on the existing PR #192 branch `docs/whole-brain-planning-scope-correction-20261107`: the planning index, outstanding-work register, initial documentation-foundation audit, fresh-reader assessment report, and whole-Brain planning scope correction.

This was a bounded terminology audit, not a claim that every historical branch, PR description, issue, artifact, or repository object was exhaustively searched.

## 3. Findings

### 3.1 Generic interface comment used a product name

At the audit baseline, `interfaces/typescript/src/operator_session.ts` described a generic supervised operator session as “ChatGPT-facing”. The interface itself is not a product-specific ChatGPT integration. The product reference was therefore unnecessary and made the abstraction appear coupled to a consumer product.

**Disposition:** corrected to “assistant-facing”. No interface behavior, type, runtime boundary, or authorization semantics changed.

### 3.2 Workflow display labels used a model/vendor name as a project role

The two active blind-assessment workflows exposed the model/vendor name in job and step labels and, in the documentation-reader workflow, in the assessment artifact filename/prefix. This conflated the role being performed with the implementation/provider used to execute it.

**Disposition:** changed the visible role labels to **Blind Fresh Tester** and renamed the human-facing assessment output/artifact labels accordingly.

### 3.3 Historical planning records contain model/product attribution

The selected PR #192 planning and evidence documents contain numerous historical references to external model identities, provider attribution, prior review submissions, and conversation provenance. Some of those details explain why a review did or did not qualify, which exact model endpoint was reported by an API, or what evidence was available at a historical decision point.

**Disposition:** not bulk-rewritten in this pass. Historical evidence must not be silently altered in a way that falsifies attribution, obscures the limits of an earlier assessment, or changes the meaning of a prior Project Director decision. The new role standard governs current and future project-facing labels. Where a historical model/provider identifier is necessary to reproduce or qualify an event, it belongs in provenance metadata, not as the participant's project role.

### 3.4 No current default-branch Grok role string was returned by the bounded code search

The default-branch search returned no matching code result for the requested reviewer-brand term. The selected PR #192 documents did contain historical reviewer attribution. This audit does not claim that the historical review itself was re-performed, qualified, or upgraded by a terminology change.

## 4. Changes made on this branch

| Path | Change |
|---|---|
| `.github/workflows/documentation-foundation-ai-reader.yml` | Job/step labels and assessment artifact naming now use **Blind Fresh Tester** |
| `.github/workflows/brain-foundation-blind-architecture-review.yml` | Job/step labels, assessment persona, and output filename now use **Blind Fresh Tester** |
| `interfaces/typescript/src/operator_session.ts` | Generic “ChatGPT-facing” comment changed to “assistant-facing” |
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
- alter historical reviewer findings, decision records, or evidence artifacts;
- modify PR #173, PR #192, or PR #193 source branches;
- merge a pull request, clear a gate, start implementation, or authorize runtime work.

## 7. Verification required before integration

Before this branch is integrated, verify the diff and workflow syntax, then confirm that:

1. All visible workflow job/step labels use **Blind Fresh Tester**.
2. The two workflow prompts accurately describe the Blind Fresh Tester task and do not claim Project Director authority.
3. Technical provider/model routing and provenance checks remain intact.
4. The generic operator-session comment no longer implies a product-specific integration.
5. No runtime behavior or authorization boundary changed.

A successful terminology edit is not evidence that either assessment workflow has executed successfully. No workflow run is claimed by this audit.
