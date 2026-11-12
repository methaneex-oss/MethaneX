# JARVIS Project Governance and Builder Rules

**Status:** Accepted project-wide governance standard by Project Director; merged into `docs/jarvis-phase-2-whole-brain-integration-map-20261105` by PR #196  
**Created:** 2026-11-05  
**Repository:** `methaneex-oss/MethaneX`  
**Companion baseline:** [Phase 1 — Whole-Repository Investigation, Reuse and Conflict Audit](../architecture/reports/PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md)  
**Architecture references:** PR #171–#174, subject to the exact scope, review outcome and authority reconciliation recorded in both Phase 1 artifacts  
**Important:** This document establishes working rules. It does not itself clear Gate A, authorize runtime implementation, merge a PR, or change the accepted architecture.

---

## 1. Purpose and scope

These rules govern all future JARVIS investigation, architecture, implementation, testing, integration, review, documentation and release work. They consolidate the established project principles with controls derived from defects, integration gaps, misleading evidence risks and documentation conflicts discovered during Phase 1.

They apply across the whole JARVIS project, including the Brain, runtime, interfaces, tools, engineering infrastructure, deployment and future system capabilities. The Brain is the first implementation focus; it is not the boundary of the complete JARVIS system.

These rules are intended to prevent:
- loss of prior work or accidental project restarts;
- conflict between phases, documents, branches and implementation;
- disconnected mechanisms that do not form a coherent cognitive system;
- hardcoded situation-specific behavior being mistaken for learning;
- donor code being treated as approved or production-ready without evidence;
- tests and reports overstating what has actually been demonstrated;
- unauthorized changes to runtime code or accepted architecture;
- repeated investigation, avoidable build regressions and undocumented decisions.

## 2. Permanent project principles

### Rule 2.1 — Continue the existing project

JARVIS is an existing long-running project. Work must begin from the verified current repository and project state. Do not create a replacement project, restart a completed phase, discard existing work, or redesign from generic assumptions.

A restart or replacement may only be proposed when evidence demonstrates that continuation is technically unsound. Such a proposal must identify the affected assets, explain why repair or adaptation is inadequate, assess migration cost and risk, and obtain explicit project-owner approval before execution.

### Rule 2.2 — Engineer mechanisms; let behavior be acquired through experience

The governing principle is:

> Engineer the mechanisms; let behavior be acquired through experience.

Build the capacities for perception, representation, memory, reasoning, prediction, appraisal, attention, planning, action, feedback, learning, adaptation and development. Do not pre-program an exhaustive catalogue of situations and their expected responses.

The system should be able to encounter unfamiliar circumstances, form and revise internal representations, use evidence, predict outcomes, act within authorization, observe consequences and improve future behavior.

### Rule 2.3 — JARVIS is not a chatbot or an LLM wrapper

An external model may provide language, perception, reasoning assistance or other bounded capabilities. It must not silently become the sole cognitive authority or substitute for persistent state, memory, learning, planning, action control and system-level integration.

A model response is an input or contribution, not automatically a verified belief, memory, decision or fact.

### Rule 2.4 — Design the whole system; implement in a controlled sequence

Architecture and requirements must account for the complete JARVIS system and its external environment. Implementation may begin with the Brain and proceed in justified stages, but this must not collapse the project scope into “Brain only.”

Every component must have a defined responsibility and system boundary, including how it interacts with other components and with the outside world.

### Rule 2.5 — One coherent cognitive system

Mechanisms may be distributed across components and processes, but they must participate in one coherent cognitive system with explicit ownership, data contracts, event semantics, persistence and failure behavior.

Do not create isolated modules merely to satisfy a checklist. Do not create competing authoritative Brain states in different languages or runtimes.

### Rule 2.6 — Human cognition and MCU J.A.R.V.I.S. are reference lenses

For major capabilities and architectural decisions, analyze both:
- relevant human cognitive functions and limitations, as a source of behavioral and functional comparison;
- MCU J.A.R.V.I.S. as the intended fictional behavioral/functional reference for the system experience.

Use these as comparative lenses, not literal implementation blueprints. Explain where the references agree, differ or are not technically transferable. Do not claim biological equivalence or fictional capabilities that have not been engineered and tested.

### Rule 2.7 — Evidence over claims

A mechanism is not complete because a class, interface, test name, design document or successful compilation exists. Claims must match demonstrated behavior and the scope of the evidence.

Use precise status language: proposed, specified, implemented, compiled, unit-tested, integration-tested, experimentally evaluated, independently reviewed, accepted, merged and deployed are different states.

---

## 3. Phase 1 is the permanent continuity baseline for all future phases

### Rule 3.1 — Mandatory Phase 1 traceability

Every future phase, subphase, task, design, implementation, test plan, review and major decision must explicitly connect to Phase 1.

The Phase 1 report is the initial repository-state and reuse/conflict baseline. It records what was inspected, what existed, what was missing, what was reusable, what was only donor work, known defects, test limitations, documentation conflicts and unresolved gates.

No future work may treat Phase 1 as optional background reading.

### Rule 3.2 — Proportionate Phase 1 traceability

Every future phase plan and final phase report must contain a full section titled **“Phase 1 Continuity and Impact.”** It must identify relevant Phase 1 findings, source paths, commits, mechanisms and decisions; preserved/reused assets; gaps addressed; dependencies; changed or superseded conclusions; carry-forward obligations; and deliberately unchanged scope.

Every substantial task, design, implementation change, test plan and review must identify its relevant inherited findings and parent phase/task traceability. Small subtasks may inherit traceability from a parent task when they introduce no new architectural, state, safety, persistence, integration or implementation risk. If a subtask reveals new evidence, changes a contract, crosses a system boundary or creates a material risk, it must add its own explicit traceability.

Do not repeat the entire Phase 1 investigation for every small task. Traceability must be concrete and auditable, but proportional to the scope and risk. A statement such as “Phase 1 was considered” remains insufficient.

### Rule 3.3 — Phase 1 is a baseline, not an untouchable assumption

Phase 1 must not be silently rewritten to make later work appear consistent. New evidence may prove a Phase 1 conclusion incomplete or incorrect.

When that happens:
- preserve the original report and commit;
- identify the exact finding being challenged;
- provide new source, test, runtime or review evidence;
- explain the discrepancy and its cause;
- create a dated correction/addendum or supersession record;
- update the active decision and traceability register;
- identify downstream phases and artifacts affected.

This preserves history while allowing the project to learn from better evidence.

### Rule 3.4 — No phase isolation

A phase may have a bounded objective, but it may not make decisions as though earlier phases, accepted architecture, existing code or future dependencies do not exist.

Before a phase begins, inspect its dependencies and inherited constraints. Before it closes, record the outputs, decisions, unresolved issues and obligations that the next phase must carry forward.

### Rule 3.5 — Mandatory carry-forward ledger

Maintain a phase continuity ledger containing, at minimum:

| Field | Required content |
|---|---|
| Item ID | Stable identifier |
| Origin | Phase, report, PR, commit, issue or review |
| Finding/decision | Exact issue or accepted decision |
| Current disposition | Open, accepted, corrected, superseded, blocked or rejected |
| Evidence | Source paths, blob/commit IDs, tests and review references |
| Owner/action | What must happen next |
| Dependency | Which mechanisms or future phases are affected |
| Closure evidence | What proves the item is actually closed |

No unresolved high-impact finding may disappear between phases. Carry it forward, explicitly defer it with a reason, or close it with evidence.

### Rule 3.6 — Cross-phase conflict check

Before accepting a new design or implementation, compare it against:
- Phase 1 findings and preservation decisions;
- accepted PR #171–#174 architecture/specification, within their approved scopes;
- all intervening accepted decisions and corrections;
- relevant implementation and donor lineage;
- open defects, gates and review findings.

If a conflict exists, stop the affected change and resolve it explicitly. Do not hide it in implementation details or rely on a later phase to discover it.

---

## 4. Authority and decision hierarchy

When artifacts disagree, apply this order, while respecting each artifact's approved scope:

1. Explicit project-owner decisions and approvals.
2. Verified approved whole-system architecture and Brain architecture/specification artifacts, within exact approved scopes. PR #174 was formally accepted for exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` in Project Director issue comment #6604790481. A subsequent review report supplied in the conversation identifies F-02 and F-03 as unresolved. Preserve the historical acceptance while treating those later findings as open correction obligations; affected requirements are not implementation-ready until resolved and the required authority/review decision is recorded.
3. Approved project governance and gate decisions.
4. Current, verified implementation and its reproducible behavior.
5. Verified tests, experiments and runtime evidence.
6. Reviewed implementation proposals and donor branches.
7. Historical blueprints, older phase documents, draft proposals and informal notes.

This is not permission to ignore contradictory runtime evidence. If code contradicts the accepted specification, record a conformance defect; do not redefine the architecture merely to match existing code.

### Rule 4.1 — Accepted is not merged

An accepted PR or planning baseline is not necessarily merged into `main`. Always report acceptance, merge status and implementation status separately.

### Rule 4.2 — Donor is not authority

PR #97, PR #156 and related donor work may contain valuable implementations. They do not override accepted specifications and must not be treated as production-ready solely because they are larger, newer or pass selected workflows.

### Rule 4.3 — No silent authority promotion

A draft, review comment, builder recommendation, experiment or branch cannot become binding architecture through repetition. Any authority change requires an explicit decision record and the appropriate approval.

---

## 5. Architecture and integration rules

### Rule 5.1 — Trace capabilities through the whole system

For every major capability, identify:
- purpose and system-level responsibility;
- inputs, outputs and state ownership;
- event and data contracts;
- upstream and downstream dependencies;
- persistence, replay and recovery behavior;
- failure and uncertainty behavior;
- safety and authorization boundaries;
- tests and measurable acceptance criteria.

Do not stop at a module diagram or a list of mechanisms.

### Rule 5.2 — Mechanisms must interact meaningfully

A capability is not integrated merely because two modules are called in the same cycle. Demonstrate that the relevant information actually crosses the boundary, influences the receiving mechanism, is persisted where required, and can affect later behavior.

Phase 1 identified a concrete example: retrieved memories were placed in cognitive-cycle context but were not supplied to the inspected reasoning problem. Future integration reviews must inspect actual dataflow, not infer integration from proximity or naming.

### Rule 5.3 — One authoritative cognitive-state owner

Every persistent cognitive state domain must have an explicit owner. Other languages, processes and services must interact through versioned contracts and defined consistency, persistence and failure semantics.

Do not let C++, Rust, TypeScript or an external model maintain conflicting authoritative versions of the same Brain state.

### Rule 5.4 — Language follows architecture

Choose languages based on justified technical requirements. Do not add a language because polyglot architecture sounds advanced. Every language boundary adds build, testing, serialization, deployment, security and operational costs that must be justified.

A declared interface is not a working integration. Verify the actual transport, implementation, compatibility and failure behavior.

### Rule 5.5 — Preserve bounded subsystem responsibilities

The engineering-agent/task-orchestration subsystem is not the JARVIS Brain. Tool providers, interfaces, model adapters, operators and external services must not acquire cognitive authority accidentally.

### Rule 5.6 — No module-count completion

Do not measure progress by number of files, classes, mechanisms, layers or completed tickets. Measure it by integrated capability, correct state transitions, evidence-backed behavior and system-level outcomes.

---

## 6. Learning, hardcoding and generalization rules

### Rule 6.1 — Classify every fixed rule

Every significant fixed rule must be classified as one of:

1. **Safety/infrastructure invariant:** permissions, authorization, risk ceilings, validation, resource bounds, isolation, rollback and integrity constraints. Retain unless a documented safety analysis justifies change.
2. **Initial cognitive prior or policy:** weights, thresholds, decay, similarity functions, feature schemas and heuristics. Treat as provisional, expose to evaluation and justify their scope.
3. **Situation-specific behavior mapping:** a predefined stimulus/context-to-emotion, goal, judgment or response mapping. Do not use this as a substitute for acquired behavior.
4. **Test-environment ground truth:** explicit labels, phases and consequences used to measure a learner. Keep isolated from production behavior and test for leakage.

### Rule 6.2 — No universal reaction tables

Do not encode exhaustive lists of situations and prescribed reactions as the Brain's intelligence. Do not hardwire rules such as “this stimulus always means this emotion,” “failure always means trauma,” or “this keyword always means this intent” as general cognitive truth.

A bounded parser, safety rule or domain-specific adapter may use explicit rules when its limited role is clear. It must not be misrepresented as general understanding.

### Rule 6.3 — Learning must produce persistent, testable change

Learning may arise through more than one evidence pathway. At minimum, distinguish:

**Observational/evidence-based learning:** new observations, verified information, contradiction, discovered relationships or appropriately sourced experience change an internal representation, belief, model, prediction or strategy. Demonstrate that the update is justified by evidence, preserves provenance and uncertainty, persists or reconstructs correctly, and improves or appropriately changes later interpretation or prediction on relevant held-out evidence.

**Action-outcome learning:** an attempted action is followed by an observed and sufficiently verified consequence. Distinguish intention, attempt, execution result and external consequence; assess attribution and uncertainty; then demonstrate a persistent update that changes later prediction, appraisal, strategy or decision and can be revised when subsequent evidence warrants it.

Learning does not require the Brain itself to act first. Nor does merely storing information, incrementing a counter, changing confidence or successfully calling a learning API prove meaningful learning. Evaluation must test the relevant pathway and rule out leakage, unsupported inference and accidental state changes.

### Rule 6.4 — Separate prediction from outcome and evidence

Do not train from an assumed outcome when execution failed or no consequence was observed. Distinguish:
- intended action;
- attempted action;
- execution result;
- verified external consequence;
- evidence source and independence;
- uncertainty about whether the consequence was caused by the action.

### Rule 6.5 — Require held-out generalization

Do not claim generalization when all evaluation examples were present during training or when task labels leak the answer.

Learning evaluations should, where relevant, include:
- held-out contexts and feature combinations;
- changed or reversed environmental relationships;
- independent seeds and repeated runs;
- persistence/restart and replay;
- contradictory evidence and belief revision;
- source and goal isolation;
- failure without observed consequence;
- comparison against fixed-policy and non-learning baselines;
- metrics for prediction quality and decision quality over time.

Report exactly what the experiment demonstrates and what it does not. Synthetic tasks are useful controlled evidence, not proof of open-world intelligence.

### Rule 6.6 — Do not preserve a model merely because it learns

A learned model with a fixed feature schema, additive structure, hand-built token rules or narrow training distribution may be a useful starting point. Its assumptions, interaction limits and failure modes must be documented and tested before broader claims.

---

## 7. Human and MCU reference analysis

### Rule 7.1 — Required comparative analysis

For every major new cognitive capability or substantial change, include:
- the relevant human cognitive function or functions;
- the corresponding MCU J.A.R.V.I.S. behavior or capability;
- the proposed software mechanism;
- what is shared at the functional level;
- what differs and why;
- what cannot reasonably be inferred from either reference;
- how the proposed behavior will be tested.

### Rule 7.2 — Do not imitate surface behavior only

A natural-sounding response, emotional phrase, personality trait or apparent confidence is not evidence of the underlying capability. Evaluate the mechanism and its effect on later behavior, not only the visible output.

### Rule 7.3 — Do not force false biological analogies

Human cognition is a reference for functions, interactions, trade-offs and limitations. It is not a demand to recreate neurons or biological structures literally. Explain engineering analogies precisely.

---

## 8. Implementation controls

### Rule 8.1 — No implementation without the required gate

Architecture approval, phase completion, a builder recommendation or a passing test does not automatically authorize runtime implementation.

Before runtime changes, verify the applicable project-owner approval, implementation gate, selected baseline, target branch and scope. If the gate is not cleared, continue only with authorized investigation, documentation, design or test preparation.

### Rule 8.2 — No wholesale donor merge by convenience

Every donor port must be selective and traceable. For each port, record:
- donor PR, exact commit and source blob/path;
- corresponding accepted requirement;
- existing implementation and replacement/extension decision;
- API and state compatibility;
- event, persistence and replay implications;
- test evidence and known limits;
- hardcoded assumptions;
- rollback or migration plan.

Do not merge PR #97 or PR #156 wholesale to save analysis time.

### Rule 8.3 — Diagnose before patching

For every defect:
1. reproduce or establish the failure from reliable evidence;
2. identify the root cause and affected contracts;
3. inspect adjacent call paths and state transitions;
4. assess regressions and data/persistence consequences;
5. choose the smallest sound correction;
6. add a regression test that would fail before the correction, or an equivalent repeatable verification appropriate to the defect type (for example, a documentation-link/authority consistency check, schema validation, reproducible inventory procedure or independent review);
7. run the relevant targeted and broader checks applicable to the change;
8. report any untested boundary.

Do not demand a software regression test where the defect is documentary or governance-related and a more appropriate repeatable verification exists. Do not apply speculative patches or repeatedly change unrelated files to make a build pass.

### Rule 8.4 — Protect persistent state and failure semantics

Changes to journals, memory, event replay, learning state, evolution adoption, rollback and multi-event transactions require explicit failure-path analysis. Test partial writes, restart, replay, idempotency, compensation and recovery where applicable.

A successful happy path is not sufficient for stateful mechanisms.

### Rule 8.5 — Preserve compatibility deliberately

Before changing public interfaces, serialization, event schemas or cross-language contracts, identify in-repository and external compatibility risks. Do not claim ABI/API compatibility based only on static call-site searches; compile/link and downstream checks remain necessary where applicable.

### Rule 8.6 — No unrelated scope expansion

A phase or task must not quietly introduce new architecture, languages, dependencies, modules or product scope. Record the reason and impact, then obtain the appropriate approval.

---

## 9. Testing and evidence standards

### Rule 9.1 — Test the requirement, not the implementation's assumptions

Tests must verify intended capability and invariants, not merely reproduce the code's current logic. Include adversarial, boundary, negative, recovery and regression cases where relevant.

### Rule 9.2 — Distinguish test levels

Report separately:
- static inspection;
- unit tests;
- component tests;
- integration tests;
- end-to-end tests;
- deterministic synthetic experiments;
- held-out generalization experiments;
- long-running or longitudinal evaluation;
- production/real-world evidence.

Do not describe one level as another.

### Rule 9.3 — Exact commit and run identity

Every CI claim must identify the exact commit tested, workflow, run, result and relevant logs. A passing earlier commit does not validate a later head. A branch run does not automatically validate a PR head.

### Rule 9.4 — Tests must be discoverable and executed

A test file existing in the repository does not mean it runs. Verify build-system registration, CI invocation and actual test output. Record skipped, disabled, unregistered and flaky tests.

### Rule 9.5 — Measure behavioral improvement

For learning and prediction, report meaningful metrics over time, including baselines, held-out performance, calibration or uncertainty where relevant, regressions and failure cases. Passing mechanism gates is not equivalent to improved capability.

### Rule 9.6 — No fabricated evidence

Never invent test runs, commits, file paths, review identities, CI status, merged state or approvals. If a result could not be retrieved or independently checked, say so.

---

## 10. Documentation and repository hygiene

### Rule 10.1 — Maintain one discoverable authority map

The repository must make clear which documents are:
- whole-system architecture;
- Brain architecture and mechanism specification;
- current phase plan and report;
- implementation decision records;
- test/evaluation protocols and results;
- governance and approval records;
- historical or superseded material.

Do not allow multiple documents to silently claim authority over the same scope.

### Rule 10.2 — Preserve history; do not delete to create cleanliness

Do not delete legacy blueprints, phase reports, donor evidence or old plans merely because they are superseded. Mark them historical, add a supersession notice and link to the current authority. Delete only after dependency/value review and explicit authorization.

### Rule 10.3 — Every important decision is recorded

Record the decision, date, authority, alternatives considered, evidence, consequences, affected artifacts and follow-up obligations. Chat discussion alone is not a durable repository decision.

### Rule 10.4 — Keep status language precise

Use labels such as **draft**, **proposed**, **under investigation**, **implemented**, **verified**, **accepted**, **merged**, **deprecated** and **superseded** consistently. Never use “complete” without naming the scope and acceptance evidence.

### Rule 10.5 — Link phase reports to source evidence

Reports should cite exact repository paths, commit IDs, PRs, test names and workflow runs. Prefer immutable commit/blob references for claims that could change over time.

---

## 11. Builder operating rules

These rules govern the work performed by the Builder (the assistant acting as the project's active engineering worker).

### Rule 11.1 — Act as the worker, not as a narrator of another worker

The Builder must not refer to “the Builder” as though it were a separate person or imply that another worker performed actions it did not perform. State clearly what was inspected, changed, tested, committed or not completed.

### Rule 11.2 — Inspect before asserting

Before making repository claims, inspect the relevant current branch, commit, file or PR. Do not rely solely on remembered summaries when the live artifact can be checked. When access is unavailable, identify the limitation rather than guessing.

### Rule 11.3 — Work in substantial, coherent batches

Prefer completing a coherent investigation or deliverable over sending repetitive status messages. Break work into bounded milestones when useful, but do not sacrifice verification to appear fast.

### Rule 11.4 — No false progress or completion

Do not claim to be working in the background, running periodic checks, monitoring a task or sending future notifications unless an actual supported automation has been created and confirmed.

“Done” means the requested scope is actually complete and verified. If only part is complete, report the completed part and remaining work precisely.

### Rule 11.5 — Explain blockers early and concretely

A blocker report must state:
- what is blocked;
- the exact evidence or error;
- what has already been attempted;
- why the attempted path failed;
- the smallest viable next action;
- whether owner input or approval is required.

Do not hide recurring errors behind repeated retries.

### Rule 11.6 — Optimize for correctness and user time

Avoid unnecessary long-running tool calls, repeated broad searches and large log dumps when a bounded query or manual step is faster. If a manual action is materially more efficient, say so. Do not confuse tool activity or response length with engineering progress.

### Rule 11.7 — Keep handoffs complete

At the end of a phase or when handing work to another session/worker, provide the current branch and commit, completed deliverables, exact evidence, open findings, gate status, next actions and constraints. The next worker must be able to continue without restarting discovery.

### Rule 11.8 — Independent review must be genuinely independent

The author/implementer must not present their own self-check as an independent review. Independent review requires a separate reviewer, a defined scope and standard, evidence against the exact commit, recorded findings and a submitted review where the process requires one.


### Rule 11.9 — Mandatory pre-change inspection and scope lock

Before every repository modification, the Builder must verify and record:
- the repository and target branch;
- the live branch HEAD and its relationship to the intended base;
- the exact target file(s) and their current blob identities;
- the relevant PR scope, existing changes and unresolved dependencies;
- the applicable governing rules, accepted architecture and current phase/gate restrictions.

The Builder must not modify a stale snapshot, assume a remembered SHA is current, overwrite concurrent work, or broaden the change beyond the authorized task. If the target moved or the expected file identity changed, refresh and reconcile before writing. If the correct target or authority cannot be established, do not write.

### Rule 11.10 — Preserve architectural intent and authority

Every material change must be traceable to the current authorized requirement and accepted architectural intent. The Builder must not silently redesign, simplify, narrow, expand, replace or reinterpret the architecture to make implementation or documentation easier.

Before changing a contract, phase boundary, mechanism responsibility, state owner, learning assumption or integration dependency, identify the governing source and assess downstream effects. When evidence conflicts with an accepted decision, stop the affected change, document the conflict and seek the required authority. Never treat a Builder proposal or convenient implementation as an approved decision.

### Rule 11.11 — Diagnose and correct causes, not symptoms

For every defect or regression, the Builder must establish the failure mechanism before selecting a fix. The diagnosis must distinguish the observed symptom, triggering conditions, causal mechanism, affected boundary and evidence supporting the conclusion.

Prefer the smallest correction that addresses the demonstrated root cause without weakening requirements, hiding failures, bypassing validation or introducing unrelated changes. After correction, check the original failure path and plausible adjacent regression paths. If the cause cannot be established, label the diagnosis provisional and do not present the patch as a verified root-cause fix.

### Rule 11.12 — Exact-revision verification is mandatory

A successful write or commit response is not proof that a task is complete. After every coherent repository change, the Builder must:
- fetch the resulting live branch/PR HEAD;
- fetch the changed files at that exact revision;
- verify the intended content and confirm that unrelated paths were not changed;
- run the relevant available validation against that exact revision, or state precisely why a check could not be run;
- record commit SHA, relevant blob identities, test/workflow run identifiers and outcomes where applicable.

If the branch advances during verification, repeat the affected checks against the new HEAD. Never transfer a test result from an older commit to a newer one. Never claim a check passed when it was not executed or its result was not observed.

### Rule 11.13 — Completion claims require evidence

The Builder may use “complete,” “fixed,” “verified,” “passed” or equivalent language only when the stated acceptance criteria have been checked and the evidence is available for the exact claimed scope and revision.

Every closeout must separate:
- completed and verified Builder work;
- completed work whose verification is unavailable;
- partially completed work;
- blocked work and its concrete cause;
- work reserved for an independent reviewer, fresh tester or Project Director.

A successful commit, green unrelated CI job, prepared report, self-review or previous-revision result must not be represented as proof of a different requirement. If evidence is incomplete, the status must remain open or qualified.

### Rule 11.14 — Maintain and revalidate project continuity

The Builder must maintain a concise, current handoff record containing the repository, branch, exact HEAD and base, task scope, changed paths, completed work and evidence, open defects, dependencies, gate status, reserved decisions and next Builder-owned actions.

At the start of a resumed session, the Builder must retrieve the live repository state and reconcile it against the handoff before acting. A handoff is a navigation aid, not authority to assume that branches, commits, PR states or decisions remain unchanged. Preserve completed work, avoid repeating settled investigations, and explicitly record when new evidence supersedes an earlier conclusion.

### Rule 11.15 — The Builder owns Builder-executable work

When acting as the main Builder, the assistant must execute the repository investigation, documentation, implementation, correction and verification tasks that are within the authorized scope and available tool permissions. It must not shift those tasks to the user, describe work as though another Builder performed it, or substitute instructions for work it can actually perform.

Ask the Project Director only for decisions or approvals reserved to that authority, and identify independent-review or fresh-testing work as external when it genuinely requires a separate person or process. Tool limitations must be stated specifically; they must not be used as a pretext to avoid feasible bounded work.

### Rule 11.16 — No unauthorized recovery actions

A defect or delay does not authorize the Builder to restart a phase, replace a baseline, merge or close a PR, rebase or retarget a branch, cherry-pick work, alter accepted architecture, waive a gate, dispatch a reserved assessment, or begin implementation outside the current authorization.

Use the least disruptive recovery path that preserves existing work and authority boundaries. Where recovery requires a reserved decision, stop only the affected action, present the evidence and options, and continue with other authorized Builder-owned work.

---

## 12. Phase lifecycle and mandatory gates

Every phase must use the following lifecycle, adapted only with a recorded reason.

### 12.1 Before phase start — entry gate

A phase may start when:
- its objective and boundaries are explicit;
- Phase 1 Continuity and Impact has been prepared;
- upstream deliverables and decisions are identified;
- relevant source, branch and commit baselines are pinned;
- dependencies, risks and approval requirements are known;
- acceptance criteria and evidence requirements are defined;
- the phase does not conflict with an uncleared gate.

### 12.2 During the phase — change control

For every material change:
- record the originating requirement or finding;
- assess impact on earlier decisions and later phases;
- update the traceability/carry-forward ledger;
- preserve source and test evidence;
- escalate scope or authority changes for approval.

### 12.3 Before phase completion — exit gate

A phase is complete only when:
- all required deliverables exist in the repository or agreed location;
- every deliverable has Phase 1 and prior-phase traceability;
- acceptance criteria are evaluated against evidence;
- tests and exact commits/runs are recorded;
- defects and unverified claims are disclosed;
- unresolved items have owners and explicit carry-forward status;
- documentation and authority links are updated;
- required review and owner approval are recorded.

A phase report must clearly separate **completed**, **partially completed**, **not completed**, **blocked**, and **deferred** items.

### 12.4 No automatic gate inheritance

Passing one phase does not automatically pass the next phase's gate. A phase can complete its documentation or investigation deliverable while a separate implementation, safety or independent-review gate remains uncleared.

---

## 13. Mandatory structure for future phase documents

Each future phase plan/report must include:

1. Objective and scope.
2. Entry criteria and inherited approvals.
3. **Phase 1 Continuity and Impact.**
4. Prior-phase dependencies and carry-forward items.
5. Whole-system impact and human/MCU reference analysis where applicable.
6. Existing source and artifact reuse assessment.
7. Proposed changes and explicit non-goals.
8. State ownership, dataflow and integration effects.
9. Hardcoding and learning assessment.
10. Risks, safety and failure/recovery analysis.
11. Test and evaluation plan.
12. Exact evidence and results.
13. Decisions and deviations.
14. Open issues and next-phase obligations.
15. Exit-gate result and approval status.

Do not omit a section silently. Mark it not applicable with a reason.

---

## 14. Phase 1-specific inherited constraints

Until new evidence formally changes them, future work must carry forward these Phase 1 conclusions:

1. The project is not to be restarted; substantial implementation and donor work exist.
2. PR #171 Documents 00 and 01 have scope-limited approvals recorded in the Phase 1 inventory; PR #172 and PR #173 are recorded as accepted planning inputs/baselines, subject to exact revision and approval verification.
3. PR #174 was formally accepted by the Project Director for exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` in issue comment #6604790481. A later review report supplied in the conversation identifies F-02 and F-03 as unresolved. This does not retroactively erase the acceptance event. It creates targeted specification-correction obligations; PR #174 remains the accepted planning baseline, but affected requirements must not be treated as implementation-ready until those findings are resolved and the required authority/review decision is recorded. The later report is not currently represented as a submitted GitHub PR review. BM-01–BM-12 mapping may proceed as analysis; implementation depending on unresolved F-02/F-03 requirements remains gated.
4. Main-branch C++ implementation is a substantial starting point, not a specification-complete Brain.
5. PR #97 and PR #148–#156 are selective donors, not a wholesale approved baseline.
6. PR #176 contains D1/D2 corrections and test evidence, but its open/unmerged status and relationship to PR #156 must be checked at the time of future work.
7. Gate A was **NOT CLEARED** in the Phase 1 report. Re-check live status before relying on any later closure claim.
8. Deeper controller-internal compensation failure injection and genuine independent re-review were outstanding in the Phase 1 snapshot.
9. The main reasoning engine did not satisfy the full BM-12 general-reasoning scope.
10. Retrieved memories were not passed into the inspected reasoning call; verify and address this integration gap.
11. Main goal selection did not demonstrate autonomous goal formation.
12. Main decision, threat, attention and learning policies contained fixed assumptions requiring classification and evaluation.
13. The main event journal and structured recall were valuable foundations, not proof of final semantic memory or tamper-proof storage.
14. The inspected main cognitive cycle did not own the complete action → observed consequence → persistent learning loop.
15. Rust must not become a competing Brain state authority; TypeScript interfaces must not be mistaken for a functioning integrated runtime.
16. Engineering-agent orchestration remains separate from JARVIS cognitive authority.
17. Legacy blueprint and old subsystem-phase documents must be marked historical/superseded, not silently treated as current architecture.
18. Phase 1 did not select an implementation baseline or authorize runtime implementation.

These are baseline findings, not claims that the repository cannot have changed since the audit. Verify current branch/commit status before acting on time-sensitive items.

---

## 15. Rule changes and governance amendments

These rules may evolve as JARVIS develops, but amendments must not happen silently.

Every proposed amendment must include:
- rule identifier and current wording;
- proposed wording;
- reason and evidence;
- affected phases, architecture documents, code and tests;
- compatibility/conflict analysis;
- approval authority;
- effective date and version.

If a rule is obsolete, mark it superseded and explain why. Preserve the prior version and decision history. Emergency safety corrections may be applied immediately when necessary, but must be documented and reviewed promptly.


### Amendment 2026-11-11 — Enforceable Builder operating controls

- **Rules added:** 11.9–11.16.
- **Prior wording:** Rules 11.1–11.8 established general Builder conduct but did not explicitly require a pre-change state/scope lock, exact-revision post-write verification, root-cause evidence, a revalidated continuity record, or a clear boundary between Builder-executable work and reserved authority.
- **Amended wording:** Rules 11.9–11.16 above establish those mandatory controls and prohibit unauthorized recovery actions.
- **Reason and evidence:** Repeated stale-state assumptions, incomplete verification, symptom-level corrections, continuity failures and premature completion claims caused avoidable rework and loss of confidence in Builder reports. The Project Director explicitly directed that these commitments be added to this existing governance document on 2026-11-11.
- **Affected scope:** All Builder work across investigation, planning, documentation, implementation, testing, integration and release. These rules do not change JARVIS architecture, phase scope, acceptance criteria or gate authority.
- **Compatibility/conflict analysis:** Additive to Rules 11.1–11.8; reinforces Rules 2.7, 3, 4, 8–10 and 12. Does not authorize runtime implementation, PR integration, independent review or fresh testing.
- **Approval authority:** Explicit Project Director instruction dated 2026-11-11 to add these controls. This records approval of this amendment only, not blanket approval of every other proposed governance provision.
- **Effective date:** 2026-11-11, for Builder work on this project, subject to repository commit and normal project governance.
- **Version:** Governance amendment 2026-11-11 / Builder operating controls v1.

---

## 16. Current execution status

**Historical snapshot notice:** This section records the status at the document's creation. Current operating requirements are defined in Sections 17–22 and the dated amendment records; do not treat this creation-time snapshot as a replacement for those current requirements.

At the time of this section's creation, this document was a proposed governance baseline awaiting project-owner review. That historical status was superseded by the Project Director acceptance recorded in the dated acceptance record below. It does not retroactively certify that all earlier work complied with these rules.

At creation:
- Phase 1 technical inventory/reuse/conflict investigation: complete within the declared static scope; historical branch/document preservation follow-up remains open.
- Architecture/specification authority: PR #171–#174 have recorded approval/acceptance events within their scopes; PR #174's historical acceptance is confirmed, while later F-02/F-03 review findings remain open correction obligations.
- Phase 1 Gate A: not cleared in the Phase 1 report.
- Phase 2: integration investigation is the recommended next phase; do not treat this governance document as authorization for runtime implementation.
- Repository merge status and all PR heads: must be rechecked live before future gate decisions.

**Governing principle:** Every future phase inherits the evidence, decisions, constraints and unresolved obligations of Phase 1 and every intervening phase. Nothing is silently discarded, contradicted or restarted. New evidence may change the project, but it must do so transparently, traceably and with the required approval.


---

## 17. Project roles and accountability

The following role model applies across all project phases and deliverables. It clarifies responsibility and decision authority; it does not change the existing JARVIS vision, architecture, accepted requirements or phase/gate restrictions.

### Rule 17.1 — Project Director owns direction and acceptance

The Project Director is responsible for project direction, priorities, boundaries, milestone authorization and final acceptance.

The Director must:
1. Establish measurable milestones before implementation.
2. Define completion criteria and the evidence required to evaluate them.
3. Protect the established project vision, architecture and approved decisions.
4. Prevent uncontrolled scope expansion and prioritize finishing existing commitments.
5. Delegate implementation decisions within clearly defined authority.
6. Evaluate evidence rather than repeatedly requesting assurances.
7. Make timely decisions when the available evidence is sufficient.
8. Avoid unnecessary intervention in ordinary engineering decisions that have been delegated.

The Director must not routinely supervise implementation details, confuse activity with measurable progress, accept unsupported completion claims, introduce unrelated work before current commitments are completed, or demand repeated reviews after sufficient verification without a new evidence-based reason.

The Director retains authority over direction, scope, reserved decisions and acceptance. The Director does not need to approve every ordinary engineering choice made within an authorized scope.

### Rule 17.2 — Builder owns complete implementation and self-verification

The Builder owns the complete implementation responsibility for the authorized milestone.

Before implementation, the Builder must read the authoritative project documentation, understand the current architecture and prior decisions, identify dependencies and constraints, confirm scope and acceptance criteria, and assess material risks.

During implementation, the Builder must complete the assigned scope, preserve architectural consistency, avoid unnecessary redesign, investigate root causes, avoid superficial patches, document significant decisions and keep changes aligned with project objectives.

Before handoff, the Builder must inspect all relevant changes, complete self-review, run relevant available tests, correct discovered defects, check integration points, disclose unresolved issues and prepare a complete evidence-backed handoff.

The Builder must not transfer unfinished self-review or obvious defects to the Independent Reviewer or Tester. Existing Rules 11.1–11.16 remain in force and provide additional enforceable Builder controls.

### Rule 17.3 — Independent Reviewer owns independent technical scrutiny

The Independent Reviewer must be a genuinely separate person or independently operated agent who did not author or implement the submitted work and did not perform the Builder's self-review. The Reviewer must receive the exact stable handoff and governing materials and conduct a fresh assessment. The Builder must not act as, simulate, or submit a purported Independent Reviewer verdict for its own work. If no genuinely separate Reviewer is available, the review status is PENDING or BLOCKED; Builder self-review cannot be relabelled as independent review.

The review must examine, as applicable:
1. Requirement completeness.
2. Architectural compliance.
3. Implementation correctness.
4. Integration with existing mechanisms and state owners.
5. Unnecessary complexity.
6. Missing functionality.
7. Error handling and failure conditions.
8. Maintainability and regression risks.
9. Deviations from established project decisions.

Every finding must state its severity, exact location or affected component, explanation, supporting evidence, and required correction or justified recommendation.

The review verdict must be exactly one of:
- **APPROVED**
- **APPROVED WITH DOCUMENTED NON-BLOCKING ISSUES**
- **REJECTED — CORRECTIONS REQUIRED**

The reviewer must not approve work merely because the Builder claims completion. The reviewer must not silently redesign the project or introduce new requirements. Findings must remain within the authorized scope; genuinely new proposals must be classified and handled through change control.

### Rule 17.4 — Independent Tester owns behavioural verification

The Independent Tester must be a genuinely separate person or independently operated agent who did not author or implement the submitted work and did not act as its Independent Reviewer. The Tester must verify actual behaviour independently against the authorized requirements and test plan, using a fresh test assessment. The Builder must not act as, simulate, or submit a purported Independent Tester verdict for its own work. If no genuinely separate Tester is available, testing is PENDING or BLOCKED; Builder tests cannot be relabelled as independent testing. Testing must target a stable implementation revision that has completed Builder self-verification and the required review/correction cycle.

Applicable coverage includes:
- unit tests;
- integration tests;
- end-to-end behaviour;
- regression tests;
- boundary conditions and invalid inputs;
- failure handling;
- persistence, replay and state transitions;
- relevant performance and reliability requirements.

**Documentation-only applicability:** When a Director-authorized milestone consists solely of documentation or governance changes and has no executable behaviour in scope, its acceptance criteria may explicitly mark Independent Testing as **NOT APPLICABLE (N/A)**. The test plan and lifecycle record must state the reason and the scope basis for that determination; the Builder may not unilaterally waive the stage. If project-specific requirements still require a Tester verdict or executable test evidence, the Tester must record **BLOCKED** with the reason rather than inventing behavioural tests or treating N/A as PASS. This does not waive Independent Review, applicable document/format validation, or Project Director acceptance.

The Tester must verify the actual implementation, use reproducible procedures, record actual outcomes, preserve failure evidence, distinguish untested behaviour from passing behaviour, rerun failed tests after corrections and identify coverage gaps.

The test verdict must be exactly one of:
- **PASS**
- **PASS WITH DOCUMENTED NON-BLOCKING LIMITATIONS**
- **FAIL**
- **BLOCKED**

A blocked test is not a passing test. A test that was not executed, could not reach its target, or lacks an observable result must not be reported as passed. The Tester must not silently change acceptance criteria to make a result pass.

### Rule 17.5 — Role separation and accountability

Each role is accountable for its own responsibilities:
- Project Director: direction, priorities, scope boundaries, reserved decisions and final acceptance.
- Builder: complete implementation, self-review, self-testing, correction and evidence-backed handoff.
- Independent Reviewer: unbiased technical scrutiny and verification of review corrections.
- Independent Tester: independent behavioural verification and retesting after implementation corrections.

One role's work does not substitute for another role's required evidence. In particular, Builder self-review does not substitute for independent review, and successful compilation or isolated unit tests do not substitute for independent behavioural testing.

---

## 18. Mandatory milestone workflow and handoff control

### Rule 18.1 — Use the required sequence

Unless a documented project-specific constraint requires a justified variation, each milestone must follow this sequence:

1. The Project Director authorizes a bounded milestone and its acceptance criteria.
2. The Builder implements the authorized scope and completes self-verification.
3. The Builder submits a complete handoff with exact revision and evidence.
4. The Independent Reviewer examines the complete, stable scope.
5. The Builder resolves review findings.
6. The Independent Reviewer confirms the corrections or records why a finding remains unresolved.
7. The Independent Tester executes the approved test plan against the reviewed, stable revision.
8. The Builder corrects implementation defects found during testing.
9. The Independent Tester verifies the corrections and reruns affected tests.
10. The Project Director evaluates the final evidence and records acceptance or rejection.

### Rule 18.2 — Do not review or test unstable work

Do not begin the milestone's independent review while the Builder is still making unrelated implementation changes to the submitted scope. Do not begin final testing against an unstable implementation or before the required review/correction stage is complete.

If a material change is necessary after handoff, the Builder must identify the changed revision and affected scope. The review and test evidence must be refreshed wherever the change could invalidate it. Never carry approval or passing status forward automatically to a materially different revision.

### Rule 18.3 — Preserve an auditable lifecycle record

Maintain a clear record of the authorized scope, implementation revision, Builder self-review and test results, handoff, review verdict and findings, corrections, reviewer confirmation, test procedures and outcomes, retests, limitations and Director acceptance.

The record must identify the exact commit or artifact revision to which each result applies. A status summary without traceable evidence is insufficient.

---

## 19. Milestone scope and change control

### Rule 19.1 — Define and protect milestone scope

Every milestone must have an explicit objective, included work, exclusions, dependencies, owner, acceptance criteria and required evidence before implementation begins. Work outside that boundary is not automatically authorized because it is discovered during implementation.

### Rule 19.2 — Classify new discoveries

Every material discovery or proposed addition must be classified as one of:
- **Required to complete current scope** — necessary to satisfy an existing acceptance criterion.
- **Critical defect** — a defect that makes the current deliverable unsafe, invalid or materially incorrect.
- **Architectural dependency** — a prerequisite or contract issue that blocks correct completion.
- **Future improvement** — useful but not necessary to meet the current milestone.
- **Unrelated suggestion** — outside the current objective and its dependencies.

Only work necessary to complete the authorized scope or correct a blocking defect/dependency should enter the current milestone. Future improvements and unrelated suggestions must be recorded for later prioritization rather than silently added to current commitments.

### Rule 19.3 — Require approval for material scope changes

A material change to scope, acceptance criteria, architecture, dependencies, schedule commitment or authority boundary must include its justification, evidence, impact assessment, affected deliverables and required approval. The Builder may make ordinary implementation decisions within the authorized scope but may not unilaterally change reserved Project Director decisions.

### Rule 19.4 — Preserve existing commitments

Do not introduce additional work before existing milestone commitments are completed unless a critical defect, safety concern or blocking dependency makes reprioritization necessary. Record the reason and the effect on the current milestone. Do not equate starting more tasks with making more progress.

---

## 20. Completion, acceptance and evidence

### Rule 20.1 — Completion requires the full applicable evidence chain

A milestone deliverable is complete only when:
- the agreed scope is implemented;
- Builder self-review is complete;
- relevant Builder self-tests have been executed and their results recorded;
- Independent Review has reached an acceptable verdict;
- required review corrections have been verified by the reviewer;
- Independent Testing has reached an acceptable verdict, or has been explicitly recorded as **NOT APPLICABLE (N/A)** under Rule 17.4 with its Director-authorized scope rationale documented;
- required implementation corrections have been retested by the Tester, where applicable;
- remaining limitations and untested areas are documented;
- evidence is available for the exact claimed revision;
- Project Director acceptance is recorded.

The acceptance criteria may define a justified subset of test types for a particular deliverable, but omitted test categories must be identified with a reason. For documentation-only deliverables, Independent Testing may be recorded as NOT APPLICABLE only under Rule 17.4; in that case no behavioural Tester retest is implied, while required document corrections and applicable document validation remain subject to their stated verification criteria. This does not waive Independent Review or Director acceptance. No role may silently waive a required gate.

### Rule 20.2 — Activity and partial evidence are not completion

A successful build alone is insufficient. A passing isolated test suite alone is insufficient. A large implementation, extensive documentation, a successful commit or a completed Builder checklist alone is insufficient.

Completion claims must state the deliverable and revision, the criteria evaluated, the review and test verdicts, the evidence references, the limitations and the Director's acceptance status. If any required stage is pending, blocked or failed, report the milestone as open, blocked or not accepted as appropriate.

### Rule 20.3 — Preserve limitations and negative evidence

Record failed tests, blocked tests, missing coverage, unresolved review findings, known limitations and deviations. Do not omit negative evidence from a handoff or summarize a mixed result as an unconditional pass.

---

## 21. Continuous improvement and governing operating principle

### Rule 21.1 — Improve the process from recurring evidence

Recurring failures must trigger investigation of their root causes and proportionate process improvements. Where evidence justifies it, improve engineering practices, automated checks, templates, review criteria and authoritative documentation so that previously resolved defects are less likely to recur.

Do not create a new rule for every isolated incident. First determine whether the incident exposes a recurring systemic weakness, an existing rule that was not followed, or an exceptional event. Improvements must be proportionate to the demonstrated cause and must not create needless process overhead.

### Rule 21.2 — Do not make the project dependent on constant Director intervention

The project must not depend on the Project Director constantly supervising routine engineering to maintain quality. Builders own implementation; reviewers own independent technical scrutiny; testers own independent behavioural verification; the Director owns direction, boundaries and final acceptance.

The objective is not merely to build more. It is to build the right things, finish them, verify them and make measurable progress without repeatedly losing ground.

---

### Amendment 2026-11-12 — Project directorship and team operating standard

- **Sections added:** 17–21, covering Project Director, Builder, Independent Reviewer and Independent Tester accountability; mandatory workflow and handoff; scope and change control; completion and evidence; continuous improvement.
- **Prior wording:** Existing Rules 1–16 established project principles, authority boundaries, phase gates and detailed Builder controls, but did not consolidate the complete role-accountability model and milestone workflow supplied by the Project Director.
- **Amended wording:** Sections 17–21 add the supplied Parts A–I as enforceable project operating requirements, with role separation, explicit verdicts, ordered handoffs, scope classification and evidence-gated completion.
- **Reason and evidence:** Explicit Project Director instruction on 2026-11-12 to incorporate the complete "PROJECT GOVERNANCE REFORM — DIRECTORSHIP AND TEAM OPERATING STANDARD" into the existing governance document as an additive amendment.
- **Affected scope:** All project directors, builders, independent reviewers, testers and supporting agents across project investigation, planning, documentation, implementation, testing, integration and release.
- **Compatibility/conflict analysis:** Additive to Rules 1–16. Existing Builder Rules 11.1–11.16 remain in force. Existing architecture, phase scope, accepted requirements, gate decisions and implementation authorization boundaries are unchanged. The workflow does not authorize runtime implementation, PR integration, gate clearance, branch-history operations or waiver of any reserved decision.
- **Approval authority:** Project Director instruction dated 2026-11-12 authorizes this additive repository amendment. This records authorization to prepare the amendment; it does not claim final acceptance or merge approval for PR #196.
- **Effective date:** 2026-11-12 for work governed by this amendment, subject to repository commit and the project's normal governance/acceptance process.
- **Version:** Governance amendment 2026-11-12 / Directorship and Team Operating Standard v1.

---

## 22. Mandatory governance revalidation on every work run

### Rule 22.1 — Revisit the governing standard at the start of every run

Every project participant must freshly revisit the applicable governance standard at the beginning of **every work run or execution invocation**, without exception for task size, duration, perceived simplicity or risk. This includes every assistant/agent execution that performs project work, every new or continued task run, each resumed task after an interruption, every Builder implementation or revision run, every Independent Review run, every Independent Testing run, and every supporting-agent run. A continuing objective does not create an exemption for later executions.

This is a required operating step, not optional background reading and not a documentation-only requirement. Participants must read the current authoritative source itself; relying only on memory, a previous summary, a prior chat, a copied checklist or another participant's assurance does not satisfy this rule.

At minimum, the participant must freshly revisit:
- the Project Governance and Builder Rules document, including the permanent project principles and the applicable role/workflow rules;
- the current Director-authorized milestone scope and acceptance criteria;
- the authoritative architecture, decisions, constraints and gate status relevant to the work;
- any newer governance amendment or explicit Project Director instruction that applies.

The revalidation must be proportionate in recording detail, but never omitted. A small task may use a concise record; it does not receive an exemption.

### Rule 22.2 — Each role performs its own revalidation

The requirement applies independently to the Project Director, Builder, Independent Reviewer, Independent Tester and every supporting agent.

- **Builder:** reread before investigation or modification, then apply the rules throughout implementation, self-review, self-testing and handoff.
- **Independent Reviewer:** reread independently before review; verify the current scope, authority, role-separation requirements and review criteria without relying on the Builder's attestation or conclusions.
- **Independent Tester:** reread independently before test planning or execution; verify the current scope, test criteria, review/correction status and exact target revision without relying on the Builder's or Reviewer's assurance in place of evidence.
- **Project Director and supporting agents:** reread the applicable standard before directing, authorizing or performing their part of the work.

A prior participant's completed revalidation does not satisfy another participant's obligation.

### Rule 22.3 — Record a run-specific revalidation

Every run must create or update a concise **Governance Revalidation Record** in its work log, task record or handoff, containing:
1. Project and work item/run identifier.
2. Exact governing document path/title and revision identifier (commit, version or date).
3. Confirmation that the source was freshly read during this run.
4. Applicable role and the rules that materially govern the work.
5. Current authorized scope, exclusions and acceptance criteria.
6. Relevant architecture, gate constraints and unresolved obligations checked.
7. Conflicts, ambiguities or changes found, with their disposition or escalation.
8. Participant identity/role and the exact artifact revision to which the record applies.

For very small tasks, fields may be compressed into a short entry, but source revision, fresh-read confirmation, role, scope and any conflict must remain identifiable. Never fabricate a revision, reading event or attestation.

### Rule 22.4 — Stop when the governing source cannot be verified

If the current governing source, applicable scope, authority or material gate status cannot be located or verified, the participant must not proceed with affected substantive or state-changing work on remembered assumptions. Record the limitation and mark the work BLOCKED or request the missing authority/source. Safe, non-mutating discovery to locate the authoritative material may continue.

If a new governance instruction or amendment appears during a run, pause affected work, reread it, assess its impact on current work and evidence, and record the result before proceeding.

### Rule 22.5 — Governance compliance is an acceptance and review criterion

Builder handoffs must include the Builder's run-specific Governance Revalidation Record. Independent Review must check that record and independently perform its own fresh revalidation. Independent Testing must do the same before testing. Missing, stale, copied without rereading, unverifiable or role-inappropriate records are findings. The Reviewer must issue **REJECTED — CORRECTIONS REQUIRED** when governance noncompliance prevents approval; if the review cannot be conducted because required sources or evidence are unavailable, record the review stage as PENDING/BLOCKED without issuing an approval verdict. The Tester must issue **FAIL** for demonstrated noncompliance or **BLOCKED** when required testing cannot be performed.

The Reviewer and Tester must explicitly assess whether the work complied with the governance principles throughout the run, not merely whether a checklist was filled in. A ceremonial attestation does not prove compliance. Evidence must show how scope, role boundaries, change control, root-cause correction, review/test separation and completion criteria were applied where relevant.

### Rule 22.6 — Preserve role independence while enforcing revalidation

Governance revalidation does not collapse the roles. The Builder cannot satisfy the Reviewer's or Tester's fresh-read obligation for them, and cannot create their verdicts. Reviewer and Tester must independently inspect the exact submitted revision and relevant evidence. If distinct qualified actors are unavailable, the independent stage remains PENDING or BLOCKED and the milestone cannot be represented as fully reviewed, tested or complete.

### Rule 22.7 — Apply the operating standard across projects

The run-by-run revalidation and role-accountability requirements are a cross-project operating standard for projects undertaken by this team, not merely a JARVIS documentation convention. For another project, participants must freshly read that project's current authoritative governance and architecture documents as well as apply this operating standard. Project-specific stricter rules and authority hierarchies remain in force; this standard does not silently override them or authorize changes to another project's repository. Where no project-specific governance exists, the Project Director must establish the applicable scope and authority before substantive implementation.

---

### Amendment 2026-11-12 — Run-by-run governance enforcement

- **Sections added:** Section 22 establishes mandatory fresh governance revalidation at the start of every work run for every role, including Builder, Independent Reviewer, Independent Tester, Project Director and supporting agents.
- **Corrections to prior amendment:** Sections 17.3 and 17.4 now explicitly require genuinely separate Reviewer and Tester actors. The Builder may not simulate or relabel its own work as independent review or testing; unavailable independent roles remain PENDING/BLOCKED.
- **Enforcement:** Every run must carry a revision-specific Governance Revalidation Record. Reviewer and Tester must independently reread the governing source and independently verify compliance. Missing or unverifiable revalidation is a review/testing finding and may block the stage.
- **Cross-project application:** The run-by-run operating requirement applies across projects undertaken by this team, subject to each project's own stricter governance and authority hierarchy. This JARVIS repository amendment does not itself modify other project repositories.
- **Compatibility and authority:** Additive to existing Rules 1–21. It does not clear gates, authorize runtime implementation, approve a merge, or alter accepted architecture.
- **Approval authority:** Project Director instruction dated 2026-11-12.
- **Effective operating instruction at amendment time:** Apply immediately in this collaboration. At that time, repository governance remained proposed pending the normal review and acceptance process; the later Project Director acceptance is recorded separately below.
- **Version:** Governance amendment 2026-11-12 / Run-by-Run Governance Revalidation v1.


### Builder correction record — Independent Review findings F-196-01 and F-196-02

- **Source review:** Independent Reviewer report `docs/architecture/reports/INDEPENDENT_GOVERNANCE_REVIEW_GROK_PR196_2026-11-12.md`, verdict **APPROVED WITH DOCUMENTED NON-BLOCKING ISSUES**, submitted against HEAD `1a8d3b691c71af0e8a2fc8091370109c4a548584`.
- **F-196-01 correction:** Added a historical-snapshot notice to §16 directing readers to current operating requirements in §§17–22 and the dated amendment records. Historical status content was not rewritten.
- **F-196-02 correction:** Added a controlled NOT APPLICABLE (N/A) path for Independent Testing on Director-authorized documentation/governance-only milestones with no executable behaviour in scope. The rationale must be in the acceptance criteria, test plan and lifecycle record; the Builder cannot waive the stage unilaterally. Where a Tester verdict or executable evidence remains required, the Tester records BLOCKED with reason. Independent Review, applicable document validation and Director acceptance remain mandatory.
- **Scope and compatibility:** Additive clarification only. No runtime, architecture, phase-gate, branch-target or merge authorization changes. Independent Review and Director acceptance remain separate mandatory gates.
- **Verification status:** Builder correction and exact-revision checks are to be recorded in the PR handoff after the resulting commit is verified. The Independent Reviewer must independently confirm both corrections against the new exact revision.


---

### Project Director acceptance record — 2026-11-12

- **Decision authority:** Project Director.
- **Decision:** ACCEPTED — the Project Director has reviewed and accepted this governance standard, including Rules 11.1–11.16 and Sections 17–22, as the operating standard for the governed project work.
- **Accepted governance content:** The governance document at blob `bb8a20d560f753d27da32259a72112bc18a5be3b`, present at PR #196 HEAD `46b220c7d7b066fc98d48eaa5680d9e021a3d899` immediately before this acceptance-record-only update.
- **Scope of this record:** Records Director acceptance and authorizes this acceptance-status clarification, independent verification of the resulting exact revision, and—only after acceptable independent verification—merging PR #196 into its existing base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`.
- **No expanded authority:** This acceptance does not clear Gate A or any other phase gate; authorize runtime implementation, training runs, architecture changes, deployment, or changes to accepted technical decisions; retarget the PR; or authorize merging into `main`.
- **Historical status reconciliation:** Earlier statements that this document was Proposed accurately describe its status before this Director decision. They are retained as historical records and do not override this acceptance record.
- **Repository state (historical wording):** At the time this acceptance record was written, PR integration remained pending. PR #196 was subsequently independently verified and merged into the existing base branch; see the dated post-merge reconciliation record below.

---

### Builder Governance Revalidation Record — Director acceptance-status update

1. **Project / work item:** MethaneX PR #196 — record Project Director acceptance and reconcile current document status.
2. **Governing source:** `docs/governance/JARVIS_PROJECT_GOVERNANCE_AND_BUILDER_RULES.md`, freshly retrieved and read at pre-change HEAD `46b220c7d7b066fc98d48eaa5680d9e021a3d899`, blob `bb8a20d560f753d27da32259a72112bc18a5be3b`.
3. **Fresh-read confirmation:** Yes, during this work run.
4. **Role / applicable rules:** Builder executing Director-authorized documentation update; Rules 11.9–11.16, 17.1–17.5, 18, 19, 20, 22.1–22.5.
5. **Authorized scope:** Change current status wording, reconcile creation-time Proposed language as historical, add the Director acceptance record, and prepare the exact revision for independent verification. No other governance substance or project scope changes.
6. **Constraints checked:** PR #196 current target branch, current governance content, review findings and correction verification, and existing JARVIS phase/gate boundaries. No gate clearance or runtime authorization.
7. **Conflicts / disposition:** The header and an unqualified sentence in §16 still stated Proposed despite Director acceptance; resolved by updating current status and explicitly marking §16 wording historical. The earlier Section 22 amendment-time status is clarified as historical. No conflict with the approved governance substance identified.
8. **Participant / revision:** Builder; this record applies to the acceptance-status update commit to be produced from pre-change HEAD `46b220c7d7b066fc98d48eaa5680d9e021a3d899`.


---

### Post-merge status reconciliation — 2026-11-12

- **Work item:** JARVIS-M0 / Workstream A — reconcile governance status after PR #196 integration.
- **Governance revalidation:** Builder freshly reread this complete governance document at blob `9c17d2870047cc1d58afea745cd7160d15e216c3` on the current documentation branch before this update.
- **Verified merge:** PR #196, `docs(governance): enforce Builder operating controls`, merged on 2026-11-12 into its existing base branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`.
- **Merge commit:** `c151e52781e56e6481424f774c19ea30128debb0`.
- **Verification:** Governance document blob at the merge commit was `9c17d2870047cc1d58afea745cd7160d15e216c3`; the accepted governance content and Project Director acceptance record were present.
- **Correction:** The header now reports the verified merged state. The acceptance record's former "repository merge pending" sentence is explicitly identified as a historical statement accurate when written, not current status.
- **Scope:** Status/documentation reconciliation only. This does not clear any planning gate, accept PR #173/#174, authorize Stage A, runtime implementation, training, baseline selection, PR integration beyond PR #196, or deployment.
- **Builder role:** Builder; JARVIS-M0 Workstream A.
- **Current revision:** This record applies to the commit created by this post-merge status reconciliation. Independent review/validation and Project Director acceptance remain separate where required by JARVIS-M0.
