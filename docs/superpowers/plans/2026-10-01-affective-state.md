# Emergent Affective State Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Add a bounded, replayable internal valuation subsystem that learns dynamic affect-like state from experience without hard-coded emotions or action rules.

**Architecture:** Introduce `AffectiveStateModel` as a pure state-transition component. Brain converts existing prediction/action/goal/memory evidence into normalized affective evidence, journals resulting state transitions, and replays them. Affective state is exposed as contextual input to attention, consolidation, prediction context, and strategy/decision context; it never directly authorizes or executes actions.

**Tech Stack:** C++20, existing Brain/Event/Memory/Attention/DevelopmentalLearning architecture, CMake/CTest.

**Spec:** `docs/superpowers/specs/2026-10-01-affective-state.md`

## Global Constraints

- No named-emotion behavior tables or fixed emotion-to-action mappings.
- All affective dimensions are finite and bounded.
- Old journals replay with neutral affective defaults.
- Affective state cannot bypass authorization, verification, rollback, or deterministic trade/action engines.
- State changes must be reconstructable from journaled events.
- Learning must operate on continuous evidence and associations, not `state X -> always action Y` rules.

## Review Focus

- Malformed/non-finite evidence must leave state finite and bounded — Task 1 tests sanitization.
- Repeated evidence must accumulate without saturation bugs or runaway values — Task 1 tests bounded accumulation.
- Old journal events lacking affective fields must replay neutrally — Task 2 tests backward-compatible replay.
- Affective context must bias cognition without directly selecting/executing an action — Task 3 tests contextual propagation and unchanged authorization.
- Contradictory evidence and decay must move state toward/reverse from prior values predictably — Task 1 tests both dynamics.

### Task 1: Affective State Core

**Files:**
- Create: `core/cpp/include/jarvis/core/affective_state.hpp`
- Create: `core/cpp/src/affective_state.cpp`
- Test: `core/cpp/tests/affective_state_suite.cpp`

**Interfaces:**
- Consumes: normalized evidence `{valence, arousal, uncertainty, agency, goal_pressure}` plus update parameters.
- Produces: `AffectiveState` and deterministic update/decay operations.

- [ ] **Step 1: Write failing tests** for neutral initialization, positive/negative evidence, repeated bounded accumulation, decay, contradiction, and non-finite evidence rejection.
- [ ] **Step 2: Run `jarvis_affective_state_suite` and verify the new API/tests fail.**
- [ ] **Step 3: Implement `AffectiveStateModel::update(const AffectiveEvidence&)`, `decay(double)`, and `state()` with finite/bounded sanitization and configurable learning/decay rates.**
- [ ] **Step 4: Run the suite and verify all core dynamics pass.**
- [ ] **Step 5: Commit `feat: add bounded affective state dynamics`.**

### Task 2: Brain Journal Integration

**Files:**
- Modify: `core/cpp/include/jarvis/core/brain.hpp`
- Modify: `core/cpp/src/brain.cpp`
- Modify: `core/cpp/tests/CMakeLists.txt`
- Test: `core/cpp/tests/affective_brain_suite.cpp`

**Interfaces:**
- Consumes: Task 1 `AffectiveStateModel`.
- Produces: journal-replayable affective state and `Brain::affective_state()`.

- [ ] **Step 1: Write failing Brain integration tests** for prediction error, action reliability, goal pressure, journal replay, and old events without affective fields.
- [ ] **Step 2: Run the integration test and verify failure.**
- [ ] **Step 3: Add `affective_state_` to Brain and journal `affective_update` evidence/state needed for deterministic replay.**
- [ ] **Step 4: Feed prediction/action/goal/memory evidence into the model without event-kind-specific emotion rules.**
- [ ] **Step 5: Replay affective events and expose `Brain::affective_state()`.**
- [ ] **Step 6: Run the integration suite and verify persistence/replay equivalence.**
- [ ] **Step 7: Commit `feat: integrate affective state with brain replay`.**

### Task 3: Cognitive Context Propagation

**Files:**
- Modify: `core/cpp/include/jarvis/core/attention.hpp`
- Modify: `core/cpp/src/attention.cpp`
- Modify: `core/cpp/include/jarvis/core/strategy.hpp`
- Modify: `core/cpp/src/strategy.cpp`
- Modify: `core/cpp/include/jarvis/core/decision.hpp`
- Modify: `core/cpp/src/decision.cpp`
- Modify: `core/cpp/include/jarvis/core/brain.hpp`
- Modify: `core/cpp/src/brain.cpp`
- Test: `core/cpp/tests/affective_context_suite.cpp`

**Interfaces:**
- Consumes: `AffectiveState` from Task 2.
- Produces: bounded affective context fields for attention/strategy/decision scoring.

- [ ] **Step 1: Write failing tests** proving affective context changes contextual scores while no affective state directly chooses an action.
- [ ] **Step 2: Run the suite and verify failure.**
- [ ] **Step 3: Add bounded context fields to existing cognitive context structures.**
- [ ] **Step 4: Incorporate those fields with bounded weights into attention/strategy/decision context calculations.**
- [ ] **Step 5: Verify authorization and action execution behavior is unchanged.**
- [ ] **Step 6: Run all affective suites plus existing action/decision tests.**
- [ ] **Step 7: Commit `feat: propagate affective context through cognition`.**

### Task 4: Developmental Learning and Consolidation Coupling

**Files:**
- Modify: `core/cpp/src/brain.cpp`
- Modify: `core/cpp/include/jarvis/core/developmental_learning.hpp` only if required by existing interface boundaries
- Modify: `core/cpp/tests/affective_context_suite.cpp`

**Interfaces:**
- Consumes: affective state + existing prediction/action outcomes.
- Produces: learned associations involving affective context, never fixed action prescriptions.

- [ ] **Step 1: Add a failing test that repeated contextual outcomes alter learned association strength but do not create an unconditional action rule.**
- [ ] **Step 2: Verify failure.**
- [ ] **Step 3: Feed bounded affective context into existing `LearningSignal` paths.**
- [ ] **Step 4: Verify learned state survives journal replay.**
- [ ] **Step 5: Run the complete cognitive test set.**
- [ ] **Step 6: Commit `feat: couple affective context to developmental learning`.**

### Task 5: Whole-Branch Verification

**Files:** existing affected files only.

- [ ] **Step 1:** Run CMake configure/build for the C++ core.
- [ ] **Step 2:** Run all existing tests plus every new affective suite.
- [ ] **Step 3:** Inspect journal compatibility and verify no hidden mutable affective state is required for replay.
- [ ] **Step 4:** Run static/source checks for emotion-to-action hardcoding and unbounded state mutation.
- [ ] **Step 5:** Fix any Critical/Important failures with a fresh RED→GREEN cycle.
- [ ] **Step 6:** Commit final verification fixes only after green tests.

## Completion Contract

The feature is complete only when all ten requirements in the spec are demonstrated by tests, existing action authorization/verification behavior remains intact, affective state survives journal replay, and no named-emotion action mapping has been introduced.
