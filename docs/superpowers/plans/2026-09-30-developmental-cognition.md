# Developmental Cognition Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a developmental cognitive architecture in which JARVIS is born with general cognitive mechanisms and acquires knowledge, associations, strategies, preferences, skills, and behavioral tendencies through experience.

**Architecture:** Preserve the existing Brain/event-journal architecture while separating semantic knowledge from individual experiences. Build cognition as a closed loop: perception/observation → attention → memory/association → world model → prediction → decision/action → outcome → prediction error → learning/adaptation. Learned behavior must emerge from mechanisms rather than a hard-coded behavior table. Subsystems should use the language/runtime appropriate to their computational requirements; the architecture must remain polyglot-capable rather than Python-only.

**Tech Stack:** Existing JARVIS C++ cognitive core and event journal; existing model-specific modules; tests already used by the repository. Add other languages/runtimes only where subsystem requirements justify them.

**Spec:** `docs/jarvis/developmental-cognition.md`

## Global Constraints

- Engineer mechanisms; acquire behavior.
- Do not encode a large `if X then behavior Y` behavioral rulebook as a substitute for cognition.
- Semantic identity and individual experience identity must remain distinct.
- Prediction outcomes must correlate to exact prediction instances when that identity is available.
- Learning must change future behavior/state, not merely append records or return successful status codes.
- Learned state must survive restart/replay through the event journal.
- Cognitive layers must interact through explicit interfaces rather than duplicated hidden state.
- Deterministic mathematical/trade/action authority remains outside probabilistic generative components where applicable.
- Do not claim human consciousness or literal biological-brain equivalence.
- Language selection follows subsystem requirements; no blanket single-language mandate.
- Every major cognitive mechanism needs behavioral verification demonstrating an observable before/after change caused by experience.

## Review Focus

- Two unresolved predictions with the same semantic key must coexist and resolve independently — covered by prediction-instance tests.
- Restart must preserve learned prediction/association state — covered by replay tests.
- A repeated experience must actually alter future prediction or strategy — covered by developmental behavioral tests.
- Unrelated experience must not corrupt a learned association — covered by interference/isolation tests.
- Learned behavior must generalize to a novel but structurally related situation without a hard-coded case — covered by generalization tests.

---

### Task 1: Prediction Instance Identity

**Files:**
- Modify: `core/cpp/include/jarvis/core/brain.hpp`
- Modify: `core/cpp/src/brain.cpp`
- Modify: prediction/cognitive-cycle source files that construct and resolve prediction outcomes
- Test: existing JARVIS brain/prediction test targets

**Interfaces:**
- Consumes: existing `Prediction`, `Event`, `Brain::predict`, `Brain::resolve_prediction`, and journal replay interfaces.
- Produces: exact prediction-instance correlation using journal sequence identity while preserving semantic-key lookup compatibility.

- [ ] **Step 1: Write the failing concurrent-prediction test**
  - Create two unresolved predictions for the same semantic key.
  - Assert both prediction instances remain addressable.
  - Resolve the first instance and assert the second remains unresolved.

- [ ] **Step 2: Run the focused test and verify failure**
  - Expected: current semantic-key-only storage overwrites the first instance or cannot resolve instances independently.

- [ ] **Step 3: Implement instance storage and correlation**
  - Preserve semantic key as the learning aggregation key.
  - Preserve journal sequence as the unique experience/prediction identity.
  - Persist `prediction_sequence` in outcome events.
  - Maintain the existing key-based API as a compatibility path that resolves the latest unresolved instance.

- [ ] **Step 4: Verify replay**
  - Restart/reconstruct the Brain from the journal.
  - Assert all prediction instances and their resolved states are restored exactly.

- [ ] **Step 5: Run focused and existing prediction tests**
  - Expected: all pass, including backward-compatible key-based resolution.

- [ ] **Step 6: Commit**
  - Commit message: `fix: preserve prediction experience identity`

### Task 2: Experience and Episodic Memory

**Files:**
- Modify/create focused cognitive-memory implementation files following existing repository structure.
- Test: episodic memory/developmental behavior tests.

**Interfaces:**
- Consumes: journal events and prediction outcomes.
- Produces: structured experience records with context, outcome, salience, causal/associative references, and consolidation status.

- [ ] **Step 1: Write failing tests for experience formation, retrieval, and persistence.**
- [ ] **Step 2: Implement experience records as mechanisms, not preloaded knowledge.**
- [ ] **Step 3: Add relevance/salience-aware retrieval without deleting low-salience history prematurely.**
- [ ] **Step 4: Add consolidation/forgetting mechanisms with deterministic bounded behavior.**
- [ ] **Step 5: Verify restart/replay preserves consolidated learning.**
- [ ] **Step 6: Commit.**

### Task 3: Associative Learning and World-Model Formation

**Files:**
- Existing association/concept/world-model modules.
- Tests for learned associations and abstraction.

**Interfaces:**
- Consumes: experiences and contextual observations.
- Produces: weighted associations, concepts, structural similarities, and world-model updates.

- [ ] **Step 1: Write failing tests where repeated co-occurrence strengthens an association.**
- [ ] **Step 2: Write failing tests where contradictory evidence weakens/disputes it.**
- [ ] **Step 3: Implement incremental association learning.**
- [ ] **Step 4: Implement concept/generalization formation from shared structure rather than explicit concept lists.**
- [ ] **Step 5: Verify novel related cases can inherit learned structure without a case-specific rule.**
- [ ] **Step 6: Commit.**

### Task 4: Prediction-Error Learning and Adaptation

**Files:**
- Existing prediction/learning/reflection modules.
- Tests for prediction error and behavioral adaptation.

**Interfaces:**
- Consumes: prediction instances and exact outcomes.
- Produces: updated predictive statistics, confidence, error history, and adaptation signals grouped by semantic concept.

- [ ] **Step 1: Write failing test proving repeated prediction errors alter future prediction.**
- [ ] **Step 2: Implement error aggregation separately from prediction-instance identity.**
- [ ] **Step 3: Add confidence adaptation based on evidence quality and error history.**
- [ ] **Step 4: Verify learned changes survive restart.**
- [ ] **Step 5: Verify unrelated keys do not receive the update.**
- [ ] **Step 6: Commit.**

### Task 5: Attention and Salience

**Files:**
- Existing attention/state modules plus focused tests.

**Interfaces:**
- Consumes: novelty, uncertainty, prediction error, goals, threat/opportunity signals, learned relevance.
- Produces: bounded attention/salience allocation that influences which information is processed deeply.

- [ ] **Step 1: Write failing salience competition tests.**
- [ ] **Step 2: Implement compositional salience mechanisms rather than keyword-triggered attention.**
- [ ] **Step 3: Verify attention changes after learned relevance and prediction error.**
- [ ] **Step 4: Commit.**

### Task 6: Affect-Like Internal State Mechanisms

**Files:**
- Existing threat/self/attention state modules where appropriate; add focused affect-state module only if current boundaries require it.
- Tests for learned appraisal effects.

**Interfaces:**
- Consumes: prediction outcomes, uncertainty, goal progress, threat/opportunity appraisal, social feedback, resource state.
- Produces: bounded internal affect-like dimensions that influence attention, prediction and decision-making.

- [ ] **Step 1: Write failing tests showing an initially neutral system develops a state from repeated experience.**
- [ ] **Step 2: Implement appraisal/state dynamics without hard-coded object→emotion mappings.**
- [ ] **Step 3: Verify the state influences future cognition and decays/updates with new evidence.**
- [ ] **Step 4: Commit.**

### Task 7: Goal and Motivation Development

**Files:**
- Existing goals/intent/strategy modules.
- Developmental goal tests.

**Interfaces:**
- Consumes: internal state, learned outcomes, explicit user goals, constraints, opportunities and resource limits.
- Produces: prioritized goal candidates and strategy adjustments without inventing unauthorized external objectives.

- [ ] **Step 1: Write failing tests for goal reprioritization from experience.**
- [ ] **Step 2: Implement learned strategy/priority adaptation within explicit authority boundaries.**
- [ ] **Step 3: Verify goal changes are explainable through recorded evidence.**
- [ ] **Step 4: Commit.**

### Task 8: Procedural/Skill Learning

**Files:**
- New focused skill/procedural-learning module if no existing equivalent is suitable.
- Skill-learning tests.

**Interfaces:**
- Consumes: action sequences, outcomes, context, cost, risk and feedback.
- Produces: reusable strategies with learned reliability and preconditions.

- [ ] **Step 1: Write failing test for learning a reusable sequence from repeated successful experience.**
- [ ] **Step 2: Implement strategy extraction and context matching.**
- [ ] **Step 3: Add failure-based weakening rather than permanent success encoding.**
- [ ] **Step 4: Verify transfer to a structurally similar task.**
- [ ] **Step 5: Commit.**

### Task 9: Self-Model Development

**Files:**
- Existing self-model/capability modules.
- Self-model developmental tests.

**Interfaces:**
- Consumes: capability observations, action outcomes, errors, successful/failed strategies.
- Produces: learned estimates of capability, reliability, uncertainty and recurring failure modes.

- [ ] **Step 1: Write failing tests where repeated success/failure changes capability confidence.**
- [ ] **Step 2: Implement evidence-backed self-model updates.**
- [ ] **Step 3: Verify self-model does not simply mirror static configuration.**
- [ ] **Step 4: Commit.**

### Task 10: Closed Developmental Cognitive Loop

**Files:**
- Brain integration/orchestration and cognitive-cycle modules.
- End-to-end developmental tests.

**Interfaces:**
- Consumes: perception/observation, learned state, goals, available capabilities.
- Produces: prediction, decision, action, outcome, learning and updated state in one coherent cycle.

- [ ] **Step 1: Write an end-to-end test starting from an inexperienced state.**
- [ ] **Step 2: Run the same environment repeatedly and capture behavioral changes.**
- [ ] **Step 3: Verify a novel but related environment benefits from learned structure.**
- [ ] **Step 4: Verify restart preserves developmental state.**
- [ ] **Step 5: Verify no behavior-specific hard-coded rule is required for the demonstrated adaptation.**
- [ ] **Step 6: Commit.**

### Task 11: Polyglot Boundary Review

**Files:**
- Architecture documentation and subsystem build/configuration files only where justified.

**Interfaces:**
- Consumes: measured computational/runtime requirements from completed cognitive layers.
- Produces: explicit language/runtime boundaries based on requirements.

- [ ] **Step 1: Profile completed cognitive components for latency, memory, concurrency, ML/runtime and deployment constraints.**
- [ ] **Step 2: Identify components where C++ is not the appropriate implementation language.**
- [ ] **Step 3: Define language/service boundaries only where they materially improve the subsystem.**
- [ ] **Step 4: Add integration tests across each selected boundary.**
- [ ] **Step 5: Commit.**

### Task 12: Cognitive Verification Gate

**Files:**
- Full cognitive test suite and verification documentation.

**Interfaces:**
- Consumes: all completed developmental mechanisms.
- Produces: evidence that JARVIS learns, adapts, persists and generalizes rather than merely executing prewritten rules.

- [ ] **Step 1: Run focused unit tests for each layer.**
- [ ] **Step 2: Run end-to-end developmental tests.**
- [ ] **Step 3: Run restart/replay tests.**
- [ ] **Step 4: Run adversarial tests for overwriting, interference, stale learning, contradictory evidence and concurrent experiences.**
- [ ] **Step 5: Review code for hard-coded behavior masquerading as learning.**
- [ ] **Step 6: Run repository build/CI verification.**
- [ ] **Step 7: Only then mark the developmental cognition milestone complete.**
- [ ] **Step 8: Commit verification evidence/documentation.**
