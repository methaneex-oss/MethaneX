# Engineering Agent Orchestration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Complete the provider-neutral engineering-agent selection and synchronized implementation/review/verification flow so JARVIS can choose agents from capability metadata, execute them in a shared workspace, and return normalized evidence without embedding vendor-specific intelligence in the brain.

**Architecture:** The engineering coordinator discovers eligible agents from declared capabilities, permissions, artifact contracts, availability, risk, cost, and reliability. The pipeline owns a run-scoped workspace and stage lifecycle; agents execute through the existing authorization/execution boundary. Results and evidence remain normalized so later cognitive components can consume them without knowing the provider.

**Tech Stack:** C++20, CMake, CTest, existing JARVIS engineering interfaces, GitHub CI.

**Spec:** In-chat approved design from 2026-09-21: metadata-driven selection; shared workspace; implementation → review → verification; normalized evidence; provider-neutral brain; tests and CI before merge.

## Global Constraints

- Preserve C++20 and existing CMake/CTest architecture.
- Do not introduce vendor-specific logic into cognitive code.
- Do not replace existing explicit-agent execution; selection is an additional path.
- Do not hard-code agent identity as the basis for capability selection.
- Authorization remains mandatory before execution.
- Workspace isolation and commit ownership remain explicit boundaries.
- Tests must verify behavior, not merely object construction.

## Review Focus

- A task with no eligible agent must fail without execution.
- A task exceeding risk/cost/permission/artifact constraints must not be dispatched.
- Selection must remain deterministic for equal metadata so runs are reproducible.
- Shared-workspace stages must not independently commit or close the run workspace.
- A failed stage must stop the pipeline and preserve failure evidence.

---

### Task 1: Verify and harden metadata-driven agent selection

**Files:**
- Modify: `engineering/cpp/include/jarvis/engineering/coordinator.hpp`
- Modify: `engineering/cpp/src/coordinator.cpp`
- Test: `engineering/cpp/tests/coordinator_suite.cpp`

**Interfaces:**
- Consumes: `EngineeringTask`, `AgentDescriptor`, `EngineeringAgent`, `EngineeringAuthorizer`, `EngineeringExecutionBoundary`.
- Produces: `AgentCandidate`, `EngineeringCoordinator::discover`, `rank`, `dispatch_selected`.

- [ ] **Step 1: Verify existing tests cover capability, permission, artifact, availability, risk and cost filtering.**
- [ ] **Step 2: Add failing assertions for deterministic tie-breaking and every rejection dimension.**
- [ ] **Step 3: Implement the minimum coordinator logic required by those assertions without provider-specific conditions.**
- [ ] **Step 4: Run the coordinator test target with CTest and confirm all selection tests pass.**
- [ ] **Step 5: Commit the focused coordinator change.**

### Task 2: Integrate selection into the engineering pipeline

**Files:**
- Modify: `engineering/cpp/include/jarvis/engineering/pipeline.hpp`
- Modify: `engineering/cpp/src/pipeline.cpp`
- Test: `engineering/cpp/tests/pipeline_suite.cpp`

**Interfaces:**
- Consumes: `EngineeringCoordinator::dispatch_selected` and existing `EngineeringWorkspace` lifecycle.
- Produces: selector-driven `EngineeringPipeline::run` while preserving explicit-agent mode.

- [ ] **Step 1: Add a failing pipeline test that supplies multiple eligible agents without selecting an agent ID.**
- [ ] **Step 2: Add a failing test proving the shared workspace opens once, is reused across stages, and commits once.**
- [ ] **Step 3: Implement selector-driven dispatch and preserve explicit-agent compatibility.**
- [ ] **Step 4: Implement failure propagation so a rejected stage closes the workspace and prevents later stages.**
- [ ] **Step 5: Run the pipeline tests and full relevant CTest subset.**
- [ ] **Step 6: Commit the pipeline integration.**

### Task 3: Normalize engineering evidence for cognitive feedback

**Files:**
- Modify: existing engineering result/evidence interfaces only where required by the current repository.
- Test: existing engineering coordinator/pipeline suites.

**Interfaces:**
- Consumes: stage results, artifacts, authorization results and execution outcomes.
- Produces: stable evidence fields describing selected agent, stage, workspace, artifacts, execution outcome and failure reason.

- [ ] **Step 1: Add failing assertions for required normalized evidence on successful and failed runs.**
- [ ] **Step 2: Implement evidence propagation using existing `AgentEvidence` rather than introducing a parallel event model.**
- [ ] **Step 3: Verify evidence survives every stage boundary and remains provider-neutral.**
- [ ] **Step 4: Run integration tests and inspect serialized/returned evidence where the repository exposes it.**
- [ ] **Step 5: Commit the evidence integration.**

### Task 4: End-to-end synchronized engineering-agent test

**Files:**
- Modify/Create: existing engineering integration test location discovered during implementation; do not create a second test framework.
- Modify: CMake only if the existing test target requires registration.

**Interfaces:**
- Consumes: coordinator selection, shared workspace, authorization, execution boundary and normalized evidence.
- Produces: one executable integration path representing implementation → review → verification.

- [ ] **Step 1: Write a failing end-to-end test with three distinct fixture agents and one shared workspace.**
- [ ] **Step 2: Verify implementation output becomes review input and review output becomes verification input through workspace artifacts, not hard-coded messages.**
- [ ] **Step 3: Implement only missing wiring; reuse existing pipeline/coordinator/workspace abstractions.**
- [ ] **Step 4: Run the integration test and relevant CTest suite.**
- [ ] **Step 5: Run sanitizer builds including ThreadSanitizer where supported by the existing CI configuration.**
- [ ] **Step 6: Commit the end-to-end verification.**

### Task 5: CI and merge verification

**Files:**
- No source changes unless verification exposes a concrete defect.

- [ ] **Step 1: Push the focused branch and inspect the exact-head GitHub Actions runs.**
- [ ] **Step 2: Fix only verified failures and rerun the affected checks.**
- [ ] **Step 3: Confirm CMake/CTest, sanitizer and ThreadSanitizer status at the exact head SHA.**
- [ ] **Step 4: Merge only after required checks are green.**
- [ ] **Step 5: Verify `main` after merge and record the resulting commit SHA before starting the next capability.**
