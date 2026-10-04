# JARVIS Concept → Context → Prediction Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Connect experience-derived concept hypotheses to contextual prediction so learned structure changes future cognition without becoming unquestionable truth.

**Architecture:** Extend the existing C++ `AssociationModel` and `Brain` interfaces. Concepts remain derived evidence; prediction consumes them as contextual evidence with provenance, while outcome feedback remains capable of revising the underlying association/concept state.

**Tech Stack:** C++17/20 as established by the repository, existing JARVIS core cognition types, existing C++ test suite.

**Spec:** `docs/superpowers/specs/2026-09-26-concept-context-prediction-design.md`

## Global Constraints

- JARVIS remains one integrated cognitive system; do not create a second brain, memory store, or parallel architecture.
- Concept hypotheses are evidence, not authoritative truth.
- No hardcoded semantic categories or phrase-specific intelligence.
- Do not create a direct concept-to-action execution path.
- Preserve contradiction and uncertainty information.
- Reuse existing association traversal and Brain interfaces.

## Review Focus

- A concept with one exception must remain usable but weaker — test bounded degradation.
- Sustained contradictory evidence must remove a concept from trusted retrieval — test threshold behavior.
- Indirect graph context must remain weaker than direct association — test path decay.
- Prediction must not mutate authoritative belief state merely because it consumed a concept — test state immutability.
- Prediction provenance must survive through outcome evaluation — test the feedback identity.

### Task 1: Make concept evidence explicit

**Files:**
- Modify: `core/cpp/include/jarvis/core/association_model.hpp`
- Modify: `core/cpp/src/association_model.cpp`
- Test: `core/cpp/tests/association_causality_phase5_suite.cpp`

**Interfaces:**
- Extend `ConceptCandidate` with explicit contradiction/evidence fields rather than introducing a second concept type.
- Keep `AssociationModel::concept_candidates(double, std::size_t)` as the source of derived hypotheses.

- [ ] **Step 1: Write failing tests** for repeated support, bounded contradiction, and trusted-view removal.
- [ ] **Step 2: Run the focused C++ test and confirm the new assertions fail.**
- [ ] **Step 3: Implement minimal evidence accounting in `AssociationModel`.** Positive co-change raises support; counter-evidence raises contradiction and lowers usable strength.
- [ ] **Step 4: Run the focused test and confirm PASS.**
- [ ] **Step 5: Commit** `feat(cognition): expose concept evidence state`.

### Task 2: Retrieve concepts as contextual evidence through Brain

**Files:**
- Modify: `core/cpp/include/jarvis/core/brain.hpp`
- Modify: `core/cpp/src/brain.cpp`
- Modify: `core/cpp/include/jarvis/core/association_model.hpp`
- Modify: `core/cpp/src/association_model.cpp`
- Test: `core/cpp/tests/association_causality_phase5_suite.cpp`

**Interfaces:**
- Add a Brain-level retrieval method accepting an observation/context key and returning ranked `ConceptCandidate` evidence.
- Retrieval must use the existing association graph; no new persistence layer.

- [ ] **Step 1: Write failing test** proving relevant learned hypotheses are returned and unrelated hypotheses are absent.
- [ ] **Step 2: Run the focused test and confirm FAIL.**
- [ ] **Step 3: Implement retrieval using existing graph traversal and concept derivation.** Preserve coherence, support, contradiction, and provenance.
- [ ] **Step 4: Run the focused test and confirm PASS.**
- [ ] **Step 5: Commit** `feat(cognition): retrieve learned concepts as context`.

### Task 3: Feed concept evidence into prediction without mutating belief

**Files:**
- Inspect/modify existing prediction interfaces in `core/cpp/include/jarvis/core/` and `core/cpp/src/`.
- Test: existing prediction test location plus `association_causality_phase5_suite.cpp` where integration is already exercised.

**Interfaces:**
- Prediction accepts contextual concept evidence as non-authoritative input.
- Prediction output records concept provenance sufficient for later outcome comparison.

- [ ] **Step 1: Identify the existing prediction interface and write the failing integration test against that interface.**
- [ ] **Step 2: Run the focused test and confirm FAIL.**
- [ ] **Step 3: Implement minimal contextual evidence consumption; do not alter authoritative belief state.**
- [ ] **Step 4: Run the focused test and confirm PASS.**
- [ ] **Step 5: Commit** `feat(cognition): use learned concepts in prediction context`.

### Task 4: Close prediction → outcome feedback

**Files:**
- Modify: the existing prediction/outcome implementation identified in Task 3.
- Test: corresponding existing prediction/outcome suite.

**Interfaces:**
- Outcome evaluation consumes prediction provenance and updates association/concept evidence through existing learning mechanisms.

- [ ] **Step 1: Write failing test** where a concept-supported prediction succeeds and another is contradicted.
- [ ] **Step 2: Run test and confirm FAIL.**
- [ ] **Step 3: Implement outcome feedback using the existing learning path; do not create a parallel learner.**
- [ ] **Step 4: Run focused and relevant regression tests.**
- [ ] **Step 5: Commit** `feat(learning): close concept prediction feedback loop`.

### Task 5: End-to-end behavioral verification

**Files:**
- Test: `core/cpp/tests/association_causality_phase5_suite.cpp` or the repository's established integration test location.

- [ ] **Step 1: Add one end-to-end scenario:** repeated experience → concept candidate → contextual retrieval → prediction → observed outcome → revised evidence.
- [ ] **Step 2: Run the complete relevant C++ test target.**
- [ ] **Step 3: Inspect failures rather than weakening assertions to make the suite pass.**
- [ ] **Step 4: Run formatting/build/static checks available in the repository.**
- [ ] **Step 5: Commit** `test(cognition): verify concept to prediction learning loop`.

## Plan Self-Review

- Spec coverage: all seven behavioral/validation requirements map to Tasks 1–5.
- Interface consistency: `AssociationModel::concept_candidates` remains the source; Brain adds retrieval; prediction consumes evidence without authority.
- Failure coverage: bounded contradiction, sustained contradiction, indirect-path decay, state immutability, and provenance are explicit review targets.
- Proportion: the plan specifies interfaces and tests without prescribing implementation bodies beyond architectural constraints.
