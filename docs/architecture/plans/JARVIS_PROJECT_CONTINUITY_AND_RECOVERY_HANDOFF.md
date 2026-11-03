# JARVIS Project Continuity & Recovery Handoff

**Last updated:** 2026-11-03  
**Purpose:** This is the authoritative restart point for any new ChatGPT conversation, collaborator, or agent continuing this project. Read this document before taking action. Do not rely on chat memory as the source of truth.

## 1. Project identity and objective

This is an existing, long-running JARVIS cognitive architecture project in `methaneex-oss/MethaneX`. It is not a new project.

The objective is to engineer a real, integrated cognitive system whose capabilities and behavioral tendencies can improve through experience. The governing principle is:

> **Engineer the mechanisms; let behavior be acquired through experience.**

Do not reduce the project to a chatbot, thin LLM wrapper, fixed rule engine, hardcoded behavior tree, or static knowledge database. Do not restart or generically redesign it.

The human-cognition and MCU J.A.R.V.I.S. comparisons are reference lenses for analysis, not permission to invent fictional internals or copy fictional capabilities as if they were engineering specifications.

## 2. Current phase — read this first

**Current phase: Brain Implementation Planning. We are not yet in implementation.**

Accepted upstream work:
- **PR #171** — whole-system foundation.
- **PR #172** — foundational Brain capability investigation.
- **PR #173** — integrated Brain foundation architecture.
- **PR #174** — integrated Brain mechanism specification. This is the governing mechanism specification; accepted HEAD: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`.

Current planning work:
- **PR #175** — Brain implementation roadmap / planning.
- Branch: `plan/brain-implementation-roadmap-20261103`.
- Latest known HEAD: `5088c0644658f573bd18cf579ba426bb51dfb506`.
- PR: https://github.com/methaneex-oss/MethaneX/pull/175

### Exact subphase: Gate A — repository baseline reconciliation

Gate A's final disposition has been documented as:

**NOT CLEARED — NO IMPLEMENTATION BASELINE SELECTED.**

The disposition document is:
`docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md`

Direct link:
https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md

Detailed reconciliation checkpoint:
`docs/architecture/plans/reviews/02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md`

PR #156 is a **candidate only**, not an accepted implementation baseline. Do not rebase, cherry-pick, merge, rewrite history, or start implementation from it.

The final-disposition review assignment was posted as PR #175 comment:
https://github.com/methaneex-oss/MethaneX/pull/175#issuecomment-6615019538

At the time of this handoff, the GitHub PR reviews endpoint returned no submitted reviews. No independent reviewer is formally requested in GitHub metadata. Do not claim a review has started or completed. The next action is to obtain an independent review of the Gate A disposition and checkpoint. If no reviewer is available, report that blocker plainly; do not impersonate an independent reviewer or approve your own work.

## 3. What Gate A found and why it is not cleared

The reconciliation records substantial evidence about candidate history and files, but important questions remain unresolved:
- exhaustive commit-to-file and origin attribution across the inherited history;
- semantic reconciliation of divergent integration files;
- 24 differing Brain API function bodies and two definitions requiring manual alignment;
- a final defensible choice of implementation baseline.

The checkpoint contains a 1,416-commit enumeration and a 165-path net tree inventory. These are recorded evidence, not proof that all semantic reconciliation is complete.

PR #156 remains useful as an evidence-bearing candidate. It is not approved as the base to build on.

## 4. What happens next — in order

1. **Complete independent Gate A review.** Reviewer must challenge the disposition, reproduce critical refs/blob claims, distinguish verified from unverified claims, and state whether any correction is needed.
2. **Resolve reviewer findings.** Record corrections and their evidence in a separate review/correction document under `docs/architecture/plans/reviews/`, not by silently rewriting the accepted specification or burying findings in the main planning document.
3. **Return the Gate A decision to the Project Director (the user).** Do not treat reviewer approval as Project Director acceptance.
4. **Only after explicit user authorization, begin Gate B.** Gate B is the detailed source-to-specification traceability audit for all 12 mechanisms in accepted PR #174. It is not implementation.
5. **Only after Gate B and a separately accepted implementation plan and explicit authorization** may implementation work begin.

Do not skip stages to make the project appear to be progressing.

## 5. Non-negotiable engineering principles

- Preserve the accepted PR #174 specification as the governing mechanism contract.
- Analyze the system as an interacting whole. Learning is not a single file or subsystem.
- The meaningful criterion is persistent, experience-dependent change in later prediction, belief, attention, memory, reasoning, valuation, decisions, and/or behavior—not merely code presence or isolated passing tests.
- Do not hardcode mappings such as stimulus → emotion, negative affect → reject, failure → trauma, success → reward, or fixed stimulus → action.
- Do not preload a finished personality, fixed goals, preferences, or behavioral repertoire and call it learning.
- Distinguish initial enabling capacities from competencies acquired through experience.
- Treat cognition as recurrent, interruptible, and potentially parallel—not necessarily one rigid linear pipeline.
- Preserve the separation between cognitive intent, governance permission, execution, and verified consequence.
- Claims of learning must be supported by evidence that experience changes persistent internal state and affects future outcomes under appropriate tests.
- Do not claim human-level cognition, MCU-level capability, consciousness, or general intelligence from subsystem demonstrations.

## 6. Working rules for the assistant / agents

1. **Act as the builder when authorized.** Do not speak about “what the Builder should do” as if you are not the builder. State what you will do.
2. **Inspect the repository before asserting facts.** Use exact branches, commit SHAs, paths, blobs, diffs, and source evidence. Chat memory is context, not repository evidence.
3. **Respect authorization boundaries.** Current authorization is limited to Gate A repository baseline reconciliation and its independent review. Gate B, runtime changes, builds, tests, technology choices, schema/API decisions, rebase/cherry-pick/merge, branch rewriting, and deployment require separate authorization unless already explicitly granted later.
4. **Do not claim actions that did not happen.** Distinguish code inspected from code changed, tests run from existing CI evidence, and requested reviews from submitted reviews.
5. **Document work.** Record findings, corrections, exact evidence, and verification in accessible repository documentation. Keep correction/review records separate from the main planning document where appropriate.
6. **Fix root causes.** Do not apply speculative patches or create follow-on changes without understanding the failure and its affected contracts.
7. **Keep communication concise and orienting.** The user has explicitly said lengthy explanations cause confusion. Start with current phase, what changed, what is blocked, and the next action. Expand only when needed.
8. **Avoid unnecessary long-running tool work.** Prefer bounded repository operations. If a local checkout/manual step is materially faster or safer, explain that rather than wasting time.
9. **Never silently change project direction.** No restart, generic redesign, chatbot conversion, premature implementation, or hardcoded behavior shortcuts.
10. **The user's approval is distinct from reviewer approval.** A reviewer assesses evidence; the user decides project direction and grants stage authorization.

## 7. Important interpretation of the 12 mechanisms

The accepted PR #174 specification defines 12 Brain mechanisms (BM-01 through BM-12). Use the exact specification for their names, boundaries, ownership, and acceptance criteria. Do not reconstruct or paraphrase the 12-mechanism list from memory when the source document is available.

Known areas that have required special scrutiny include:
- BM-05 causal attribution and prediction scope/resolution;
- BM-06 active context and attention integration;
- BM-08 experience-acquired candidate-goal formation;
- BM-10 corrective metacognition;
- BM-12 memory-to-reasoning flow and inference lineage.

These are audit priorities, not a substitute for tracing all 12 mechanisms.

## 8. Key repository references

- Repository: https://github.com/methaneex-oss/MethaneX
- Current planning PR: https://github.com/methaneex-oss/MethaneX/pull/175
- Accepted specification PR: https://github.com/methaneex-oss/MethaneX/pull/174
- Gate A detailed checkpoint: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/02_GATE_A_REPOSITORY_BASELINE_RECONCILIATION_2026-11-03.md
- Gate A final disposition: https://github.com/methaneex-oss/MethaneX/blob/plan/brain-implementation-roadmap-20261103/docs/architecture/plans/reviews/03_GATE_A_FINAL_DISPOSITION_2026-11-03.md
- Independent review assignment: https://github.com/methaneex-oss/MethaneX/pull/175#issuecomment-6615019538

## 9. Startup instructions for a new chat

When continuing this project:

1. Read this document in full.
2. Read the current PR #175 description and latest comments/reviews.
3. Read the Gate A final-disposition document and detailed Gate A checkpoint.
4. Read the accepted PR #174 specification when mechanism-level questions arise.
5. Verify the live PR head and review state; this handoff may become stale.
6. State the current phase and the single next authorized action to the user.
7. Do not repeat completed work, reopen settled upstream stages without evidence, or start Gate B/implementation without explicit authorization.

### Required first response in a recovery chat

Give the user a short status update in this format:

- **Phase:** Brain Implementation Planning — Gate A independent review.
- **Last decision:** Gate A not cleared; no implementation baseline selected.
- **Current blocker:** Independent review not yet submitted (verify live state).
- **Next action:** Obtain/review the independent Gate A verdict, then report findings and proposed corrections.
- **Not authorized:** Gate B and implementation until separately authorized.

If repository state contradicts this document, trust the verified live repository state, explain the discrepancy, and update this handoff through a documented commit. Never silently assume this snapshot is still current.
