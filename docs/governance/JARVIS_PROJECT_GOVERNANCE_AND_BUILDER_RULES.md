# JARVIS Project Governance and Builder Rules

**Status:** Proposed project-wide governance baseline, published for explicit owner review  
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

This document is a proposed governance baseline for project-owner review. It does not retroactively certify that all earlier work complied with these rules.

At creation:
- Phase 1 technical inventory/reuse/conflict investigation: complete within the declared static scope; historical branch/document preservation follow-up remains open.
- Architecture/specification authority: PR #171–#174 have recorded approval/acceptance events within their scopes; PR #174's historical acceptance is confirmed, while later F-02/F-03 review findings remain open correction obligations.
- Phase 1 Gate A: not cleared in the Phase 1 report.
- Phase 2: integration investigation is the recommended next phase; do not treat this governance document as authorization for runtime implementation.
- Repository merge status and all PR heads: must be rechecked live before future gate decisions.

**Governing principle:** Every future phase inherits the evidence, decisions, constraints and unresolved obligations of Phase 1 and every intervening phase. Nothing is silently discarded, contradicted or restarted. New evidence may change the project, but it must do so transparently, traceably and with the required approval.
