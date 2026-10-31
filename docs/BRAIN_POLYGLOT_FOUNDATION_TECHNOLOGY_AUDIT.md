# JARVIS Brain — Polyglot Foundation Technology Audit

**Status:** Initial repository-grounded audit and engineering direction; not an implementation-completion claim.  
**Audit date:** 2026-10-31  
**Inspected baseline:** `docs/brain-polyglot-foundation-audit-20261031`, branched from PR #163 HEAD `573ed8e43ed77c1e119af89e13a6a2cd9a319557`.  
**Purpose:** Record the current technology foundation, identify capability gaps, and define how the Brain should use suitable languages and frameworks without forcing every mechanism into C++ or introducing technology for appearance.

This document supplements, and does not replace, `JARVIS_BRAIN_MASTER_BLUEPRINT.md`, `DEVELOPMENTAL_BRAIN_PLAN.md`, or the Priority-One trust-boundary contract.

---

## 1. Governing engineering position

The Brain is the primary developmental system from which the wider JARVIS system will derive its capabilities. It must be engineered as a serious, integrated cognitive foundation.

The governing principle remains:

> **ENGINEER THE MECHANISMS; LET BEHAVIOR BE ACQUIRED THROUGH EXPERIENCE.**

The foundation must be capable of supporting increasingly capable perception, representation, memory, learning, prediction, reasoning, planning, action, adaptation, and controlled cognitive development.

Technology selection must be capability-driven:

- Use a language or framework when it provides a material capability, reliability, research, performance, safety, or maintainability advantage.
- Do not force every subsystem into C++ merely because C++ is fast.
- Do not introduce Python, PyTorch, Rust, CUDA, or Triton as decorative dependencies. Each must have a real responsibility and an integration path into the Brain.
- Do not artificially reserve a language for a rigid list of modules. Boundaries are provisional engineering decisions and must be revisited when profiling, experiments, or architecture evidence justify it.
- Do not duplicate the same cognitive state in disconnected implementations.
- Do not replace internally engineered cognitive mechanisms with a hosted AI API or a thin model wrapper.
- Do not hardcode scenario answers, stimulus-to-behavior mappings, or fixed learning outcomes where the intended capability is supposed to be acquired from experience.

The objective is a coherent polyglot Brain, not a collection of unrelated language-specific prototypes.

## 2. Repository evidence inspected

The following observations are grounded in the inspected repository snapshot. They describe what was visible at this baseline, not every possible uninspected file or future branch.

### 2.1 C++ is currently the implemented center of gravity

Inspected file: `core/cpp/CMakeLists.txt` (blob `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`).

The C++20 `jarvis_core` target compiles a substantial set of cognitive and runtime source files, including:

- Brain and cognitive-cycle/runtime orchestration.
- Memory and persistence.
- World model, world state, representation, and perception pipeline.
- Knowledge, reasoning, causal and association models.
- Prediction context, learning loop, and developmental learning.
- Attention, affective state/learning, threat appraisal, and resilience.
- Goals, intent, planning, strategy, decision, and action execution.
- Self-state, self-model, reflection, and self-testing.
- Evolution proposal, experiment, sandbox, adoption, monitoring, and rollback components.
- Capability registry, evaluation, and execution.

This is meaningful existing work and must be preserved. It is also a concentration risk: the current build manifest shows the cognitive substrate is overwhelmingly compiled as one C++ library. The presence of many C++ modules does not itself prove that all mechanisms form a capable developmental learning system.

The CMake target sets C++20, builds a static library, enables CTest, and applies compiler warnings. The inspected target does not declare a Python/PyTorch integration, CUDA language target, or Triton kernel build.

### 2.2 Python and PyTorch are not yet visible as an implemented Brain development stack

The inspected repository root contains `.github`, `core`, `docs`, `engineering`, `interfaces`, and `runtime`, plus `README.md`. No top-level Python project or Python Brain package was visible in that root listing.

The inspected C++ build manifest does not declare Python, PyTorch, or a Python binding/runtime dependency. This audit has not exhaustively searched every file on every branch; therefore the precise finding is **no verified, integrated Python/PyTorch Brain subsystem at the inspected baseline**, not a claim that no Python file exists anywhere in the repository.

This is a material gap against the intended use of the modern machine-learning ecosystem. Python and PyTorch should be evaluated for actual learning mechanisms and experiments, rather than being excluded by a C++-only default.

### 2.3 Rust exists, but the inspected runtime is still minimal

Inspected files:

- `runtime/rust/Cargo.toml` (blob `c8e5a4d1cd1faef5c79a816fbef04d5022575f0a`).
- `runtime/rust/src/lib.rs` (blob `ba949e43b7e06ce081b078035dfe7e48625d521c`).

The Cargo manifest has no dependencies. The inspected `BrainRuntime` owns a small `CognitiveState` and exposes a simple validated `observe(key, value, strength)` method. The crate forbids unsafe Rust.

This is a useful starting point for exploring a safe runtime boundary, but it is not evidence of a production Rust host, secure storage provider, full cognitive runtime, or integrated Rust/C++ Brain. It must not become a second competing source of cognitive truth.

Rust should be developed where its ownership, memory safety, concurrency, or isolation properties materially strengthen the system. A concrete candidate is a host-owned trust/security boundary, but that work must satisfy the unresolved host trust-anchor contract in `PRIORITY_ONE_TRUST_BOUNDARY_CONTRACT.md`. The actual deployment and key lifecycle must be specified before claiming that Rust solves journal integrity.

### 2.4 TypeScript exists as an interface area

The inspected repository contains `interfaces/typescript/src`. It is a suitable place for typed integration contracts and external control/interface work. The inspected directory listing did not show a `package.json` at `interfaces/typescript`; the status and completeness of the TypeScript toolchain require a separate targeted inspection.

TypeScript should not become the cognitive engine merely because it is convenient for application interfaces. Its value is typed contracts, operator/developer interfaces, and integration surfaces.

### 2.5 CUDA and Triton are not verified as integrated

The inspected C++ CMake target does not enable CUDA or declare GPU kernel targets. No Triton dependency or kernel integration was verified in the inspected manifests.

This is an integration gap to evaluate, not an instruction to add GPU dependencies blindly. CUDA and Triton become relevant when measured workloads contain enough tensor/matrix or other parallel numerical computation to justify GPU execution. A CPU path must remain available where practical.

## 3. Recommended technology responsibilities

These are initial responsibility boundaries, not immutable module assignments.

| Technology | Where it can materially help the Brain | Required integration rule |
|---|---|---|
| **C++20** | Existing cognitive runtime, event lifecycle, deterministic state transitions, memory/replay, orchestration, latency-sensitive mechanisms, and native integration | Remains the current runtime foundation; do not make it the only implementation language by default |
| **Python** | Learning research, experiment orchestration, data preparation, model training, evaluation, and rapid iteration on learning algorithms | Must operate on real Brain experiences and return versioned, testable learned artifacts or results through explicit contracts |
| **PyTorch** | Trainable neural representations, learned embeddings, sequence/temporal models, predictive models, differentiable components, and other learning mechanisms where experiments justify them | Use for actual model learning, not as a decorative import or a replacement for the whole cognitive architecture |
| **Rust** | Memory-safe services, trust-boundary components, concurrency-sensitive infrastructure, process isolation, and host-owned security facilities | Must have a clearly defined authority boundary and must not create a competing cognitive state |
| **CUDA** | GPU acceleration for measured numerical workloads, including PyTorch operations and custom kernels where needed | Introduce only with a reproducible workload, benchmark, hardware capability check, and CPU fallback where feasible |
| **Triton language** | Custom GPU kernels when profiling shows framework operations are insufficient or a specialised kernel materially improves throughput/latency | Treat as an optimisation layer, not a prerequisite for basic learning and not the Triton inference server |
| **TypeScript** | Typed interfaces, developer/operator tooling, and integration contracts | Keep cognition and authoritative learning state in the Brain; interfaces are clients of explicit contracts |

### 3.1 Python and PyTorch: the most important missing ecosystem to investigate

The current architecture should not be limited to hand-authored C++ statistical updates if a trainable model can provide a useful learned representation or predictive capability.

Priority investigations for Python/PyTorch include:

1. **Representation learning:** test whether the Brain can learn useful structure from observations rather than relying only on hand-authored feature mappings.
2. **Associative and relational learning:** learn reusable relationships across experiences and distinguish meaningful structure from coincidental co-occurrence.
3. **Prediction:** train models to predict outcomes from context and measure whether prediction error improves future predictions.
4. **Temporal learning:** investigate sequence models and delayed consequences where the current mechanisms need temporal credit assignment.
5. **Generalisation:** test transfer to unseen contexts, with controls against memorisation and label leakage.
6. **Continual learning:** evaluate how new experiences can improve the model while measuring forgetting, interference, and regression.
7. **Evaluation:** build reproducible experiment tooling for learning curves, calibration, transfer, reversal, retention, and regression.

These are candidate research directions. The audit does not assert that one neural architecture is already known to solve them. Each mechanism must be selected through experiments and compared with simpler baselines.

A PyTorch model must not be allowed to silently become the sole owner of memory, beliefs, goals, or decisions. The Brain needs inspectable state, evidence lineage, explicit update semantics, and controlled model lifecycle.

### 3.2 Integration must be part of the design

Python/PyTorch should not become a disconnected training notebook that produces a model nobody in the live Brain uses.

The integration design must define:

- A versioned, typed representation of experiences and context.
- Which component owns authoritative episodic history and event sequencing.
- How training examples are derived from real, validated experience.
- How provenance, uncertainty, dependence, and outcome labels are retained.
- How model versions, configuration, training progress, and evaluation evidence are recorded.
- How inference results re-enter the cognitive cycle.
- How failures, timeouts, incompatible model versions, and unavailable accelerators are handled.
- How a candidate model is evaluated against a baseline before adoption.
- How rollback works without erasing the experience that led to the candidate.
- How deterministic replay and reproducibility are preserved where required.

The C++ Brain may host Python through an embedded runtime or communicate with a separately managed local process. This choice is **not decided by this audit**. It must be made after comparing deployment complexity, latency, crash isolation, concurrency, packaging, model lifecycle, and testability. Either way, the integration is internal and must not depend on a hosted third-party AI API.

A process boundary can be useful for fault isolation; it is not automatically the best design. Avoid premature microservice decomposition.

### 3.3 Rust must strengthen the foundation rather than duplicate it

The Rust runtime should have a specific contract before substantial expansion. Candidate responsibilities include secure host services, constrained execution, concurrency-sensitive infrastructure, and a protected trust integration.

Do not port existing C++ cognitive modules to Rust merely to increase language count. Do not allow two runtimes to make independent authoritative belief or memory updates. If Rust owns a security or persistence boundary, the Brain must consume explicit success/failure and integrity status from that boundary.

### 3.4 CUDA and Triton must be evidence-led

GPU acceleration is useful only when the workload benefits from it. The engineering sequence is:

1. Establish a correct CPU implementation and behavioural baseline.
2. Measure representative training and inference workloads.
3. Identify actual bottlenecks and memory-transfer costs.
4. Benchmark a GPU implementation on supported hardware.
5. Add CUDA or Triton kernels only where the measured benefit justifies maintenance and portability costs.
6. Verify numerical tolerances, determinism requirements, fallback behavior, and end-to-end cognitive behavior.

Do not make GPU availability a prerequisite for running the basic Brain or its developmental tests.

## 4. Architecture risks identified

1. **C++ monoculture risk:** many mechanisms are represented in the C++ target, while the Python/PyTorch learning ecosystem is not yet verified as integrated.
2. **Module-count illusion:** the large source list can create a false impression of cognitive completeness. Integration and acquired behavioral change remain the acceptance criteria.
3. **Parallel-runtime risk:** a growing Rust runtime could create a second, inconsistent cognitive state unless authority and synchronization are explicit.
4. **Disconnected-ML risk:** adding PyTorch without connecting real experiences, persisted training state, inference, and evaluation would create a demo rather than a brain capability.
5. **Premature-GPU risk:** adding CUDA/Triton before profiling creates build, packaging, hardware, and test complexity without proven cognitive benefit.
6. **State/provenance risk:** learned model artifacts and training data must respect the Brain's evidence, journal, trust, and replay contracts. A model checkpoint alone is not a trustworthy record of how a belief was acquired.
7. **Hardcoded-learning risk:** scenario-specific features, labels, reward rules, or fixed action mappings can make a test appear to learn when it merely encodes the answer. Test environments may define ground truth and consequences; the Brain must acquire the relevant policy or relationship from experience.

## 5. Recommended implementation sequence

This sequence is designed to improve the existing Brain without restarting it or diverting from the active priority.

### Work package A — Complete the current Priority-One foundation

Continue the active Priority-One work and its independent testing/review. In particular, resolve the documented persistence/trust boundary, evidence provenance, calibration, and replay requirements. A trainable model must not be built on top of an untrustworthy experience history.

The technology audit does not change the Priority-One acceptance criteria and does not authorize declaring Priority One complete.

### Work package B — Perform a focused Python/PyTorch integration design

Before introducing dependencies, write a concrete design covering:

- The first learning capability that genuinely benefits from PyTorch.
- Experience schema and event ownership.
- Training/inference boundary and process model.
- Model/checkpoint versioning and persistence.
- Provenance and outcome-label policy.
- Evaluation, baseline comparison, adoption, and rollback.
- CPU-only execution and optional GPU acceleration.
- Build, packaging, CI, and reproducibility requirements.

The first capability must be selected from an actual gap in the current Brain, not from framework popularity.

### Work package C — Build one end-to-end learned capability

Choose one bounded capability and implement a complete vertical slice:

1. The existing Brain receives and validates experiences.
2. The experiences are represented with context and provenance.
3. A Python/PyTorch mechanism learns from those experiences.
4. The learned model makes a prediction or produces a representation used by the live cognitive cycle.
5. An observed outcome produces a measurable learning signal.
6. The model is evaluated against a baseline and only then adopted.
7. The model and its provenance survive restart.
8. An unseen-context test checks transfer and a negative control checks inappropriate transfer.
9. Repeated trials measure learning, forgetting, reversal, and regression.

The selected capability must be learned from data/experience; the test must not hand the model the answer through fixed mappings.

### Work package D — Define and strengthen the Rust boundary

Inspect the existing Rust runtime and decide whether it should become a host/security service, a constrained execution service, or remain a limited prototype until a concrete need exists. Define authority, contracts, and failure behavior before expansion.

### Work package E — Profile and selectively accelerate

Benchmark actual training/inference workloads. Introduce CUDA and/or Triton only for demonstrated bottlenecks. Keep CPU operation and CI coverage.

### Work package F — Integrate and validate the developmental Brain

Run cross-language integration, fresh-process persistence, exact-head CI, sanitizers, fault injection, adversarial tests, and long-duration developmental experiments. Measure acquired behavioral capability, not language count, source lines, or module count.

## 6. Required acceptance evidence for polyglot integration

A language/framework is not considered integrated merely because a dependency file exists or a sample imports successfully.

For each integrated component, require:

- A documented responsibility and owner.
- A versioned interface and explicit data schema.
- Clear authority over state and updates.
- Defined concurrency, timeout, and failure semantics.
- Reproducible build and deployment instructions.
- Unit and integration tests.
- Invalid-input and fault-injection tests.
- Persistence/restart behavior where stateful.
- Performance measurements where performance is the reason for adoption.
- Evidence that the component improves a real cognitive capability or materially strengthens reliability/security.
- A fallback or degraded-mode policy where the component is optional.

For a learning component, additionally require:

- Training data derived from validated experience.
- Explicit train/validation/test separation.
- Leakage and memorisation controls.
- An appropriate baseline.
- Unseen-context transfer tests.
- Contradictory and distribution-shift tests.
- Continual-learning and forgetting measurements.
- Checkpoint/model provenance and reproducibility.
- A candidate-adoption and rollback protocol.
- A demonstrated change in later Brain behavior, not only a changed loss value or model metric.

## 7. Decisions deliberately left open

The following choices require evidence and must not be guessed:

- Embedded Python versus a separately managed local Python process.
- The first PyTorch architecture and learning task.
- Whether Rust should own a particular host/security boundary.
- The exact C++/Rust inter-process or foreign-function interface.
- CUDA versus framework-managed GPU execution for each workload.
- Whether custom Triton kernels are justified.
- The eventual deployment topology and number of machines.

No cloud-hosted AI API is required to answer these questions. The Brain's own architecture, locally controlled components, and reproducible experiments must remain central.

## 8. Audit conclusion

The repository already documents an intentional polyglot direction in `docs/ARCHITECTURE.md` and `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md`. However, the inspected implementation is currently centered on a large C++20 cognitive library, with a minimal Rust runtime, a TypeScript interface area, and no verified integrated Python/PyTorch learning stack or CUDA/Triton execution path.

That mismatch should be addressed deliberately. The next meaningful technology investment is a properly designed Python/PyTorch learning path integrated with the existing Brain's real experiences and state—not a wholesale rewrite and not an isolated model demo. Rust should be given a concrete safety/host responsibility. GPU technologies should follow workload evidence.

**The measure of success is not that JARVIS uses more languages. It is that these technologies cooperate to make the Brain more capable of acquiring, retaining, generalising, and applying knowledge through experience.**

**Disposition:** Initial audit documented. No runtime dependencies or cognitive implementation were changed by this document. Priority One remains governed by its existing acceptance gates. Independent architecture review is required before implementation of the proposed cross-language learning boundary.
