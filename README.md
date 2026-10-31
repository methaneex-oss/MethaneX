# JARVIS

> A continuously evolving, multimodal cognitive system.

JARVIS is being engineered as a persistent, adaptive cognitive system—not a chatbot, a wrapper around an external model, or a collection of disconnected agents. The Brain is the current construction target.

## Governing principle

**ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

## Engineering principles

- **Cognition over conversation** — perception, memory, world modelling, reasoning, planning, decision, action and reflection cooperate as one system.
- **Continuity over storage** — memory preserves experience, context, evidence and state continuity; it is not merely a database of messages.
- **Learning over hardcoding** — behavior intended to be learned must change through evidence and experience, not scenario-specific fixed mappings.
- **One cognitive authority** — subsystems and workers may cooperate, but canonical cognitive state has explicit ownership.
- **Internal cognition** — core reasoning, memory, prediction, decision and learning mechanisms are built and owned within this project; hosted AI APIs and external cognitive engines are not core dependencies.
- **Evidence before complexity** — mechanisms, languages, frameworks and dependencies require a concrete responsibility and measurable justification.
- **Resilience by design** — faults should be detected, isolated and recovered without corrupting continuity.
- **Security as a native concern** — trust boundaries, authorization, integrity and controlled recovery are foundational.

## Repository layout

```text
MethaneX/
├── core/                 # Native cognitive foundation
│   └── cpp/
├── runtime/              # Bounded infrastructure services
│   └── rust/
├── interfaces/           # Monitoring and authorized interface contracts
│   └── typescript/
├── docs/                 # Architecture and engineering documentation
└── tests/                # Verification and regression tests
```

## Brain

The Brain is being developed as one layered cognitive system. Its responsibilities include perception and representation, memory and continuity, beliefs and evidence, world and self-modelling, attention, prediction, valuation, reasoning, goals, planning, decision, authorized action, outcome evaluation, learning, metacognition, resilience and governed self-improvement.

These are interacting mechanisms, not independent chatbot features. Their presence in the repository does not prove that they are integrated or behaviorally effective.

## Language strategy

The current proposed Brain allocation uses C++20 for authoritative cognition and orchestration; Python/PyTorch for bounded trainable mechanisms and evaluation; Rust only for justified infrastructure or isolation; TypeScript for monitoring and authorized interface contracts; and CUDA/Triton only when measured acceleration benefits justify them. No language is introduced merely to increase the language count. See the [Brain Layer-to-Language Ownership Map](docs/BRAIN_LAYER_LANGUAGE_OWNERSHIP_MAP.md).

## Brain identity and behavioral target

The [Brain Identity and Behavioral Specification](docs/JARVIS_BRAIN_IDENTITY_AND_BEHAVIORAL_SPEC.md) defines what JARVIS is intended to be, the MCU behavior used as a reference, the target Brain capabilities, and the non-negotiable project rules.

## Brain engineering governance

The [Brain Polyglot Engineering Governance](docs/BRAIN_POLYGLOT_ENGINEERING_GOVERNANCE.md) defines language ownership, implementation standards, cross-language contracts, state integrity, security, persistence, testing, dependencies, performance and approval gates.

## Project governance

The command structure, role boundaries, decision authority, architecture change control, independent testing/review requirements, and handoff rules are defined in [JARVIS Project Governance](docs/JARVIS_PROJECT_GOVERNANCE.md).

## Development status

JARVIS is under foundational development. The present work is focused on the Brain. Future embodiments—such as a house, suit, phone, satellite, or other host—are not current implementation targets. The Brain must remain independent of any one such environment.

## Philosophy

The objective is to engineer the closest practical software architecture to the behavioral idea of MCU JARVIS: persistent, context-aware, capable of reasoning across domains, able to use authorized capabilities, resilient to faults, and able to improve through experience. Cinematic behavior is a reference for requirements, not proof of a known technical implementation or a claim of human-equivalent intelligence.
