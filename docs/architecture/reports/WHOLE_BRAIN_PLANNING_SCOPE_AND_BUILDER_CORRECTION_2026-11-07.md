# Whole-Brain Planning Scope and Builder Correction — 2026-11-07

**Status:** Documentation correction proposal; awaiting independent review and Project Director acceptance  
**Repository:** `methaneex-oss/MethaneX`  
**Prepared by:** ChatGPT (GPT-6), acting as the JARVIS Builder under user-delegated bounded documentation-work authority granted 2026-11-07  
**Authorization boundary:** Correct existing planning/continuity documentation only. No runtime implementation, tests, builds, baseline selection, donor adoption, merge, rebase, deployment or gate clearance is authorized.  
**Governing principle:** **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

---

## 1. Why this correction exists

The user's instruction is that the project must plan the **entire future Brain before deciding where development should begin or what existing code should be used**.

The correct sequence is:

1. Define the complete intended Brain and its capabilities.
2. Develop and challenge the whole-Brain mechanism architecture and interactions.
3. Assess architectural completeness and reconcile existing specifications.
4. Only then plan development order and the first development increment.
5. Only then inspect the repository for what to reuse, adapt, extend, replace or build.
6. Obtain the required approvals and explicit implementation authorization before implementation.

The current Phase 1 and early Phase 2 artifacts contain valuable work, but they did not complete this sequence. Their titles and use of the phrase "whole Brain" must not be mistaken for proof that the entire future Brain was architecturally defined.

This is a **scope correction and continuity handoff**, not a restart of the repository investigation and not a new implementation architecture.

## 2. The actual planning objective

The immediate objective is to establish a sufficiently complete architectural account of the whole Brain that JARVIS is intended to develop into.

The Brain is not defined by the current number of mechanisms, current source files, a previously proposed layer sequence, or a list of features selected for implementation convenience.

The architecture must discover and explain:

- the major cognitive capacities the future Brain must support;
- the underlying responsibilities and mechanisms that may enable those capacities;
- the information, state, memory, belief, knowledge, goal and internal-state ownership involved;
- how mechanisms exchange evidence and influence one another;
- recurrent, selective, delayed, interruptible, concurrent and developmental interactions;
- how learning can change persistent internal capability and later behavior through experience;
- which capacities are foundational enabling capacities and which competencies should be acquired or refined through experience;
- what capabilities emerge from interactions among mechanisms;
- how uncertainty, contradiction, failure, recovery and self-correction affect cognition;
- the Brain's boundary with the rest of JARVIS, including sensory acquisition, signalling/coordination, action/execution, regulation, security, embodiment, interfaces and external infrastructure;
- unresolved scientific, functional and engineering questions.

This list is a set of questions to investigate, **not a final exhaustive capability checklist**. The next Builder must conduct its own analysis, find omissions, challenge assumptions and justify the architecture. It must not simply turn this list into another fixed mechanism count.

## 3. Three required reference lenses

### 3.1 Human brain and human cognition

Use human cognition and neuroscience to investigate relevant functions, interactions, developmental processes, strengths, limitations and trade-offs. Consider perception, representation, attention, working context, memory, learning, reasoning, prediction, valuation/affect, motivation, goal formation, planning, decision, language, spatial understanding, social cognition, skill acquisition, metacognition and other relevant capabilities.

This is not a claim that the list above is complete. Research must identify additional functions and relationships where relevant.

Do not copy biological anatomy literally into software, assume that a debated neuroscience theory is settled, or claim biological equivalence. Distinguish established evidence, contested theories, engineering abstractions and project hypotheses.

### 3.2 MCU J.A.R.V.I.S.

Use MCU J.A.R.V.I.S. as a fictional functional aspiration for the kind of integrated assistant JARVIS should ultimately become: context-aware assistance, situation understanding, technical analysis, diagnostics, communication, coordination, complex task support and authorized interaction with external systems, among other capabilities supported by the actual fictional reference.

Do not invent fictional internals, treat cinematic behavior as scientific evidence, or assume every depicted capability belongs inside the Brain. Translate observable functions into requirements and identify the surrounding JARVIS systems they depend on.

### 3.3 The developing-Brain analogy

The Brain begins with engineered enabling mechanisms and the capacity to develop. It is not delivered as a finished intelligence with a preloaded mature personality, fixed preferences, exhaustive knowledge, universal reaction tables or a completed behavioral repertoire.

Experience, evidence, interaction, feedback and appropriate training should support the development of representations, knowledge, skills, strategies, calibrated internal responses and increasingly capable behavior.

The analogy does not mean that a human infant is a literal engineering specification. It means the architecture must distinguish **capacity to develop** from **competence already acquired**.

## 4. Status and correct interpretation of prior planning

### 4.1 Phase 1 — repository investigation

The Phase 1 report, `PHASE_1_WHOLE_REPOSITORY_INVESTIGATION_AND_REUSE_AUDIT_2026-11-04.md`, is a repository inventory, static source investigation and reuse/conflict assessment at its pinned baseline.

Its findings remain valuable evidence about existing mainline code, donor branches, tests, documentation, implementation gaps and preservation obligations. Its declared technical investigation may remain complete within that bounded scope.

However, Phase 1 did **not** define the complete future Brain's capability space, prove that the accepted mechanism specification was exhaustive, or decide the final whole-Brain architecture.

Therefore:
- preserve the audit and its exact source baseline;
- do not repeat its completed repository archaeology without a specific evidence gap;
- do not treat its reuse recommendations as development decisions;
- do not use its BM-01–BM-12 coverage as proof of whole-Brain completeness.

### 4.2 Phase 2 — BM-01 through BM-12 source integration mapping

The Phase 2 report maps the twelve logical mechanisms in PR #174 to current-main and donor source, state ownership, dataflow, consumers, persistence/replay and evidence.

That is useful source-integration evidence. Its own report correctly says the unit of analysis is the integrated Brain, rather than twelve independent modules. Nevertheless, its capability universe and acceptance ledger are organized around BM-01–BM-12. It therefore cannot, by itself, prove that the full intended Brain has been defined.

The human/MCU comparison in PR #191 likewise compares BM-01–BM-12. It is a useful comparison of those specified mechanisms, not a complete survey of every capability the future Brain may need.

Preserve the existing maps and findings. Reclassify their authority accurately:
- they are a **partial mechanism-to-source integration investigation**;
- they are not the complete whole-Brain capability architecture;
- their existing technical findings remain valid unless new evidence corrects them;
- their BM-01–BM-12 completion checkboxes do not satisfy the new whole-Brain architectural completeness requirement.

### 4.3 Existing twelve-mechanism specification

PR #174's BM-01–BM-12 specification is important existing planning work at the exact historically cited revision. Do not discard it, silently rewrite its history, or assume that twelve is the final number of Brain mechanisms.

**Authority qualification:** Earlier handoff material described this exact revision as accepted. However, the Phase 1 inventory records a subsequent independent re-review identifying F-02 (contextual language/operator-intent grounding) and F-03 (downstream reasoning integration) as unresolved, while PR #175's description calls PR #174 accepted. Those records conflict. Until the exact reviewer report, current PR discussion, and Project Director decision are reconciled, do not represent PR #174 as unconditionally accepted or final. The documentation index flags this conflict for the next Builder and independent reviewer.

Treat BM-01–BM-12 as an existing mechanism decomposition to be assessed against the whole-Brain architecture. The later architecture reconciliation must determine whether each mechanism remains correctly bounded, needs clarification, needs to be divided or combined, or leaves responsibilities uncovered. Any change to specification authority must follow the required independent review and Project Director decision.

### 4.4 Earlier blueprint and implementation roadmap

- `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` is an earlier Layer 0–19 construction proposal. Preserve it as historical planning evidence. Its linear layer order and "next implementation target" are not the current whole-Brain architecture or an authorized development sequence.
- `docs/architecture/plans/00_BRAIN_IMPLEMENTATION_PLAN.md` in PR #175 is a proposed implementation roadmap built from the then-current mechanism specification and source audit. It is premature as the active next-step plan until whole-Brain architecture planning and completeness review are completed.
- The old `docs/JARVIS_PHASE_2_COMPLETION.md` describes a bounded Perception & Representation work package. It must not be confused with the current whole-Brain Phase 2 investigation.

Do not delete these documents or erase their original decisions. Mark their current applicability precisely and carry them forward as historical/proposed inputs.

## 5. Corrected planning stages and exit evidence

### Stage A — whole-Brain capability and responsibility definition

Identify the future Brain's required functional capabilities from the three reference lenses and project purpose. For each capability, record its purpose, observable meaning, dependencies, expected inputs/outputs at a conceptual level, foundational prerequisites, developmental/acquired aspects, boundaries and evidence needed to demonstrate it.

Do not select code, languages, libraries, algorithms, model providers, databases, schemas, APIs, deployment topology or implementation order in this stage.

**Exit evidence:** a traceable whole-Brain capability register with source/reference rationale, explicit unknowns, overlap/contradiction analysis and a documented completeness challenge.

### Stage B — whole-Brain mechanism architecture and interaction model

Derive the necessary mechanisms from the capability analysis rather than forcing capabilities into the existing twelve. Define responsibilities, authoritative state, conceptual contracts, producer/consumer relationships, recurrent and delayed paths, concurrency, interruption, recovery, learning influence and emergent behavior.

Determine what belongs inside the Brain and what belongs to surrounding JARVIS systems. A surrounding system may be essential to a complete JARVIS capability without becoming a Brain mechanism.

**Exit evidence:** an architecture and interaction model that explains how the required capabilities can arise from cooperating mechanisms, identifies ownership and boundaries, and records unresolved design questions without prematurely selecting implementation technology.

### Stage C — whole-Brain completeness and architecture reconciliation

Challenge the architecture against:
- the human cognition reference and its limitations;
- the MCU functional aspiration without treating fiction as evidence;
- the developing-Brain analogy;
- the full JARVIS system boundary;
- the existing PR #171–#174 architecture/specification and relevant research;
- the Phase 1 and Phase 2 source findings.

Identify omissions, duplicated responsibilities, unclear ownership, missing interactions, unsupported assumptions and capability claims that have no mechanism path. Reconcile BM-01–BM-12 with the resulting architecture through an explicit, reviewed mapping.

**Exit evidence:** documented gap dispositions, updated architecture traceability, independent review and Project Director acceptance of the whole-Brain planning baseline.

### Stage D — development planning

Only after Stages A–C are accepted, decide where development should begin.

Assess dependency criticality, foundational value, risk, integration leverage, measurable learning evidence, reversibility and the cost of delaying other capabilities. Define candidate development increments and their acceptance evidence.

### Stage E — repository capability and reuse assessment for the chosen development increments

Only after the architecture and development priorities are established, inspect the exact current repository state for each selected increment. Decide whether existing work is reusable, adaptable, incomplete, incompatible, replaceable or missing. Record exact source, tests, donor lineage, compatibility and failure/recovery implications.

A code component being present or previously classified "reusable" does not automatically select it for development. Reuse is a decision made against the accepted whole-Brain architecture and the chosen increment.

### Stage F — implementation planning and authorization

Define concrete implementation work packages, dependencies, tests, integration boundaries and rollback plans. Obtain the applicable gate decisions, independent review and explicit Project Director implementation authorization.

No implementation begins merely because the architecture is accepted or a plan exists.

## 6. Non-negotiable constraints for the next Builder

1. Do not restart the project or discard Phase 1/Phase 2 evidence.
2. Do not treat BM-01–BM-12 as an exhaustive or immutable list.
3. Do not add arbitrary mechanisms simply to make the list longer. Derive responsibilities from capability and interaction requirements.
4. Do not turn the human-brain comparison into literal biological imitation.
5. Do not turn MCU J.A.R.V.I.S. into invented technical requirements.
6. Do not treat the developing-Brain analogy as permission to hardcode a finished personality or behavior.
7. Do not choose implementation order, source reuse, language, algorithm, provider, database, API or runtime topology before the appropriate planning stage.
8. Do not confuse the Brain with the complete JARVIS system; explicitly define the boundary and contracts with other SYS domains.
9. Do not confuse repository investigation with architecture definition, architecture definition with development planning, or development planning with implementation authorization.
10. Preserve exact historical acceptance, review, PR and gate status. Re-fetch live repository evidence before making current-state claims.
11. Keep independent review separate from Builder self-check and Project Director acceptance.
12. Make every material decision traceable and preserve unresolved questions rather than silently filling them with assumptions.

## 7. Explicit Builder error record

This correction is authored by ChatGPT (GPT-6), the assistant that performed the earlier planning/review work. The following are my mistakes and must remain visible to the next Builder:

1. **I let BM-01–BM-12 become the effective boundary of whole-Brain planning.** I treated the existing twelve-mechanism decomposition as the main completeness frame instead of first asking whether it represented every capability the future Brain must support.
2. **I conflated two different tasks:** defining the whole Brain's capabilities and mapping an existing mechanism specification to repository source. The Phase 2 source map is valuable, but it cannot substitute for the first task.
3. **I over-relied on the phrase "whole Brain" in the Phase 2 report.** Its actual acceptance criteria and ledgers were predominantly bounded by BM-01–BM-12. I should have checked whether the scope itself was complete, not merely whether the map was internally thorough.
4. **I failed to carry the user's three reference lenses through the planning boundary.** Human cognition, MCU J.A.R.V.I.S. and the developing-Brain analogy should have informed the whole capability architecture from the beginning, not been applied mainly as a comparison of the twelve existing mechanisms.
5. **I proposed moving toward implementation planning/source selection too early.** The correct next task is whole-Brain architecture definition and completeness review. Development ordering and repository reuse decisions come later.
6. **I gave an insufficiently precise account of prior progress.** Phase 1's repository investigation can be complete within its declared static scope while the whole-Brain architecture remains incomplete. Phase 2 can contain extensive useful source mapping while still not establish whole-Brain completeness. I should not have implied that the earlier work was fully aligned with the user's intended planning sequence.

These are scope and sequencing failures in my planning judgment. They do not establish that the prior source investigation or mechanism specifications are technically worthless. Preserve the useful work and correct its scope/authority.

## 8. Verified repository snapshot used for this correction

The following live PR metadata was fetched while preparing this correction on 2026-11-07. Recheck before future decisions:

| PR | Recorded role | State at inspection |
|---|---|---|
| #171 | Whole-system architecture foundation | Open, draft, unmerged |
| #174 | Brain mechanism specification; historically accepted at exact HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` | Open, draft, unmerged |
| #175 | Brain implementation roadmap | Open, draft, unmerged |
| #178 | Phase 1 inventory/preservation and governance package | Open, draft, unmerged |
| #179 | Phase 2 BM-to-source integration map | Open, draft, unmerged |
| #180 | Competing Phase 2 report proposal | Closed, unmerged |
| #191 | Human/MCU comparison for BM-01–BM-12 | Open, draft, unmerged |

Relevant inspected heads:
- PR #171: `b05434758ad4fe72815503f89bd5d2990ccb658b`
- PR #174: `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`
- PR #175: `874c732973b6ab303d65a503f5a215b0af8e1153`
- PR #178: `39fe09dcf13496f5f0005ccf3f00739303e29f88`
- PR #179: `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`
- PR #180: `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`
- PR #191: `609d38ede50bbdd98a93dfed112781eacabee9fd`

The Phase 2 report's latest inspected exit ledger still records unresolved/partial items and does not establish Phase 2 completion. Gate A was recorded NOT CLEARED; Gate B was not passed/accepted. This correction does not change those gate decisions.

## 9. Required first actions for the next Builder — documentation foundation first

1. Read the [Initial Documentation Foundation Audit and Completion Gate](INITIAL_DOCUMENTATION_FOUNDATION_AUDIT_AND_COMPLETION_GATE_2026-11-07.md) in full.
2. Reconcile the exact authority and provenance of the existing whole-system, capability, Brain architecture, and mechanism-specification inputs. Do not infer acceptance from later documents when the exact decision record is missing.
3. Keep the proposed governance rules explicitly proposed unless an exact acceptance record is found.
4. Reconcile the canonical index, detailed inventory, README, continuity handoff, and implementation-plan hold. They must agree on the current phase.
5. Validate cross-branch links against exact commits; document the PR #191 stale base and the separate PR #192/#193 lineages.
6. Preserve the Phase 1 and Phase 2 evidence and all historical artifacts. Do not restart completed technical work or delete/move historical files.
7. Perform the fresh-reader continuity test, then complete the Builder self-review.
8. Obtain a genuinely independent review and the required authority decision on the exact revised documentation baseline.

**Do not begin Stage A until the Initial Documentation Foundation Completion Gate is independently reviewed and accepted.** Stage A remains the first whole-Brain planning stage after that gate; it is not the current task.

## 10. Initial Documentation Foundation Completion Gate — 2026-11-07

The user has clarified that the initial documentation foundation must be made clear before whole-Brain planning begins. Documentation will continue to evolve during planning and engineering; this gate establishes the initial reliable baseline rather than claiming that documentation can ever become permanently complete.

The gate covers:

- one canonical navigation index and one synchronized detailed inventory;
- exact document/commit/blob provenance and authority classification;
- explicit PR base/head/dependency relationships;
- durable commit-pinned cross-branch links;
- consistent current-phase and authorization language across README, index, correction report, continuity handoff, and deferred implementation plan;
- visible unresolved findings, historical preservation obligations, and unaccepted governance proposals;
- a reproducible fresh-reader continuity test;
- Builder self-review, genuinely independent review, and the required authority decision.

The current audit records blockers F-01 through F-11 and measurable exit criteria DF-01 through DF-13. Those findings are not considered closed merely because this addendum exists. Closure requires the evidence and review specified in the audit.

**Current phase:** Initial Documentation Foundation Completion Gate.  
**Stage A:** Not started; held pending acceptance of this gate.  
**Implementation:** Not authorized.

---

**End of correction.**
