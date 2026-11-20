# Phase 1 — Whole-Repository Investigation, Reuse and Conflict Audit

> **Whole-Brain scope correction — 2026-11-07:** This report is a repository inventory and static reuse/conflict investigation at the exact baseline recorded below. It is not the complete definition or completeness proof of the future Brain. Preserve its source findings; do not treat BM-01–BM-12 coverage or reuse classifications as a final whole-Brain architecture or development decision. The corrected planning sequence and Builder error record are in [Whole-Brain Planning Scope and Builder Correction](WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).

**Date:** 2026-11-04  
**Repository:** methaneex-oss/MethaneX  
**Audited main baseline:** 1273ddbcd0087d189e01388ded2d362fb1e058d2  
**Learning-development donor:** PR #97, exact inspected head c1da222e6c94aeb3f2ad000392c21fe4fc81ab25  
**Integrated donor tree:** 15d49e5fdeb5723c475922ab78fb92f97c4b3b84  
**Governing Brain specification:** PR #174, accepted head 0811a59e46bf934e32e794f90e4e7d18d4e2bd97  
**Planning PR:** #175, open/draft/unmerged  
**Donor-correction PR:** #176, open/draft/unmerged  
**Disposition:** Phase 1 inventory and reuse/conflict investigation complete. Formal Gate A is not cleared. No implementation baseline is selected.

---

## 1. Executive result

The repository is not an empty foundation and does not need to be restarted. It contains a substantial C++ cognitive substrate, a large unmerged cognitive/affective development branch, a later integrated donor containing knowledge and compositional-learning work, a meaningful evolution and execution-safety subsystem, and a separate engineering-agent layer.

The central finding is that **the strongest existing work is real and reusable, but it is not yet one accepted, specification-complete, integrated Brain**. Current main and the candidate branches represent materially different states. Treating main as the whole project would discard valuable work; treating PR #97 or PR #156 as an already-complete Brain would overstate what has been demonstrated.

Recommended direction:

1. Preserve the accepted whole-system and Brain architecture/specification as the governing design authority.
2. Use accepted PR #174 as the integration starting point.
3. Treat PR #97 and the later PR #148 → #155 → #156 work as donor sources, not as a wholesale baseline.
4. Selectively port mechanisms only after state ownership, event contracts, persistence/replay behavior, API compatibility and fit against BM-01 through BM-12 are checked.
5. Retain deterministic infrastructure and safety constraints, but do not let provisional fixed cognitive policies become permanent situation-specific behavior.
6. Keep Rust, TypeScript and engineering-agent code in their proper roles until one cognitive authority and explicit cross-language contracts are established.

**The Phase 1 audit is complete as a repository inventory and reuse/conflict assessment. Gate A remains formally NOT CLEARED.** Its remaining blockers are specific donor-correction, failure-injection and independent-review obligations—not a reason to restart the audit.

### Blunt conclusion

There is enough existing work to move forward. There is not enough evidence to say the present repository already behaves like a developed JARVIS or a human-level learning system. The most valuable next move is integration against the accepted architecture, not adding more disconnected modules and not adopting the largest branch wholesale.

---

## 2. Scope, method and limits

This audit covers the complete tracked-file inventory at the pinned main tree; the core C++ Brain source, interfaces, tests and build registration; the unmerged cognitive/action-feedback and affective development branch; the knowledge, contradiction-resolution, compositional-learning and evolution-replay donor line; the Rust, TypeScript and engineering-agent areas; the active CI/workflow surface and selected exact-run evidence; the current and proposed architecture, governance, blueprint and preservation documents; and the existing Gate A provenance, API, workflow and defect reports.

The work is repository archaeology and static technical investigation. I inspected critical dataflows and high-risk implementation areas, compared candidate source and test behavior, checked PR metadata and selected GitHub Actions logs. I did not run a new local build, alter runtime source, merge branches, rebase, cherry-pick, delete files or select an implementation baseline. CI results below are results from the identified GitHub Actions commits, not a claim that I reran those jobs.

This is not a line-by-line correctness certification of every source line. The complete tree and path origins are inventoried; critical cognitive paths and candidate integration risks were examined in depth. Runtime capability still requires executable, adversarial and longitudinal evidence.

---

## 3. Repository inventory at the audited main commit

The audited main tree contains **200 tracked files**:

| Area | Files |
|---|---:|
| Core C++ public headers | 58 |
| Core C++ implementation files | 58 |
| Core C++ test source files | 48 |
| Engineering-agent C++ headers | 5 |
| Engineering-agent C++ implementation files | 5 |
| Engineering-agent C++ test source files | 1 |
| Rust crate files: Cargo manifest plus Rust sources | 4 |
| TypeScript interface files | 3 |
| GitHub Actions workflows | 10 |
| Markdown documentation and notes | 5 |
| Other configuration/text files | 3 |
| **Total** | **200** |

The core C++ test CMake file registers **45 executable/test targets**. Three C++ test source files exist in the tree but are not registered by that CMake file:

- brain_smoke.cpp
- evolution_experiment_test.cpp
- representation_suite.cpp

Their presence is not evidence that normal CTest runs execute them. They need an explicit retain/register/archive decision during later test consolidation.

The main tree has separate CMake projects for core/cpp and engineering/cpp; there is no root-level integrated build definition in the audited tree. Rust has its own Cargo manifest. TypeScript has interfaces but no TypeScript package/build manifest in the audited tree. No Python source files are present, despite Python appearing in the README language strategy.

**Inventory interpretation:** the repository is C++-dominant. The polyglot claim is presently a mixture of a substantive C++ Brain, a small Rust cognition/runtime prototype, TypeScript transport/operator contracts and a separate C++ engineering-agent subsystem. It is not yet a demonstrated integrated multi-language cognitive runtime.

---

## 4. What already exists on main

### 4.1 Brain state, events and continuity

Relevant source: core/cpp/include/jarvis/core/brain.hpp, core/cpp/src/brain.cpp, core/cpp/include/jarvis/core/event.hpp and core/cpp/src/memory.cpp.

The C++ Brain owns persistent event history and reconstructs much of its internal state by replaying journaled events during construction. This is a valuable foundation: state changes can be tied to experience records rather than existing only as transient in-memory values.

Memory provides sequenced event append, binary serialization, journal loading and valid-prefix recovery behavior, a separate metadata sidecar, recent/history access, structured attribute-based ranked recall, salience and confidence metadata, and memory-tier bookkeeping/consolidation support.

**Verdict: REUSE THE EVENT/CONTINUITY FOUNDATION, WITH INTEGRITY AND RETRIEVAL ADAPTATION.**

It is not a general semantic memory system yet. Recall ranking scores overlap between query attributes and stored event attributes, with recency, salience and confidence contributing. This is useful structured episodic retrieval, but it does not demonstrate semantic retrieval, abstraction, autobiographical understanding or broad generalization.

The current journal is also not a complete tamper-evident trust system. The Priority-One trust-boundary contract in PR #160 explicitly identifies valid-boundary truncation, whole-file rollback, metadata integrity, external anchoring, cryptographic framing and production provenance as unresolved requirements. The existence of an append-only journal is not equivalent to authenticated, rollback-resistant storage.

**Decision:** retain the event model and replay architecture. Do not mistake the current journal for a final memory-integrity solution. Keep the PR #160 trust-boundary contract as a required engineering input, not as implemented functionality.

### 4.2 Perception and representation

Relevant source: representation.hpp/.cpp, perception_pipeline.hpp/.cpp and world_state.hpp/.cpp.

The main tree has canonical representation structures for attributes, semantic nodes, relations, confidence and evidence spans. The perception pipeline supports provider registration, provider capability checks, candidate validation, exception isolation, confidence-based candidate selection and a deterministic normalization fallback.

This is a good mechanism boundary: providers can contribute perception without becoming the Brain itself.

However, no concrete vision, speech, audio or other external perception provider implementation was found in the audited main tree. Fallback modality classification maps a small set of exact source strings such as voice, speech, vision, camera, audio, microphone, sensor and system. The fallback is structured normalization of supplied event data, not raw multimodal perception.

**Verdict: REUSE THE PROVIDER/REPRESENTATION CONTRACT; ADAPT THE FALLBACK AND PROVIDER DISCOVERY.**

The exact source-name mapping is a brittle adapter convention. It should not become the Brain's general understanding of modality. Provider identity, declared capabilities and validated output should determine the boundary.

### 4.3 World model and knowledge

Relevant source: world_model.hpp/.cpp, knowledge.hpp/.cpp and causal_model.hpp/.cpp.

The main WorldModel stores facts and relations, updates confidence for repeated matching facts, and retains conflicting facts or relations as disputed evidence. The KnowledgeModel tracks source reliability using a running average. The causal model observes state transitions, stores causal links, simulates supported consequences and weakens hypotheses when predictions fail.

These are reusable foundations, but their current semantics are limited:

- A conflicting fact can be marked disputed and a higher-confidence incoming fact can replace the current value. The main model does not fully accumulate, compare and adjudicate support for every competing alternative.
- Conflicting relations can be retained and marked disputed, but the main model does not provide a complete evidence-sensitive resolution lifecycle.
- Source reliability is keyed by a source string and averaged. It is not yet a full provenance system establishing source identity, independence, host-verified origin, freshness and evidence lineage.
- The main causal model is a relatively narrow transition learner. It does not establish broad causal discovery under confounding, counterfactual reasoning or reliable transfer to arbitrary domains.

**Verdict: REUSE THE DATA STRUCTURES AND EVENT-DRIVEN UPDATE DIRECTION; ADAPT THE EVIDENCE AND CONFLICT SEMANTICS.**

PR #148 is the important donor for competing alternatives, evidence accumulation, stronger post-conflict evidence, source/provenance separation and replay-order validation. It is not a merged main-branch capability.

### 4.4 Reasoning

Relevant source: reasoning.hpp/.cpp and cognitive_cycle.hpp/.cpp.

The current ReasoningEngine checks premise consistency and performs bounded forward inference over encoded causal links. It can derive a conclusion when a supplied cause is known and the effect is not already present.

That is useful, but it is not a general reasoning capability. The inspected implementation does not provide the full range required by the accepted Brain specification: robust inductive, abductive, analogical, temporal, spatial, counterfactual and constraint reasoning, with explicit assumptions, alternatives, provenance and premise lineage.

A concrete integration gap exists in the current cognitive cycle:

1. It retrieves ranked memories into the cycle context.
2. It obtains current beliefs and causal links.
3. It constructs the ReasoningProblem from beliefs and causal links.
4. The retrieved memories are not supplied to that reasoning call.

Memory retrieval is therefore available in the context, but it does not materially participate in that reasoning operation.

**Verdict: REUSE THE REASONING INTERFACE AND CAUSAL-INFERENCE COMPONENT AS A NARROW SPECIALIST; REDESIGN/EXPAND THE GENERAL REASONING AUTHORITY.**

The accepted PR #174 specification explicitly added BM-12 for general reasoning and requires memory-supported reasoning with retained provenance and contextual limits. The current main ReasoningEngine should not be represented as satisfying BM-12.

### 4.5 Attention, decision and threat assessment

Relevant source: attention.hpp/.cpp, attention_state.hpp/.cpp, decision.hpp/.cpp and threat.hpp/.cpp.

Attention combines novelty, uncertainty and urgency using policy weights, ranks signals and supports reinforcement/suppression. Decision ranking uses a weighted score over utility, expected value, goal alignment, plan value, uncertainty, threat, risk, resources, consequences and urgency. Threat assessment maps anomaly, integrity risk, intrusion risk and explicit threat inputs into a weighted score and fixed posture bands.

These mechanisms are not all the same kind of rule:

- Permission, risk, reversibility and resource limits are appropriate candidates for deterministic infrastructure constraints.
- Decision weights, attention priorities and threat aggregation are cognitive appraisal policies. They should be calibratable, context-sensitive where justified, and evaluated against evidence.
- Fixed thresholds may be useful initial safety defaults, but they are not proof of learned judgment.

The current main decision formula has explicit fixed default weights and act/reject/clarify/escalate thresholds. The threat model uses fixed coefficients and fixed posture cutoffs. Attention policy weights can be reinforced or suppressed in memory, but the main implementation does not establish a complete persistent, experience-acquired attention policy across the entire Brain.

**Verdict: REUSE THE SEPARATION OF ATTENTION, DECISION AND THREAT RESPONSIBILITIES; ADAPT THE POLICY LEARNING AND VALIDATION.**

Do not remove deterministic safety boundaries in an attempt to remove hardcoding. Remove or replace arbitrary fixed cognitive behavior, not enforceable security and execution invariants.

### 4.6 Goals, intent and planning

Relevant source: goals.hpp/.cpp, intent.hpp/.cpp, strategy.hpp/.cpp, planning.hpp/.cpp and cognitive_cycle.cpp.

The GoalModel supports goal creation, activation, progress, completion, abandonment, priority, prerequisites and deadlines. Planning scores candidate actions and produces plans under supplied constraints.

The current main CognitiveCycle selects a supplied goal ID if provided; otherwise it selects the first eligible goal. This is deterministic selection among already-existing goals, not autonomous experience-acquired goal formation. The main branch does not establish a complete developmental motivation system.

**Verdict: REUSE GOAL STATE AND DEPENDENCY PRIMITIVES; ADAPT GOAL FORMATION, CONFLICT ARBITRATION, INTENT AND STRATEGY LEARNING.**

The candidate PR #97 branch has richer intent, affect-aware planning and developmental strategy integration, but the later integrated donor line contains a confirmed wrong-goal strategy-context defect. The fix is on PR #176, not merged into the donor.

### 4.7 Action assessment, authorization and execution

Relevant source: action_model.hpp/.cpp, action_authorization.hpp/.cpp and action_execution.hpp/.cpp.

The main tree separates action assessment from authorization and execution. Authorization checks assessment disposition, risk ceiling, reversibility requirement and explicit permissions. Execution handles callback failure, verification and optional rollback.

This separation is correct and should be preserved. It is not undesirable hardcoding: these are explicit control and safety contracts.

The limitation is integration. In the current main CognitiveCycle, the cycle produces action assessments; it does not itself run the complete observe → choose → authorize → execute → observe consequence → persist feedback loop. The action executor exists, but the integrated Brain-owned action/consequence feedback path is substantially more developed in PR #97.

**Verdict: REUSE THE AUTHORIZATION/EXECUTION BOUNDARY; PORT THE BRAIN-OWNED FEEDBACK LOOP SELECTIVELY.**

The Brain must remain the authoritative owner of experience, beliefs, predictions and learned state. Runtime transport should not become a competing cognitive policy owner.

### 4.8 Learning, prediction and adaptation

Relevant source: adaptation.hpp/.cpp, learning_loop.hpp/.cpp, causal_model.hpp/.cpp and brain.cpp.

The main tree has prediction records, prediction feedback, an adaptation metric, running prediction error and estimate updates, and an evolution proposal path. This proves there is learning machinery in the repository. It does not prove broad developmental learning.

The current AdaptationModel uses cumulative averages for bounded numeric predictions. The LearningLoop accepts finite feedback, updates adaptation and fitness, proposes evolution changes and adopts a proposal only when confidence and expected-gain thresholds pass. Those thresholds are fixed policy values in the current implementation.

Limitations:

- cumulative averages can be slow to adapt to non-stationary regimes;
- numeric prediction handling is narrow and bounded;
- a stored and resolved prediction proves feedback plumbing, not improved predictive accuracy;
- generalization beyond a trained context is not established by main alone;
- a successful evolution proposal is not the same as broad cognitive self-improvement.

**Verdict: REUSE PREDICTION/ERROR/ADAPTATION DATAFLOW; ADAPT THE LEARNING REGIMES AND REQUIRE HELD-OUT LONGITUDINAL EVIDENCE.**

### 4.9 Evolution, isolation and rollback

Relevant source: evolution.hpp, evolution_controller.hpp/.cpp, evolution_experiment components, evolution_sandbox, process_isolation, evolution_adoption_journal, evolution_canary and evolution_rollback.

This is one of the strongest engineering areas. It contains candidate proposal/evaluation, experiment coordination, bounded isolated execution, fitness comparison, safety checks, adoption journaling, canary monitoring and rollback support.

These mechanisms are useful for safe internal model/parameter evolution. They are not yet a general autonomous architecture-rewriting system.

The later donor work also exposed multi-event failure-ordering obligations. PR #176 adds deterministic failure/replay tests for selected goal-completion and evolution rollback boundaries. A deeper controller-internal compensation failure boundary remains un-injected in the latest closure report.

**Verdict: REUSE THE EVOLUTION EXPERIMENT AND SAFETY SUBSTRATE SELECTIVELY; RETAIN THE FAILURE-INJECTION GATES.**

Do not let the existence of an evolution subsystem imply that every part of the Brain can safely evolve itself.

### 4.10 Self-model, reflection, resilience and capabilities

Relevant source: self_model, self_state, reflection, resilience, self_testing, capability_registry, capability_evaluator and capability_execution.

The current tree can represent capability health, active goals, workload, uncertainty and internal state; it has reflection and self-testing/healing mechanisms; and it has a capability registry/evaluation/execution boundary.

These are valuable foundations. Their current demonstrated scope is closer to system health and capability bookkeeping than a comprehensive self-model that understands its own cognitive competence, assumptions, limitations, causal failures, alternative strategies and developmental trajectory.

**Verdict: REUSE THE HEALTH, CAPABILITY AND RECOVERY PRIMITIVES; EXPAND METACOGNITIVE AND SELF-MODEL SEMANTICS AGAINST BM-10.**

---

## 5. Major donor: PR #97

**PR #97:** JARVIS cognitive + affective development  
**Branch:** feat/jarvis-affective-state  
**Exact inspected head:** c1da222e6c94aeb3f2ad000392c21fe4fc81ab25  
**State:** open, draft, unmerged  
**Changed files:** 159

PR #97 is not a minor feature branch. It is a substantial implementation line adding or integrating experience memory, representation/perception, belief and world state, causal learning, attention, reasoning, goals/intent, planning, action execution feedback, affective state, developmental strategy learning, prediction feedback and evolution support.

The branch's cognitive loop is materially more integrated than current main:

- retrieves prior episodic/action experience;
- records and represents new observation;
- updates beliefs and world/causal context;
- computes attention, appraisal and reflection;
- makes forecasts;
- uses learned context/action strategies in planning and decision;
- executes selected actions through a runtime adapter;
- records observed consequences and routes feedback back through Brain-owned state;
- reconstructs relevant learning state from journal history.

That is significant reusable work. It is not a finished learning Brain.

### 5.1 Affective state

PR #97 adds continuous state variables such as valence, arousal, uncertainty, tension and stability. Its affective appraisal learner adapts sensitivity weights from observed consequences and calibration error. Affective signals influence attention, planning, memory significance and decision appraisal.

This is directionally compatible with avoiding named-emotion-to-fixed-action mappings. The state is continuous and consequence-sensitive.

However, the state dynamics still contain fixed equations, normalization, decay constants and default weights. Those are engineered inductive biases, not learned biological or general-purpose affective mechanisms. They should be retained only where their assumptions are explicit and empirically validated. This is a useful affective substrate, not a complete affective system.

### 5.2 Developmental strategy learning

PR #97 adds context/action strategy learning and related-context transfer. The mechanism does not simply encode one fixed route outcome for every situation. It stores outcome evidence and can influence later action values.

However, transfer uses explicit context tokenization, a fixed negator list, slash-delimited context hierarchy, feature-schema parsing, similarity calculations and default thresholds. These are fixed representation and transfer assumptions. They are not direct stimulus-to-action mappings, but they constrain what counts as a similar situation.

The later PR #151 adds a per-action online additive feature model. It is a stronger step because it can combine learned feature contributions for an unseen feature combination rather than relying only on the nearest complete context.

That model still has a fixed learning rule, additive structure, feature schema, evidence-support cap and confidence threshold. It does not learn arbitrary feature interactions. It is a promising constrained generalization mechanism, not unrestricted general intelligence.

### 5.3 PR #97 audit findings

The recorded exact-head learning-machinery audit identifies these limitations:

1. Causal transition semantics on PR #97's exact head were incomplete. PR #135 corrected use of the pre-transition state and exclusion of unchanged effects.
2. PR #137's DLT-003 tested changing action mappings, reversal and restart, but all evaluated contexts were trained. It did not establish held-out transfer.
3. PR #97's world-model contradiction resolution was incomplete. PR #148 adds evidence accumulation and adjudication.
4. Prediction feedback plumbing did not by itself prove prediction quality improved. The recorded earlier DLT-002 result had final prediction MAE worse than early MAE.
5. Evolution replay required stronger trust and authenticated evidence controls.

The same audit explicitly recorded that PR #97 itself had no exact-head workflow runs returned at that inspection. Do not substitute later or earlier branch runs for an exact-head PR #97 validation claim.

**PR #97 verdict: HIGH-VALUE DONOR; NOT A COMPLETED BRAIN; DO NOT MERGE WHOLESALE.**

---

## 6. Stronger learning evidence: what it proves and what it does not

### 6.1 PR #99 learning-mechanisms workflow

PR #99 is merged, but its only changed file is the GitHub Actions workflow. The workflow runs explicit mechanism gates and a bounded changing-environment trial against a supplied source reference.

The inspected successful run recorded:

- source reference: feat/jarvis-affective-state;
- exact tested commit: 8525de774493de7c8eab05baa98af94cd068e995;
- duration: 600 seconds;
- seed: 20261026;
- 35/35 explicit mechanism gates passed;
- integrated DLT-002 trial completed with 587 episodes and all six configured phases present.

This is real evidence that the tested revision could compile, pass those named gates and complete that bounded synthetic trial.

It is **not** a four-hour run, not an exact-head validation of PR #97 at c1da222, and not proof of robust real-world learning. The run tests an earlier commit on the branch. The integrated trial is an engineered environment with predeclared phases and a controlled set of actions.

### 6.2 PR #137 / DLT-003

The later DLT-003 line tests action-mapping change, reversal and restart over two seeds. The PR #97 audit correctly notes that all contexts used for evaluation were trained. It is useful evidence of context-specific adaptation and reversal, but not held-out compositional generalization.

### 6.3 PR #151 / DLT-004

PR #151 is a stronger donor for generalization. Its DLT-004 test:

- trains on five combinations of environmental feature values;
- withholds the open/poor/rough combination from outcome training;
- varies the successful action label by seed;
- checks feature coverage and confidence;
- checks source and goal isolation;
- checks that the held-out action is selected;
- introduces contradictory later outcomes and checks that the held-out decision revises;
- restarts the Brain and checks that the learned decision and related evidence are reconstructed;
- checks that an execution failure with no observed consequence does not train feature utility;
- checks that many repetitions of one context or contradictory samples do not manufacture independent support.

Five seeds are run by the test. The four PR #151 GitHub Actions workflows at its exact head completed successfully.

This is the strongest existing evidence of experience-dependent compositional transfer found in the inspected donor line. Its limits remain important: it is a small synthetic environment, two candidate actions, three explicit features, a linear additive model and a controlled set of training/test combinations. It does not prove open-world generalization, rich causal understanding or transfer across arbitrary domains.

**Learning verdict:** the repository contains genuine experience-dependent behavior-change mechanisms and at least one serious held-out feature-composition experiment. It does not yet demonstrate broad, robust, open-ended learning. The next standard must require held-out environments, changing regimes, independent seeds, prediction-quality tracking, replay and failure tests, and comparison with fixed-policy controls.

---

## 7. Hardcoding audit

The project principle is: **engineer the mechanisms; let behavior be acquired through experience.** The investigation found fixed logic, but it is important not to label every deterministic rule a violation.

### 7.1 Determinism that should remain

These are legitimate infrastructure or safety constraints unless evidence shows otherwise:

- event sequence validity and journal framing;
- finite-value validation and bounded numeric domains;
- permission checks and execution authorization;
- risk ceilings and reversibility requirements;
- process isolation, timeouts and output limits;
- evidence identity and replay consistency;
- idempotency and rollback invariants;
- explicit provider capability contracts;
- schema and API validation.

Removing these to make the Brain appear more adaptive would weaken it.

### 7.2 Fixed cognitive policies that need evaluation or adaptation

These are not automatically wrong, but they must not silently become permanent universal behavior:

- weighted decision scoring and fixed act/reject/escalate thresholds;
- fixed threat aggregation coefficients and posture cutoffs;
- fixed attention weights and prioritization assumptions;
- fixed novelty and similarity calculations;
- fixed learning rates, confidence thresholds and adoption thresholds;
- deterministic selection of the first eligible goal when no goal ID is supplied;
- exact source-name-to-modality mapping;
- context-token, negator and hierarchy heuristics in developmental transfer;
- fixed additive feature-model structure and support rules.

These should be documented as initial assumptions or bounded policies, exposed to evaluation, and changed only through validated learning or an explicitly justified safety contract.

### 7.3 Hardcoded behavior versus a controlled training environment

The DLT tests deliberately define synthetic worlds, phases, feature names and action consequences. That is acceptable as a test harness: the environment must have a known ground truth to measure learning.

The risk arises if those environment labels, route mappings or phase assumptions leak into production Brain policy. The DLT-004 test makes a meaningful attempt to prevent leakage by excluding task/context/episode labels and withholding the held-out combination. The runtime's feature extraction and additive model still encode assumptions that require broader validation.

### 7.4 Specific findings

| Finding | Classification | Disposition |
|---|---|---|
| Main decision weighted sum and thresholds | Fixed cognitive policy | Adapt/calibrate; not final judgment |
| Main threat coefficients and posture bands | Deterministic risk policy | Retain as provisional guardrails; validate |
| Exact modality source-name mapping | Brittle adapter convention | Replace with provider/capability identity |
| First eligible goal fallback | Fixed selection behavior | Replace with intent/goal arbitration and learned formation |
| Memory attribute-overlap ranking | Narrow retrieval algorithm | Retain as baseline retrieval; add richer retrieval |
| Causal link threshold and decay | Fixed model assumptions | Validate against diverse causal tasks |
| DLT phase/route labels | Test-environment design | Keep isolated from runtime behavior |
| Permission/risk/reversibility checks | Safety invariants | Preserve |
| PR #151 linear feature learner | Learned model with fixed structure | Donor; expand and test interaction limits |
| PR #97 affective equations and decay | Engineered affective dynamics | Donor; retain only with calibration evidence |

**Hardcoding verdict:** the repository is not simply a hardcoded behavior engine. It contains learned state updates and experience-dependent decision changes. It also contains many fixed cognitive assumptions. The task is to separate the safety substrate from provisional cognitive policy and make the latter earn its place through evidence.

---

## 8. Polyglot and engineering-agent audit

### 8.1 Rust runtime

The Rust crate contains a small BrainRuntime, CognitiveState and Belief model. It stores beliefs in a HashMap, updates evidence strength and keeps a bounded working-memory vector.

This is a prototype-level state container. It does not implement the C++ Brain's event journal, world model, reasoning, prediction, affect, action, evolution or integrated learning loop. If it becomes an independent cognitive state owner, the system risks two competing brains.

**Verdict: DO NOT TREAT AS A SECOND BRAIN.** Retain only as a prototype or future runtime component behind an explicit contract to the authoritative Brain.

### 8.2 TypeScript interfaces

The TypeScript files define observation/decision/capability interfaces, Brain transport contracts, agent bridge messages and operator sessions. They are useful boundary definitions.

No concrete transport implementation or complete cross-language runtime was found in the audited tree. The interface layer does not itself execute cognition.

**Verdict: RETAIN AS INTERFACE/TRANSPORT CONTRACTS; DO NOT ATTRIBUTE COGNITIVE CAPABILITY TO THEM.**

### 8.3 Engineering-agent C++

The engineering subsystem provides agent descriptors, task eligibility/ranking, authorization-aware dispatch, an in-process message bus, bounded pending queues and an operator console.

This is relevant to a future multi-agent software-building workflow. It is not the JARVIS cognitive Brain. Its current message bus is in-process and its visible source does not establish durable shared memory, cross-process coordination, distributed consensus or a complete shared workspace.

**Verdict: RETAIN AS A SEPARATE ENGINEERING-ORCHESTRATION SUBSYSTEM.** Do not merge its task/agent state into the Brain's cognitive authority.

### 8.4 Cross-language decision

The accepted architecture's one-coherent-cognitive-authority principle is the correct constraint. The polyglot implementation must assign each language a bounded responsibility and define versioned contracts, ownership, persistence and failure semantics. Language diversity alone is not integration.

PRs #164, #167 and #168 contain technology and language-ownership proposals, but they remain open/draft proposals. They should inform later design, not override the accepted PR #173 architecture.

---

## 9. PR and branch lineage — what is available and what is authoritative

### 9.1 Current main

Main remains at 1273ddbcd0087d189e01388ded2d362fb1e058d2 in the inspected snapshot. It does not contain the full PR #97 cognitive/affective development line.

### 9.2 Cognitive/action-feedback development

- **PR #96:** open/draft/unmerged; 51 changed files; separate cognitive action-feedback loop proposal with Brain, CognitiveCycle, authorization, execution and runtime boundaries.
- **PR #97:** open/draft/unmerged; 159 changed files; major cognitive and affective development line.
- **PR #99:** merged; adds the learning-mechanisms workflow, not the full PR #97 Brain implementation.

PR #96 and #97 overlap in responsibility. They are donor/history references, not independent complete systems to merge together.

### 9.3 Learning, knowledge and evolution donor chain

- **PR #135:** causal transition correction.
- **PR #137:** DLT-003 changing action-mapping test.
- **PR #148:** evidence-sensitive contradiction resolution, provenance and source-feedback safeguards.
- **PR #150:** evolution replay/evaluation evidence hardening.
- **PR #151:** compositional feature learning and DLT-004.
- **PR #155:** integration of knowledge safeguards and compositional learning.
- **PR #156:** integrated candidate combining knowledge, compositional learning and evolution replay safeguards.

These are not all merged into main. PR #156 is an integrated donor candidate, not an approved production baseline.

The existing Gate A reconciliation records a 165-path main-to-candidate tree delta. Its corrected path-origin partition is:

- 143 paths changed by PR #97 and byte-for-byte unchanged after PR #97;
- 16 paths changed both in PR #97 and in the later integration segment;
- 2 existing paths modified only after PR #97;
- 4 files first introduced after PR #97.

The earlier 145/14/6 classification was corrected. The risk-based provenance report records exact path/blob checks and high-risk source attribution. The residual 1,416-commit hunk ledger is not required for the current baseline recommendation because the candidate is not being adopted wholesale; each future selective port must still receive its own semantic and BM-01–BM-12 review.

### 9.4 Architecture and specification authority

- **PR #171:** whole-system architecture foundation; open/draft/unmerged. Its documents 00 and 01 received scope-limited approvals. The research package had a separate review/correction history and must not be described as automatically approved in its entirety.
- **PR #172:** foundational Brain capability investigation; accepted at exact head d7d676b79dbf3269f7fd3ebdb4363a6df19f255d.
- **PR #173:** Brain Foundation Architecture; accepted planning baseline at exact head 97191111bc2573c14d391c0af9628db7b11f194b.
- **PR #174:** Integrated Brain Mechanism Specification; accepted planning baseline at exact head 0811a59e46bf934e32e794f90e4e7d18d4e2bd97. It includes BM-12 general reasoning. A BM-07/SYS-05/SYS-08 boundary clarification remains a documented non-blocking refinement to carry forward before implementation relies on that boundary.
- **PR #175:** implementation roadmap and Gate A evidence; open/draft/unmerged. It is a planning proposal, not implementation authorization.
- **PR #176:** donor corrections and deterministic journal failure/replay tests; open/draft/unmerged.

The accepted architecture/specification is the authority for later integration decisions. Older implementation plans and branch descriptions cannot silently override it.

---

## 10. Gate A status — why the baseline is still not cleared

The existing Gate A reports materially advanced the evidence:

| Workstream | Current documented state |
|---|---|
| Risk-based provenance | Closed for the baseline recommendation under the risk-based standard |
| Static API declarations and in-repository call sites | Closed within core/cpp; external ABI/downstream compatibility remains a later compile/link gate |
| Five workflow continuity specifications | Closed as specifications; workflow adaptation and execution remain future work |
| D1/D2 candidate defects | Corrected on PR #176 and CI-verified there; not merged into PR #156 |
| Goal/evolution multi-event consistency | Partially closed; deeper controller-internal compensation failure injection remains open |
| Independent re-check | Open; a separate reviewer identity and actual submitted review remain outstanding |

### 10.1 Confirmed defects

**D1 — learned-strategy context mismatch.** In the donor candidate, strategy retrieval could use a higher-priority pending goal rather than the selected active intent. PR #176 changes both Brain::choose and Brain::choose_with_affect to use the selected intent identity, with an explicit global fallback when no intent is selected.

**D2 — non-finite goal values can reach the journal.** The donor candidate could journal a goal event before the model rejected invalid numeric state. PR #176 rejects NaN and positive/negative infinity for priority/progress before event creation or append.

Both fixes have regression coverage on PR #176. The PR is not merged into PR #156.

### 10.2 Exact PR #176 CI evidence

At exact head 4cf017e073da980c9f77d739fde6f92ef1a2fbc1, the following four GitHub Actions runs completed successfully:

- Native Brain Build: run 41808525486;
- Brain ThreadSanitizer: run 41808525492;
- Brain CI: run 41808525499;
- JARVIS Brain Tests: run 41808525557.

The inspected logs show 73/73 tests passed in the native, sanitizer and ThreadSanitizer CTest jobs. This is strong candidate-donor evidence. It does not make PR #176 merged, does not prove external ABI compatibility, and does not validate the five long-running workflow contracts.

### 10.3 Residual failure boundary

PR #176 tests selected journal append failures, replay recovery and idempotency for goal completion and evolution rollback. The deeper failure of controller-internal compensation—such as restoring adoption-journal/history state after an injected failure—remains unverified in the latest closure evidence. A later branch-ref test claim was explicitly not counted because it was not present in the verified PR head.

### Gate A decision

**Gate A remains NOT CLEARED. PR #156 remains a selective source donor only. No implementation baseline has been formally selected.**

The technical direction is clear; the formal evidence and approval gate is not complete. A Builder-side recommendation or a technical review document is not a submitted independent GitHub review and is not Project Director authorization.

---

## 11. Documentation and artifact preservation

The audit found several generations of documentation. They should not be deleted merely because newer architecture work exists.

### 11.1 Preserve as current planning authority

- PR #171 whole-system architecture foundation and anatomy/responsibility map, within their approved scope.
- PR #172 accepted foundational capability investigation.
- PR #173 accepted Brain Foundation Architecture.
- PR #174 accepted Brain Mechanism Specification.
- PR #175 implementation roadmap and its Gate A evidence, clearly marked as proposal/not cleared until the formal gate is closed.

### 11.2 Preserve as implementation evidence and donor history

- PR #97 cognitive/affective implementation and tests.
- PR #96 action-feedback implementation proposal.
- PR #135/#137 causal and learning tests.
- PR #148/#150/#151/#155/#156 knowledge, compositional learning and evolution integration.
- PR #176 defect corrections and failure-injection tests.
- Existing DLT/JBP test workflows and run artifacts.

These should remain discoverable as source evidence, not presented as already merged or approved capabilities.

### 11.3 Mark as historical, superseded or non-authoritative

The main-branch docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md describes a fixed Layer 0–19 construction order. It is useful historical planning material, but treating it as the governing architecture would conflict with the newer accepted design's recurrent, branching and concurrent cognitive interactions and its whole-system ownership boundaries.

The main-branch docs/JARVIS_PHASE_2_COMPLETION.md describes an older perception-pipeline phase and says the next phase is the World Model. That is a legacy subsystem phase label, not the new whole-project Phase 2 requested in this work. Reusing the label without qualification would create a false status claim.

docs/ARCHITECTURE.md is a short earlier cognitive-flow summary. core/cpp/tests/phase4_notes.md is test-history documentation, not architecture authority.

PRs #166–#170 contain project governance, language ownership, polyglot engineering, MCU behavioral-reference and older Layer 0–19 planning proposals. They are useful historical inputs, but they remain open/draft proposals and must not become competing authorities alongside the accepted PR #171–#174 chain.

**Preservation decision:** do not delete these artifacts in Phase 1. In a later documentation-maintenance pass, move or label superseded planning documents under an explicit historical/archive area, add supersession notices and link to the current authority. Preserve commit history and original evidence.

---

## 12. Reuse, adaptation and retirement register

| Existing area | Verdict | Why |
|---|---|---|
| Event model and persistent Brain journal | **Reuse, harden** | Valuable continuity/replay foundation; integrity and trust gaps remain |
| Memory tiers and structured recall | **Reuse, adapt** | Useful episodic substrate; retrieval is overlap-based, not semantic |
| Perception provider contract | **Reuse** | Extensible provider boundary and failure isolation are sound |
| Raw modality/source mapping | **Adapt** | Exact source strings are brittle and should not define cognition |
| Representation/evidence spans | **Reuse, extend** | Good evidence-bearing representation foundation |
| World model | **Adapt** | Dispute retention exists; evidence adjudication is incomplete on main |
| Knowledge/provenance | **Adapt from PR #148** | Source reliability alone is insufficient; provenance independence and conflict support matter |
| Causal model | **Reuse, correct and extend** | Useful causal substrate; transition semantics and generality require validation |
| Current reasoning engine | **Retain as narrow specialist; expand** | Forward causal chaining is not BM-12 general reasoning |
| Attention and attention state | **Reuse, adapt** | Valuable signal/resource mechanisms; policy learning and persistence need work |
| Decision engine | **Reuse formula as provisional baseline only** | Weighted scoring and fixed thresholds are not final learned judgment |
| Threat model | **Retain as provisional safety control** | Deterministic risk policy; calibrate and keep separate from general cognition |
| Goal model | **Reuse state primitives; adapt formation/arbitration** | Goal lifecycle exists; autonomous experience-acquired goals not established |
| Planner | **Reuse and extend** | Useful action-sequence planning substrate; limited strategy/motivation integration on main |
| Authorization/execution | **Reuse** | Correct separation of cognition, permission and execution |
| Brain-owned action/consequence feedback | **Selective donor from PR #97** | Major missing main integration; validate persistence and failure semantics |
| Affective state and appraisal | **Selective donor from PR #97** | Continuous, outcome-sensitive design; fixed dynamics require validation |
| Developmental strategy learning | **Selective donor from PR #97/#151** | Demonstrated context learning and bounded compositional transfer; heuristic/linear limits |
| Evolution experiment machinery | **Reuse selectively** | Strong candidate-evaluation and safety substrate; compensation/replay boundaries remain |
| Self-model/reflection/resilience | **Reuse and expand** | Health and reflection primitives exist; metacognitive scope is incomplete |
| Capability registry/evaluator/execution | **Reuse** | Useful capability lifecycle boundaries |
| Rust CognitiveState | **Prototype only** | Risks a second cognitive authority if treated as a Brain |
| TypeScript interfaces | **Reuse as contracts** | Useful transport/operator types; no concrete integrated runtime |
| Engineering-agent subsystem | **Keep separate** | Useful builder/worker coordination; not the JARVIS Brain |
| Legacy 0–19 blueprint and old phase notes | **Archive/mark superseded, do not delete** | Historical context, not current architecture authority |

No component is recommended for immediate deletion. “Retire candidate” should be reserved for a later evidence-backed decision where a component is demonstrably redundant, incompatible or unused and its history has been preserved.

---

## 13. Recommended Phase 2 entry

Phase 1 has delivered the repository inventory, identified the strongest donor mechanisms, distinguished main from candidate code, classified fixed policy versus infrastructure, and reconciled the existing Gate A evidence. There is no reason to restart.

**I recommend entering Phase 2 today, but as an architecture-to-capability integration phase—not as an immediate wholesale code merge.**

The first Phase 2 deliverable should be one traceable integration map from accepted PR #174 BM-01 through BM-12 to:

1. the authoritative state owner and current source/interface;
2. the best donor implementation and exact commit/blob;
3. the actual event, memory, belief, prediction and consequence dataflow;
4. the tests that demonstrate the capability, including their limits;
5. the known fixed assumptions and required generalization tests;
6. the cross-mechanism dependencies and failure/replay boundaries;
7. the disposition: reuse, adapt, redesign or no current implementation.

The integration map must assess the Brain as one interacting system, not as twelve disconnected module tickets. It must also preserve the whole-system boundary established in PR #171: Brain-first implementation does not mean JARVIS is only a Brain.

### What can start immediately

- Build the BM-01–BM-12 capability-to-source/test map from the accepted PR #174 baseline.
- Reconcile candidate donor source and API differences at the exact refs already identified.
- Design the whole-loop integration sequence and acceptance experiments.
- Define how the C++ Brain remains authoritative while Rust/TypeScript/engineering agents remain bounded subsystems.
- Specify held-out, multi-seed, changing-environment and persistence/replay acceptance tests.

### What must remain blocked

- Wholesale adoption or merge of PR #156.
- Runtime source changes or selective ports without separate implementation authorization.
- Treating PR #176 as merged or its corrections as present in PR #156.
- Claiming Gate A cleared before the residual failure boundary and independent re-check are completed.
- Treating passing synthetic tests as proof of general intelligence or broad real-world learning.

Phase 2 should proceed from the accepted architecture/specification and use the donor findings above. Formal Gate A closure can continue as a parallel prerequisite to implementation.

---

## 14. Final Phase 1 disposition

**Phase 1 — COMPLETE as a whole-repository inventory and reuse/conflict investigation.**

The repository contains meaningful mechanisms worth preserving and integrating. The highest-value source donor is the PR #97 learning/affective line, strengthened by the PR #148 knowledge/provenance work, PR #151 compositional learning, PR #150 evolution replay safeguards and the PR #155/#156 integration line. The current main branch is a narrower baseline and should not be mistaken for the full available project state.

**Formal Gate A — NOT CLEARED.** The technical baseline recommendation remains accepted PR #174 as the integration starting point and PR #156 as a selective source donor only. D1/D2 fixes exist on PR #176 and have passing CI, but they are not merged into the donor. One deeper controller compensation boundary and a genuine independent re-check remain open.

**Implementation authorization — NOT GRANTED by this report.** No runtime source was changed and no baseline was selected.

The correct next step is Phase 2 capability-to-source integration mapping against the accepted specification, while the remaining Gate A closure items are resolved. Do not restart, do not throw away the existing mechanisms, and do not promote a donor branch into the authoritative Brain merely because it is larger or has more green tests.

---

## 15. Evidence index

### Main repository snapshot and core source

- Main tree: https://github.com/methaneex-oss/MethaneX/tree/1273ddbcd0087d189e01388ded2d362fb1e058d2
- Main README: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/README.md
- Core CMake source list: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/CMakeLists.txt
- Core CTest registration: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/tests/CMakeLists.txt
- Cognitive cycle: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/cognitive_cycle.cpp
- Memory: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/memory.cpp
- World model: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/world_model.cpp
- Knowledge: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/knowledge.cpp
- Reasoning: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/reasoning.cpp
- Decision: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/decision.cpp
- Threat: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/threat.cpp
- Action authorization: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/action_authorization.cpp
- Action execution: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/core/cpp/src/action_execution.cpp

### Candidate learning and integration evidence

- PR #96 action-feedback proposal: https://github.com/methaneex-oss/MethaneX/pull/96
- PR #97 cognitive/affective development: https://github.com/methaneex-oss/MethaneX/pull/97
- PR #99 learning-mechanisms workflow: https://github.com/methaneex-oss/MethaneX/pull/99
- PR #148 contradiction/provenance work: https://github.com/methaneex-oss/MethaneX/pull/148
- PR #150 evolution replay work: https://github.com/methaneex-oss/MethaneX/pull/150
- PR #151 compositional feature learning: https://github.com/methaneex-oss/MethaneX/pull/151
- PR #155 integration: https://github.com/methaneex-oss/MethaneX/pull/155
- PR #156 integrated donor: https://github.com/methaneex-oss/MethaneX/pull/156
- PR #151 DLT-004 test source at exact head: https://github.com/methaneex-oss/MethaneX/blob/8c8889fc225fbefbda27989e06e656aad9bbfd33/core/cpp/tests/dlt_004_feature_composition.cpp
- PR #151 developmental learning implementation at exact head: https://github.com/methaneex-oss/MethaneX/blob/8c8889fc225fbefbda27989e06e656aad9bbfd33/core/cpp/src/developmental_learning.cpp
- PR #99 successful 10-minute learning probe run: https://github.com/methaneex-oss/MethaneX/actions/runs/40419118694

### Accepted architecture and Gate A evidence

- PR #171 whole-system architecture foundation: https://github.com/methaneex-oss/MethaneX/pull/171
- PR #172 accepted capability investigation: https://github.com/methaneex-oss/MethaneX/pull/172
- PR #173 Brain Foundation Architecture proposal (historical “accepted” label superseded; exact-revision acceptance remains UNVERIFIED/PROPOSED; see §26.2): https://github.com/methaneex-oss/MethaneX/pull/173
- PR #174 accepted Brain Mechanism Specification planning baseline only (exact accepted HEAD and scope recorded in PR #174 discussion): https://github.com/methaneex-oss/MethaneX/pull/174
- PR #175 implementation roadmap and Gate A evidence: https://github.com/methaneex-oss/MethaneX/pull/175
- PR #176 donor corrections: https://github.com/methaneex-oss/MethaneX/pull/176
- Gate A Report 13 — final baseline recommendation: https://github.com/methaneex-oss/MethaneX/blob/874c732973b6ab303d65a503f5a215b0af8e1153/docs/architecture/plans/reviews/13_GATE_A_FINAL_BASELINE_RECOMMENDATION_2026-11-04.md
- Gate A Report 14 — independent technical review: https://github.com/methaneex-oss/MethaneX/blob/874c732973b6ab303d65a503f5a215b0af8e1153/docs/architecture/plans/reviews/14_GATE_A_INDEPENDENT_TECHNICAL_REVIEW_2026-11-04.md
- Gate A Report 16 — closure evidence update: https://github.com/methaneex-oss/MethaneX/blob/874c732973b6ab303d65a503f5a215b0af8e1153/docs/architecture/plans/reviews/16_GATE_A_CLOSURE_EVIDENCE_UPDATE_2026-11-04.md
- PR #176 Native Brain Build: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525486
- PR #176 Brain ThreadSanitizer: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525492
- PR #176 Brain CI: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525499
- PR #176 JARVIS Brain Tests: https://github.com/methaneex-oss/MethaneX/actions/runs/41808525557

### Preservation inventory

- Existing documentation/artifact inventory branch: https://github.com/methaneex-oss/MethaneX/tree/ebbda074957e0f9fb0d0f04dd9b03fe58b270a0a
- Legacy master blueprint: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md
- Legacy Phase 2 completion note: https://github.com/methaneex-oss/MethaneX/blob/1273ddbcd0087d189e01388ded2d362fb1e058d2/docs/JARVIS_PHASE_2_COMPLETION.md
- Priority-One trust-boundary contract: https://github.com/methaneex-oss/MethaneX/blob/cfbcbdd29839f062851d3ca7da63ab2ae3a8f4f1/docs/PRIORITY_ONE_TRUST_BOUNDARY_CONTRACT.md

## 16. Post-publication review corrections and reproducibility records

The following dated addenda refine the evidence package without changing the original audited source baseline or reopening the completed technical inventory:

- [Phase 1 tracked-file inventory](../inventory/PHASE_1_TRACKED_FILE_INVENTORY_2026-11-05.md) — all 200 tracked blob paths, sizes and blob SHAs at the exact audited tree, with reproduction procedure.
- [PR #97 donor capability traceability](../inventory/PHASE_1_PR97_DONOR_CAPABILITY_TRACEABILITY_2026-11-05.md) — selected high-impact donor paths traced to exact source/test blobs, dataflow, consumers, persistence and limitations.
- [Phase 1 review corrections and scope reconciliation](PHASE_1_REVIEW_CORRECTIONS_AND_SCOPE_RECONCILIATION_2026-11-05.md) — reconciles PR #174's formal acceptance chronology with subsequent F-02/F-03 findings, records F2–F5 dispositions, and captures governance refinements G1–G3.

**Source-link correction:** all source links in this report that previously used mutable `blob/main/` references are pinned to the audited main commit `1273ddbcd0087d189e01388ded2d362fb1e058d2`.

**Completion boundary:** the technical repository inventory and reuse/conflict assessment is complete within the static-investigation scope in Sections 1–2. Historical branch-to-PR mapping, duplicated-document reconciliation, README/cross-link verification and archive curation remain open preservation work; they are not claimed complete and do not require restarting the technical investigation.

**End of Phase 1 report (with dated review addenda).**