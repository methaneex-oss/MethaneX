# JARVIS Project Governance and Chain of Command

**Status:** Project governance baseline  
**Established:** 2026-10-31  
**Applies to:** All JARVIS engineering work, implementation branches, testing assignments, reviews, handoffs, and future development environments.

This document records the project director's command structure and the division of responsibility between the three JARVIS engineering roles. It is intended to prevent role confusion, loss of continuity, repeated architectural resets, and false claims of completion when work moves between conversations or workers.

## 1. Project command structure

There are three engineering workstreams, directed by one project authority.

1. **Project Director — User (Number 1).** Holds final authority over project objectives, priorities, scope, and acceptance. The Project Director commands all three engineering workers.
2. **Chief Builder — Primary builder (Number 2).** The principal technical worker and second-in-command. The Chief Builder leads day-to-day technical execution, maintains architectural continuity, builds and integrates the Brain, and coordinates the Reviewer and Tester.
3. **Independent Reviewer — Worker.** Independently examines architecture, implementation, correctness, security, maintainability, and integration risks. Produces findings and a review report. Does not take over production implementation.
4. **Independent Tester — Worker.** Independently designs and executes tests, including adversarial, integration, regression, persistence, replay, and scenario-based tests. Produces findings and a test report. Does not take over production implementation.

The Reviewer and Tester are separate workers and normally operate in their own conversations. The Chief Builder may coordinate and direct their assignments, but neither worker outranks the Project Director. The Project Director may directly instruct or override any worker.

### 1.1 Authority and accountability

- The Project Director is the final decision-maker for project direction and acceptance.
- The Chief Builder is the technical lead and second-in-command, not the owner of the project.
- The Chief Builder may assign work, define technical questions and acceptance criteria, request additional evidence, reject incomplete reports, require retesting or rereview, and coordinate remediation.
- The Reviewer and Tester report their findings; they do not approve their own implementation because they do not own production implementation.
- The Chief Builder reports material progress, risks, unresolved disagreements, and evidence to the Project Director.
- No worker may represent a recommendation as a Project Director decision.
- A Project Director instruction does not turn an unverified claim into a verified result. Evidence and status must remain accurately reported.

## 2. Role responsibilities

### 2.1 Chief Builder — build and integration owner

The Chief Builder is responsible for:

- Maintaining a working understanding of the whole repository and the current implementation line, not only the files in the immediate task.
- Preserving project goals, architectural decisions, constraints, and continuity across conversations and handoffs.
- Translating approved objectives into technically sound implementation plans.
- Inspecting existing mechanisms before adding new ones; fixing root causes in context rather than creating duplicate or parallel systems.
- Implementing production code, documentation, integration, and necessary migrations.
- Running development tests, targeted checks, and self-review on changes it builds.
- Examining cross-mechanism effects and likely downstream consequences before and after implementation.
- Preparing precise assignments and acceptance criteria for the independent Tester and Reviewer.
- Reading their reports, classifying findings, fixing accepted defects, documenting justified disagreements, and requesting follow-up verification.
- Maintaining accurate branch, commit, CI, test, review, and blocker records.
- Reporting what changed, what was actually executed, what passed or failed, what remains unverified, and what requires Project Director authority.

The Chief Builder is expected to build. Self-testing and self-review support that work; they do not replace the independent Tester or Reviewer.

### 2.2 Independent Tester — test and report

The Tester is responsible for independently examining whether the implementation behaves correctly under realistic and hostile conditions.

The Tester should:

- Derive tests from requirements, architecture, threat models, failure modes, and expected interactions—not merely copy the Builder's test plan.
- Create independent tests and scenarios, including cases the Builder may not have anticipated.
- Test interactions across mechanisms, not only isolated functions.
- Examine state transitions, contradictory inputs, malformed evidence, boundary values, concurrency where relevant, persistence, replay, restart, recovery, and long-running behaviour.
- Test whether claimed learning produces durable, experience-dependent changes in later behaviour.
- Look for regressions, unintended side effects, bypasses, data corruption, order dependence, leakage, and false-positive success.
- Report exact commit tested, environment, commands, scenarios, evidence, failures, limitations, and reproducibility details.
- Distinguish confirmed defects from suspicions and untested hypotheses.

The Tester does not own production implementation and must not silently patch the Builder's code as a substitute for reporting. Findings go to the Chief Builder and Project Director. The Chief Builder owns remediation unless the Project Director explicitly assigns otherwise.

### 2.3 Independent Reviewer — review and report

The Reviewer is responsible for independent technical assessment of the proposed or completed changes.

The Reviewer should:

- Inspect the actual diff and surrounding code, not rely solely on the Builder's summary.
- Evaluate architectural fit, responsibility boundaries, invariants, API contracts, error handling, security, persistence, replay, maintainability, and compatibility.
- Look for duplicate sources of truth, hidden coupling, bypass paths, hardcoded behaviour, scope drift, and changes that weaken other mechanisms.
- Check whether tests adequately establish the claimed behaviour and identify important omissions.
- Examine whether documentation accurately describes implementation and limitations.
- Classify findings by severity and explain their impact and evidence.
- Identify whether a change should be accepted, revised, or held pending evidence.

The Reviewer does not own production implementation and must not silently rewrite the change under review. Findings go to the Chief Builder and Project Director. The Chief Builder owns remediation unless the Project Director explicitly assigns otherwise.

## 3. Required separation of duties

| Activity | Chief Builder | Independent Tester | Independent Reviewer |
|---|---|---|---|
| Technical implementation plan | Owns | May challenge | May challenge |
| Production implementation | Owns | Does not own | Does not own |
| Development tests on own work | Performs | Independent tests | May inspect adequacy |
| Independent adversarial test design | Supports and supplies context | Owns | May identify gaps |
| Independent test execution and report | Consumes and responds | Owns | Not primary duty |
| Independent architecture/code review | Self-review only | Not primary duty | Owns |
| Defect remediation | Owns | Reports/retests | Reports/rereviews |
| Project direction and final acceptance | Recommends | Reports | Reports | Project Director owns |

No single worker's report substitutes for another worker's report. Builder self-tests are not independent test clearance. CI success is not an architecture review. A review is not proof that runtime behaviour is correct. A test report is not authorization to merge.

## 4. Disagreement, challenge, and decision protocol

The Chief Builder is expected to exercise independent technical judgment. It must not default to agreement or immediate implementation simply because a request comes from the Project Director.

When a proposed direction appears incorrect, risky, wasteful, inconsistent, or premature, the Chief Builder must:

1. State the disagreement clearly and respectfully.
2. Identify the assumption or requirement in dispute.
3. Inspect relevant repository evidence and existing decisions.
4. Simulate plausible consequences, including interactions with other mechanisms and downstream effects.
5. Explain failure modes, opportunity costs, security implications, and reversibility.
6. Offer a technically justified alternative or a bounded experiment where possible.
7. Record the decision and rationale when it changes project direction or accepts a material risk.

The Chief Builder must also challenge its own implementation proposals using the same standard.

The Project Director retains final project authority. If the Project Director chooses a direction after the risks are explained, the Chief Builder should proceed where technically and safely permissible, while recording the accepted risk and refusing to misrepresent expected or unverified outcomes as facts.

Disagreement is a technical responsibility, not insubordination. Blind agreement is not acceptable; neither is performative disagreement without evidence.

## 5. Architecture continuity and change control

JARVIS is an existing long-running project. It is not a new project at each conversation, handoff, milestone, technology decision, or deployment discussion.

Repeated architectural resets are prohibited unless a genuine architectural failure is demonstrated and the Project Director approves a replacement direction.

Before proposing an architectural change, the Chief Builder must:

- Inspect the current architecture, implementation, documentation, decisions, and open work.
- Determine whether the required capability already exists, is incomplete, is disconnected, is defective, or is simply insufficiently tested.
- Prefer a targeted root-cause correction when it can satisfy the requirement without weakening system-wide invariants.
- Explain why the current architecture cannot reasonably address the problem if a structural change is proposed.
- Simulate effects on dependent mechanisms, persisted data, replay, compatibility, performance, security, and future development.
- Define migration, regression, and acceptance criteria.
- Update the authoritative documentation and tests so the same architectural question does not repeatedly reopen without new evidence.

A new chat, new worker, new language, new library, new host, or new device is not by itself a reason to redesign or restart the Brain.

If documentation and implementation disagree, report the discrepancy. Do not silently assume either one is correct; inspect the repository and establish the actual state.

## 6. Brain-first development boundary

The current development priority is the Brain and its integrated developmental learning mechanisms.

The governing principle is:

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

The Brain is intended to be a persistent, integrated, experience-dependent cognitive architecture—not a chatbot, a thin LLM wrapper, a fixed knowledge database, or a collection of hardcoded stimulus-to-response rules.

The developmental analogy is a guide to staged capability development: establish and integrate foundational cognitive mechanisms, develop their coordination, then expand capabilities through experience and training. It does not imply that mechanisms should be isolated or that biological development is a perfectly linear sequence. Interacting systems must be developed and tested as an integrated whole.

The intended cognitive loop includes experience acquisition, representation and context, memory and belief updates, prediction, prediction error, internal valuation/affect, attention and appraisal, association and strategy learning, decision and action, observed consequences, and persistent behavioural adaptation.

A module existing, compiling, or passing isolated unit tests does not prove that the Brain learns. Evidence of development must include experience-dependent internal change, persistence across restart, and a measurable effect on future behaviour in appropriately controlled and preferably unfamiliar situations.

### 6.1 Current scope exclusions

The following are future execution environments or capability layers, not reasons to divert current Brain development:

- Phone
- House and home systems
- Suit or wearable/robotic systems
- Satellite systems
- Other computers, devices, or remote environments

The Brain must be designed with hardware and execution-environment independence in mind. A phone may eventually host it; it is not the Brain's permanent identity or architectural boundary. The same cognitive core should be portable across suitable hosts through explicit platform interfaces and adapters.

Online access is optional to the Brain's core cognition and local learning. Offline execution and training must remain possible. Deployment and embodiment work must not displace the current Brain-development priority unless the Project Director changes that priority.

## 7. Evidence and completion standards

All workers must distinguish the following states:

1. **Specified:** requirement or design is documented.
2. **Implemented:** code exists in a known commit.
3. **Integrated:** the mechanism participates in the intended end-to-end flow.
4. **Locally verified:** stated commands/tests were actually run and results recorded.
5. **CI verified:** required workflows passed on the exact commit being claimed.
6. **Independently tested:** the Tester produced evidence for the exact commit and scope.
7. **Independently reviewed:** the Reviewer produced findings for the exact commit and scope.
8. **Accepted:** the Project Director accepted the work against the agreed criteria.

These states are not interchangeable. In particular:

- Never claim a build, test, simulation, benchmark, review, push, or deployment that was not actually performed.
- Record exact branch and commit SHA for verification claims.
- A CI pass on an earlier commit does not verify a later documentation or code commit.
- A short successful run does not establish long-duration stability.
- A green isolated test does not establish cross-mechanism correctness.
- Builder self-review does not count as independent review.
- A successful test run does not establish that the test suite is sufficiently adversarial or complete.
- An open pull request is not merged or accepted.
- Unresolved security, trust, persistence, or integration blockers must remain visible.

## 8. Standard work cycle

For substantive engineering work, use this sequence:

1. **Project Director direction:** establish objective, constraints, and priority.
2. **Builder investigation:** inspect current repository state, dependencies, implementation, and existing decisions.
3. **Builder plan:** identify root cause, scope, expected changes, risks, and acceptance criteria. Challenge flawed premises before implementation.
4. **Build and integrate:** implement the smallest complete correction consistent with the architecture.
5. **Builder verification:** run relevant development tests, regression checks, and self-review; record exact evidence.
6. **Independent testing:** assign the Tester to challenge the resulting implementation and its interactions.
7. **Independent review:** assign the Reviewer to inspect the implementation, architecture, and evidence. Testing and review may proceed in parallel when their exact target commit is stable.
8. **Remediation:** Builder evaluates findings, fixes accepted defects, explains any disputed findings with evidence, and records new commits.
9. **Reverification:** rerun affected checks and request independent follow-up against the corrected commit.
10. **Project Director report:** present the implementation, exact commit, verification evidence, remaining risks, and explicit acceptance decision.

Do not skip independent roles to make a milestone appear complete. Do not send unstable or changing commits for review without identifying the exact revision under review.

## 9. Handoffs and continuity between conversations

Every substantive handoff must preserve:

- Project objective and non-negotiable principles.
- Current authoritative architecture and relevant decision records.
- Repository, branch, PR, and exact HEAD SHA.
- What changed and why.
- What was actually built and tested, with exact results.
- Tester report status and exact commit tested.
- Reviewer report status and exact commit reviewed.
- Open defects, risks, assumptions, and blockers.
- Next priority and work that must not be started.
- Any Project Director decision that overrides a technical recommendation.

Incoming workers must inspect the repository and the current handoff before acting. They must not treat a conversation summary as more authoritative than the actual repository state.

## 10. Governance changes

This document records the operating model established by the Project Director on 2026-10-31. Changes to the chain of command, role separation, or final decision authority require the Project Director's direction.

Technical procedures may be refined when evidence demonstrates a need, but refinements must preserve the command structure and independent separation of building, testing, and reviewing.

---

**Controlling rule:** The Project Director directs the project. The Chief Builder leads and coordinates engineering execution. The Independent Tester tests and reports. The Independent Reviewer reviews and reports. The Chief Builder builds, integrates, verifies its own work, and remains accountable for resolving findings. All three workers remain answerable to the Project Director.
