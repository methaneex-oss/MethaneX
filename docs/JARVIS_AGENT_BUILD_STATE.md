# JARVIS — Agent Build Handoff / Current Project State

**Purpose:** This document is the handoff contract for the AI coding/building agents working on JARVIS. Read this before modifying the repository. It is intentionally explicit so agents do not need to reconstruct project intent from scattered conversations.

**Repository:** `methaneex-oss/MethaneX`

**Project:** JARVIS

**Document role:** engineering state + architecture constraints + current work + rules + remaining evolution objectives.

**Authority:** The repository's actual code, tests, CI, and persisted architecture are authoritative when they conflict with this document. This document records intent and known state; it must be corrected when implementation changes.

---

## 1. What JARVIS actually is

JARVIS is being engineered as a persistent, adaptive, autonomous **software brain**.

It is not a chatbot, not a single LLM prompt, not an API wrapper, and not a collection of disconnected AI features.

The README describes the project as a continuously evolving, multimodal software intelligence platform and explicitly emphasizes cognition over conversation, continuity over simple storage, learning over hardcoding, evolution over stagnation, resilience, model-agnostic intelligence, polyglot engineering, and security as a native concern.

The central objective is to create mechanisms through which useful intelligence can emerge from state, evidence, models, capabilities, experiments, outcomes, and feedback.

### Absolute rule

**NO HARDCODED INTELLIGENCE.**

Allowed:
- schemas
- interfaces
- safety constraints
- deterministic mathematics
- validation
- resource limits
- security boundaries
- algorithms
- persistence formats
- protocol/state-machine mechanics
- explicit engineering invariants

Forbidden:
- phrase -> tool mappings
- phrase -> response mappings
- domain-specific `if/else` pretending to be cognition
- fake `understand()`, `think()`, `learn()`, or `evolve()` methods that return scripted results
- hard-coded evolution winners
- fixed knowledge presented as intelligence
- arbitrary self-modification without evidence and safety controls

If a new rule encodes what JARVIS should "think" rather than providing a mechanism by which JARVIS can reason from state/evidence, stop and redesign it.

---

## 2. Language and architecture

JARVIS is deliberately polyglot. Do not force everything into Python or everything into C++.

Current intended direction:

- cognitive core / brain state / memory / world model: C++
- reasoning: C++ + Python
- learning: Python + C++
- evolution: C++ + Python
- self-healing/security: Rust + C++
- communication: C++ / Rust
- data/knowledge: Python + C++
- voice/vision: Python + C++
- build: CMake
- native standard: C++20
- static core library
- CTest
- sanitizer testing, including ThreadSanitizer

The language follows subsystem requirements. The architecture is not defined by a particular language or AI provider.

---

## 3. Long-term cognitive loop

The intended cognitive flow is:

Observation
-> Perception
-> Representation
-> Attention
-> Memory retrieval
-> World-model update
-> Belief update
-> Reasoning
-> Goal evaluation
-> Planning
-> Decision
-> Authorization
-> Action
-> Outcome observation
-> Prediction error
-> Learning
-> Reflection
-> Adaptation
-> Future behavior improvement

The long-term target is a continuous operating loop, not a pile of independent APIs.

Every major subsystem should eventually have a real information path into and out of the cognitive runtime.

---

## 4. Cognitive foundation already built

The repository has substantial cognitive infrastructure. Preserve it. Inspect actual implementation before creating anything new.

Existing concepts include:

- cognitive state
- events
- persistence
- perception
- representation
- attention
- memory
- knowledge
- world model
- self model
- associations
- causality
- prediction
- simulation / counterfactual infrastructure
- goals
- intent
- strategy
- planning
- decision
- action assessment
- authorization
- action execution
- outcome feedback
- learning
- adaptation
- reflection
- self-testing
- self-healing
- cognitive runtime
- cognitive workspace
- event-driven cognition
- capability registry
- capability evaluation
- evolution

Do not declare a subsystem complete because a header or class exists. Trace actual data flow and tests.

---

## 5. Important cognitive architecture rules

### Cognitive triggers

The event/trigger layer should consume normalized cognitive signals such as novelty, urgency, and uncertainty. It must not interpret arbitrary user phrases or vendor-specific event text as intelligence.

### Capability registry

Capabilities are represented using metadata rather than hard-coded command mappings.

Relevant metadata includes concepts such as:

- identity
- name
- description
- input/output schema
- permissions
- cost
- risk
- reliability
- availability
- reversibility

Capability selection should be driven by task/context/constraints/evaluation, not by hard-coded phrase matching.

### External providers

GitHub, AWS, Neon, Vercel, Railway, Render, Datadog, Hugging Face, Linear, Notion, Make, or any future provider is a **capability provider**, never JARVIS itself.

The brain must remain provider-independent.

An LLM is a capability/resource available to cognition. It is not the definition of JARVIS.

---

## 6. The current engineering/building-agent layer

This layer is **for making/building JARVIS**, not the JARVIS cognitive brain itself.

Its purpose is to give the brain eventually usable engineering capabilities and to provide multiple coding/building agents that can work under controlled orchestration.

The agent layer must remain subordinate to JARVIS's cognitive architecture.

### Current agent architecture direction

The engineering layer contains concepts around:

- agent descriptors
- capabilities
- permissions
- risk
- availability
- reliability
- costs
- input/output artifacts
- engineering tasks
- execution boundaries
- authorization
- agent discovery
- capability/risk-aware ranking
- dispatch
- sequential orchestration
- shared task/workspace context
- agent results/evidence
- communication/message exchange
- model-provider boundaries

The existing `EngineeringCoordinator` exposes discovery/ranking/dispatch/sequence operations. Do not duplicate it with another coordinator.

### Agent synchronization principle

Agents cannot genuinely work in sync if they cannot exchange information.

Therefore the target is:

Agent A
-> message/request/result
-> shared run context/message bus
-> Agent B
-> feedback/review
-> Agent C
-> verification
-> coordinator
-> evidence/result

Shared artifacts and structured messages should carry actual state. Avoid using conversational prose as the system of record.

### Agent communication

The communication mechanism must support at minimum:

- sender identity
- recipient identity
- run/task identity
- message type
- structured payload/context
- correlation where needed
- result/evidence exchange
- failure propagation
- bounded retries
- auditability

Provider-specific model APIs must sit behind provider-neutral interfaces.

### Direct human -> agent communication

The user also wants a future direct communication path where the user and ChatGPT can communicate with the building agents rather than only communicating through the coordinator.

This must be designed as an **explicit supervised interface**, not an uncontrolled backdoor into execution.

Desired shape:

Human / ChatGPT
        |
        v
Agent communication interface
        |
        v
Agent / coordinator
        |
        v
Workspace + artifacts + execution boundary
        |
        v
Evidence / result / response

A direct message must not automatically grant execution permissions. Authorization remains separate from communication.

---

## 7. Why the building-agent layer exists

The user explicitly wants multiple builders/agents so that JARVIS development can proceed faster through parallel or coordinated work.

The objective is not to create 100 agents.

The objective is to create a small number of capable, synchronized builders that can:

1. understand the current JARVIS state;
2. receive a bounded engineering task;
3. inspect the repository;
4. modify an isolated workspace/branch where appropriate;
5. build and test;
6. communicate findings to other agents;
7. review previous agent output;
8. produce evidence;
9. hand work forward;
10. stop or escalate when authorization/safety boundaries require it.

Agent count is not a progress metric.

---

## 8. External capability providers

Potential providers and their intended roles:

### GitHub

Primary engineering capability.

Potential operations:
- inspect repository
- create branch
- modify code
- commit
- run/inspect CI
- inspect PRs
- compare candidate against baseline
- review evidence
- controlled rollback

GitHub access must remain bounded by authorization. JARVIS must not freely modify production merely because a model believes a change is good.

### Hugging Face

Model ecosystem / candidate model capability.

Potential uses:
- discover candidate models
- evaluate models
- compare models
- provide specialized ML capabilities

Hugging Face is not JARVIS's brain.

### Datadog

Observability/evidence capability.

Potential uses:
- metrics
- logs
- traces
- post-adoption regression evidence

### Neon

Durable data/persistence capability where appropriate.

Potential uses:
- durable experiment records
- evolution data
- structured state that belongs in external storage

### AWS / Railway / Render / Vercel

Infrastructure/deployment capabilities.

Potential uses:
- controlled candidate environments
- builds
- deployment
- canary infrastructure
- resource measurement

### Linear / Notion

Engineering context and knowledge capabilities where useful.

### Make

External workflow orchestration capability where useful.

Do not integrate a provider just to claim that it is integrated. Use it only when it provides real evidence or execution value.

---

## 9. Current evolution objective

Evolution is the next major cognitive capability and must be completed using the existing infrastructure rather than duplicated classes.

Target lifecycle:

Limitation / Opportunity
-> Evidence
-> Hypothesis
-> Candidate generation
-> Candidate validation
-> Historical ranking
-> Scheduling
-> Baseline measurement
-> Isolated candidate trials
-> Repeated trials
-> Statistical evaluation
-> Safety gate
-> Adoption decision
-> Controlled adoption
-> Canary
-> Live monitoring
-> Retain OR rollback
-> Evolution history
-> Future learning

Every meaningful evolution must have provenance.

At minimum, record:

- why it was proposed
- motivating evidence
- hypothesis
- candidate identity
- baseline
- candidate configuration
- trials
- measurements
- statistical evaluation
- safety decision
- adoption decision
- canary observations
- rollback information
- final outcome

---

## 10. Existing evolution foundation

The repository already contains substantial evolution infrastructure. Inspect it before modifying it.

Known components include:

- `EvolutionModel`
- `EvolutionProposal`
- `EvolutionPolicy`
- `EvolutionEvaluation`
- evolution experiments
- experiment outcomes
- evolution sandbox abstraction
- process-isolation infrastructure
- evolution experiment runner
- evolution experiment coordinator
- trial statistics
- evolution scheduler
- evolution history
- evolution learning
- evolution strategy
- evolution safety
- evolution adoption
- evolution adoption journal
- evolution controller
- evolution canary
- evolution monitor
- evolution opportunity detection
- candidate validation

`core/cpp/include/jarvis/core/evolution.hpp` currently contains strategy parameters, proposals, policy, evaluation and the `EvolutionModel` interface. The existing model uses observations, proposal generation, evaluation, adoption, rollback and baseline restoration.

The existing implementation is a foundation, not the final autonomous-evolution system.

Do not call the evolution subsystem "Tony-level" merely because these classes exist.

---

## 11. Evolution quality requirements

The current trial/statistical mechanisms must eventually be strengthened.

Move toward:

- repeated trials
- paired trials where scientifically appropriate
- baseline distributions
- candidate distributions
- sample-count requirements
- variance
- effect size
- confidence intervals
- minimum practical improvement
- holdout validation
- regression detection
- reproducibility
- conservative adoption thresholds

A heuristic such as `1 / (1 + standard_error)` must never be described as mathematically rigorous statistical confidence.

---

## 12. Evolution safety requirements

Higher evolution levels require stronger isolation.

The system must not implement:

- random self-modification
- arbitrary source rewriting
- uncontrolled production mutation
- direct production deployment from an LLM
- fake sandboxing
- fake confidence
- hard-coded winners
- automatic adoption without evidence
- automatic adoption without safety validation
- irreversible changes without rollback

Requested isolation must fail closed when it cannot actually be enforced.

Relevant isolation concerns include:

- process isolation
- filesystem isolation
- network isolation
- privilege restrictions
- no-new-privileges
- CPU limits
- memory limits
- file-size/output limits
- timeouts
- controlled dependencies

Do not describe a sandbox as production-grade without verifying its actual guarantees.

---

## 13. Evolution levels

Build toward these levels progressively:

1. Parameter evolution
2. Policy evolution
3. Planning evolution
4. Capability composition
5. Model evolution
6. Architecture evolution
7. Implementation evolution
8. Infrastructure evolution

Higher levels require stronger evidence, isolation, verification, authorization and rollback.

---

## 14. The evolution feedback loop

Evolution must eventually participate in the normal cognitive loop:

Cognitive evidence
-> limitation/opportunity
-> hypothesis
-> candidate
-> experiment
-> measured result
-> safety evaluation
-> adoption/canary
-> outcome
-> evolution history
-> evolution learning
-> strategy/model improvement
-> future planning/decision
-> new outcome

The loop must eventually be triggered by actual normalized evidence, not by a developer manually invoking evolution every time.

Useful evidence sources include:

- repeated prediction errors
- recurring action failures
- degraded capability performance
- high uncertainty
- inefficient strategies
- repeated self-test failures
- regression observations

Do not encode domain-specific meanings as hard-coded phrase rules.

---

## 15. Integration architecture

The intended long-term boundary is:

JARVIS BRAIN
        |
        v
Capability discovery
        |
        v
Capability evaluation
        |
        v
Authorization
        |
        v
Execution boundary
        |
   +----+----+----+----+
   |    |    |    |    |
 GitHub AWS Neon Datadog HF ...
   |
   v
Normalized result/evidence
        |
        v
Outcome / learning / cognition

The brain should never become a pile of vendor adapters.

---

## 16. What the building agents should do now

The building agents are being added to accelerate JARVIS development. They are not being asked to redesign JARVIS.

Current mission for the agents:

### First priority

Finish and strengthen the **Autonomous Evolution Loop** using the existing evolution architecture.

The desired complete path is:

Opportunity
-> Hypothesis
-> Candidate generation
-> Validation
-> Ranking
-> Scheduling
-> Baseline
-> Isolated trials
-> Statistical evaluation
-> Safety
-> Adoption
-> Canary
-> Monitoring
-> Retain/Rollback
-> History
-> Learning

### Second priority

Strengthen agent orchestration only where it is necessary to make the builders genuinely useful.

Do not spend excessive time polishing the agent layer while the core JARVIS work is waiting.

### Third priority

Return focus to the main JARVIS cognitive architecture once the engineering-agent layer is sufficient for practical coordinated work.

---

## 17. What agents must NOT do

Do not:

- restart the project
- replace the cognitive architecture
- create duplicate evolution classes
- create duplicate coordinators
- rewrite working subsystems without evidence
- introduce hard-coded intelligence
- convert JARVIS into an LLM wrapper
- add integrations merely for marketing/checkbox purposes
- claim a capability is complete because code compiles
- weaken tests to obtain green CI
- silently change public contracts without architectural justification
- merge unverified work
- bypass authorization or safety boundaries
- deploy self-modifications directly to production

---

## 18. Engineering workflow

For every meaningful task:

1. Inspect first.
2. Identify existing implementation.
3. Trace actual data flow.
4. Reuse existing infrastructure.
5. Design the smallest change that closes the capability gap.
6. Implement.
7. Integrate it into real information flow.
8. Add/update tests.
9. Build.
10. Run relevant CTest tests.
11. Run failure-path tests.
12. Run sanitizers where relevant.
13. Run ThreadSanitizer where relevant.
14. Inspect exact CI status at the exact commit.
15. Fix failures rather than hiding them.
16. Verify branch/commit state.
17. Merge only after verification.
18. Verify the merge.
19. Continue to the next meaningful capability.

Do not stop after every small file change. Work in meaningful batches.

---

## 19. Testing definition of complete

A capability is complete only when applicable portions of the following are real:

- data enters
- processing occurs
- state changes correctly
- output affects downstream cognition/execution
- outcomes are observed
- learning/feedback occurs
- persistence works
- restart/reconstruction works
- failures are handled
- authorization is enforced
- concurrency is safe where relevant
- tests verify actual behavior
- CI verifies the exact commit

Number of classes/files is irrelevant.

---

## 20. Git discipline

Repository: `methaneex-oss/MethaneX`

Work from current `main`.

Use focused branches.

Do not overwrite unrelated work.

Before merge:

- inspect exact branch
- inspect exact head SHA
- inspect changed files
- run relevant tests
- inspect CI for exact head
- resolve failures
- merge only when verified
- inspect post-merge main

Never report a green build without actual evidence.

---

## 21. Human review boundary

The user wants the building agents to finish the evolution implementation, after which the user and ChatGPT will review it before committing/merging the final result.

Therefore agents should:

- implement and test
- document evidence
- expose assumptions and unresolved risks
- stop short of treating an unreviewed high-risk evolution capability as automatically approved

The final human/ChatGPT review should inspect:

- correctness
- real data flow
- statistical validity
- safety
- isolation semantics
- rollback behavior
- persistence/restart behavior
- security
- CI
- scope creep

---

## 22. Human <-> agent communication goal

The user wants to be able to talk directly with the building agents, with ChatGPT acting as an additional supervisory/engineering participant.

Desired conceptual topology:

                    HUMAN
                      |
              +-------+-------+
              |               |
          ChatGPT        Direct Agent UI
              |               |
              +-------+-------+
                      |
               Agent Gateway
                      |
             Authorization Layer
                      |
              Agent Message Bus
          /       /      \       \
      Builder  Reviewer  Tester  Researcher
          \       \      /       /
              Shared Run Context
                      |
                 Workspace
                      |
             Execution Boundary
                      |
                 Evidence

Communication is not authorization.

A human can ask an agent a question without granting it permission to mutate code, deploy, merge, or modify production.

---

## 23. Provider/model policy

Agents may use different models/providers when technically useful.

Potential model sources include OpenAI-compatible providers and Hugging Face models, but provider selection belongs behind a model-provider interface.

Do not write intelligence around one model vendor.

Do not assume the strongest model is always the correct model.

Model selection itself can eventually become an evidence-driven capability/evolution problem.

---

## 24. Important known architectural principle

JARVIS should not be defined by the agents building it.

The agents are an engineering capability layer used to accelerate development of the brain.

The long-term JARVIS brain remains responsible for:

- state
- memory
- world model
- reasoning
- goals
- planning
- decisions
- actions
- outcomes
- learning
- reflection
- adaptation
- evolution

The engineering agents are tools/capabilities that can operate on engineering tasks under authorization and isolation.

---

## 25. Current practical checkpoint

At the current handoff, the project has moved beyond the question "can we create building agents?".

The engineering layer has a coordinator concept, capability-aware discovery/ranking, execution/authorization boundaries, shared task context, and agent communication infrastructure.

The immediate objective is no longer to keep building infrastructure indefinitely.

**Use the agents. Finish the remaining Autonomous Evolution Loop work. Then return focus to the main JARVIS brain.**

If an engineering-agent problem becomes a blocker, fix the smallest necessary part and continue. Do not turn the agent layer into a permanent project inside the project.

---

## 26. Decision rule for agents

When uncertain whether to add a new abstraction, ask:

> Does this enable a real information flow or safety boundary that JARVIS currently lacks?

If no, do not add it.

When uncertain whether something is intelligence or infrastructure, ask:

> Is this encoding a conclusion JARVIS should derive, or providing a mechanism from which JARVIS can derive conclusions?

If it encodes the conclusion, it is probably hard-coded intelligence and should be rejected.

---

## 27. Final mission statement

Build JARVIS as a real software brain.

Build the engineering agents as controlled capabilities that help create and improve that brain.

Let agents communicate through structured, auditable mechanisms.

Let cognition select capabilities through metadata, evidence, constraints and authorization rather than phrase mappings.

Let evolution improve the system through hypotheses, experiments, evidence, safety gates, canaries, rollback and persistent learning.

Do not fake intelligence.

Do not confuse infrastructure with cognition.

Do not spend forever perfecting the scaffolding.

Build, verify, integrate, learn, and continue.
