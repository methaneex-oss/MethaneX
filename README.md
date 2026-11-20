# JARVIS

> A continuously evolving, multimodal software intelligence platform.

JARVIS is being engineered as a **software-first cognitive system** rather than a chatbot, a single model wrapper, or a single-language application. The architecture uses the language and runtime best suited to each subsystem.

## Engineering principles

- **Cognition over conversation** — perception, memory, world modelling, reasoning, planning, action and reflection are separate capabilities that cooperate.
- **Continuity over storage** — memory represents experience and state continuity, not merely a database of messages.
- **Learning over hardcoding** — behaviour should improve from evidence, outcomes and experience instead of depending on large collections of fixed `if/else` rules.
- **Evolution over stagnation** — capabilities, strategies and internal models are designed to improve as evidence accumulates.
- **Resilience by design** — faults should be detected, isolated and recovered without assuming that every subsystem is always available.
- **Model-agnostic intelligence** — external models and knowledge sources may contribute capabilities without becoming JARVIS itself.
- **Polyglot by engineering necessity** — C++, Rust, Python, TypeScript and other technologies may be used where each provides the strongest implementation characteristics.
- **Security as a native concern** — defensive monitoring, isolation, integrity and controlled recovery belong in the platform rather than being an afterthought.

## Repository layout

```text
MethaneX/
├── core/                 # Native cognitive and systems core
│   └── cpp/
├── runtime/              # High-performance runtime components
│   └── rust/
├── interfaces/           # Integration and external contracts
│   └── typescript/
├── docs/                 # Architecture and engineering documentation
└── tests/                # Verification and regression tests
```

## Documentation and planning navigation

Start at the [JARVIS Documentation Portal](docs/README.md). It provides role-specific reading routes for new readers, Builders, independent reviewers, testers, researchers and documentation maintainers. The [Planning Documentation Index](docs/architecture/00_JARVIS_PLANNING_DOCUMENTATION_INDEX_2026-11-07.md) remains the canonical planning-artifact catalog and authority/status map. Read the portal and index before treating an individual planning report as authoritative.

## Brain

The Brain's complete future capability architecture is still being planned. The following items are broad project concepts, not an exhaustive or accepted capability inventory, final mechanism decomposition, or implementation sequence:

- persistent continuity memory
- working context and attention
- belief and evidence management
- world modelling and relationships
- causal reasoning and simulation
- prediction and outcome learning
- adaptive decision making
- planning
- reflection / metacognition
- knowledge assimilation
- threat assessment and defensive posture
- resilience and recovery
- capability self-modeling
- evolution and performance adaptation

These are **components of one cognitive system**, not independent chatbot features.

## Language strategy

There is deliberately no requirement that the entire project be written in one language. Native systems work may use C++, safety-critical/high-concurrency components may use Rust, integration layers may use TypeScript, and Python may be introduced where it provides a genuine technical advantage such as scientific/ML tooling. The architecture decides the language; the language does not define the architecture.

## Development status

JARVIS is an existing software project with implemented runtime foundations and substantial open architecture/planning work. The immediate repository task is to complete the initial documentation foundation before beginning whole-Brain Stage A. Existing source is preserved as engineering evidence; this status does not claim that the whole-Brain architecture or integrated Brain capability is complete.

The current BM-01–BM-12 source-integration investigation is maintained in the [Phase 2 — Whole-Brain Capability-to-Source Integration Map](docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md). It is a useful partial map, not proof that the complete future Brain has been architecturally defined. The corrected planning scope is in [Whole-Brain Planning Scope and Builder Correction](docs/architecture/reports/WHOLE_BRAIN_PLANNING_SCOPE_AND_BUILDER_CORRECTION_2026-11-07.md).

## Philosophy

The objective is not to reproduce a fictional implementation line-for-line. The objective is to engineer the closest practical software architecture to the **behavioural idea** of JARVIS: persistent, adaptive, context-aware, capable of reasoning across domains, able to use available tools, resilient to component failure, and capable of improving through experience.
