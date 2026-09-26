# JARVIS Concept → Context → Prediction Design

## Goal

Make experience-derived concept hypotheses usable by JARVIS's cognitive context and prediction mechanisms without turning learned concepts into unquestionable facts or bypassing existing architecture.

## Scope

This design extends the existing association/concept machinery in `core/cpp` and its existing Brain-facing interfaces. It does not introduce a second brain, second memory system, independent concept store, or direct concept-to-action authority.

## Behavioral model

```text
experience
  ↓
association evidence
  ↓
concept hypothesis
  ↓
confidence / contradiction state
  ↓
relevant contextual evidence
  ↓
prediction
  ↓
outcome
  ↓
updated evidence
```

A concept is evidence with uncertainty, not truth. Repeated support increases usable confidence; contradictory evidence reduces it. Competing hypotheses remain possible. Prediction records must retain provenance so later learning can distinguish useful from misleading concepts.

## Design constraints

- Preserve the existing C++ cognitive architecture.
- Reuse the existing `AssociationModel` and `Brain`; do not create parallel cognitive stores.
- No hardcoded semantic categories.
- No direct concept-to-action execution path.
- Derived concepts must remain distinguishable from direct observations.
- Indirect context must decay with path strength and not become a direct fact.
- Contradictory evidence must be represented explicitly.
- Prediction must remain falsifiable through subsequent outcomes.
- Deterministic mechanics are acceptable; semantic interpretation must arise from evidence rather than phrase-specific rules.

## Proposed interfaces

Extend `ConceptCandidate` with evidence state sufficient to expose uncertainty and contradiction without pretending the candidate is a semantic truth. Add a Brain-level retrieval method that returns concept candidates relevant to a supplied observation/context key.

The retrieval path should use existing association traversal rather than a new database. The result should be a ranked set of hypotheses with coherence/support/contradiction information and explicit provenance.

Prediction should consume these hypotheses as contextual evidence. It must not silently promote a concept hypothesis into a belief. A prediction that used a concept should retain the concept members and evidence strength needed for later outcome comparison.

## Validation requirements

Tests must prove:

1. repeated evidence produces a usable concept candidate;
2. contradictory evidence lowers its usable strength;
3. an exception does not immediately erase a learned hypothesis;
4. sustained contradiction removes the hypothesis from the trusted retrieval view;
5. indirect context remains weaker than direct association evidence;
6. prediction can consume a learned hypothesis without changing the authoritative belief state;
7. prediction provenance survives until outcome evaluation;
8. no semantic label is injected by the implementation.

## Non-goals

- autonomous consequential actions based solely on newly learned concepts;
- self-modifying source code;
- replacing external models;
- implementing a complete world model in this change;
- creating a generic ontology or manually curated taxonomy.

## Success criterion

JARVIS demonstrates an end-to-end, observable path in which a repeated experience-derived abstraction changes contextual prediction, while uncertainty and contradiction remain visible and subsequent outcomes can revise the abstraction.
