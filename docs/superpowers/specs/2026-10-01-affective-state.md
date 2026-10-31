# Emergent Affective State Architecture

## Purpose

Add an internal valuation/state mechanism to JARVIS so experience can produce persistent, dynamic internal states that influence attention, memory, prediction, and action selection without hard-coded emotional scripts.

## Core principle

The system does not encode emotions as predefined behavior rules. It maintains continuous internal state variables and learning mechanisms. State changes are produced by observed conditions and outcomes, and those states can subsequently bias cognition.

## Mechanism

The subsystem receives normalized evidence from existing cognitive systems:

- prediction error and prediction confidence
- action reliability and verification outcome
- novelty and salience
- uncertainty/threat signals
- goal progress and unresolved goal pressure
- memory-derived recurrence/consolidation evidence

These signals are transformed into bounded valuation dimensions and updated through accumulation, decay, reinforcement, and regulation. No dimension directly maps to a fixed action.

## State representation

Use continuous bounded dimensions rather than a fixed list of named emotions. Initial dimensions:

- valence: aggregate positive/negative valuation
- arousal: activation/importance level
- uncertainty: unresolved model uncertainty
- agency: perceived effectiveness of recent actions
- goal_pressure: unresolved internally represented goal demand

Each dimension is a scalar in [-1, 1] where appropriate, with non-negative dimensions represented in [0, 1]. The representation must permit future dimensions without changing the event model.

## Dynamics

Each update combines current state with normalized evidence:

`new = decay * current + learning_rate * evidence + regulation`

Updates are bounded and finite. Repeated evidence accumulates; absent evidence decays toward a neutral baseline. Contradictory evidence can move the state in the opposite direction. No threshold is allowed to instantiate a named emotion or fixed behavior.

## Cognitive effects

Affective state is an input to existing mechanisms, not an independent decision-maker:

- attention receives arousal/uncertainty/goal-pressure signals;
- memory consolidation receives valuation and activation signals;
- prediction confidence and error interpretation can use state context;
- action selection receives state as one contextual feature alongside goals, threat, uncertainty, and learned strategies.

These effects must remain bounded so affect cannot bypass authorization, deterministic trade/action engines, or safety controls.

## Persistence and replay

State updates must be represented in the existing journal/event model so a fresh Brain can reconstruct equivalent state by replay. No hidden mutable state may be required for correctness.

The subsystem must tolerate old journals where affective fields are absent by using neutral defaults.

## Learning constraint

The system learns associations between internal state context and outcomes through existing developmental-learning mechanisms. It must not learn or persist rules of the form `state X -> always perform action Y`.

## Safety constraints

- No direct actuator access.
- No authorization bypass.
- No hard-coded emotional behavior tables.
- All values finite and bounded.
- Invalid/non-finite evidence is ignored or normalized safely.
- State cannot override explicit human authorization or action verification.

## Verification requirements

Tests must demonstrate:

1. neutral initial state;
2. prediction error changes state;
3. reliable successful action changes state in the opposite valuation direction where appropriate;
4. repeated evidence accumulates but remains bounded;
5. state decays without continuing evidence;
6. contradictory evidence reverses state direction;
7. journal replay reconstructs equivalent state;
8. affective state changes attention/memory/action-context signals without directly selecting an action;
9. malformed/non-finite evidence cannot poison state;
10. existing authorization and action-verification behavior remains unchanged.
