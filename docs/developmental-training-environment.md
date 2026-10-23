# JARVIS Developmental Training Environment

## Purpose

This is the first controlled environment for observing whether the existing JARVIS brain can learn from action consequences, revise a context-specific belief when conditions change, and retain the resulting learning after restart.

It is a simulated environment, not a claim that JARVIS has human-like consciousness or general intelligence. The goal is to test a real developmental loop using the existing cognitive runtime rather than a separate hard-coded learner.

## Environment

The integration scenario lives in `core/cpp/tests/developmental_training_environment_suite.cpp` and runs through `CognitiveRuntime`, `CognitiveCycle`, the existing action adapter, brain memory, and developmental strategy mechanisms.

The environment presents observations containing:
- `route_condition`: clear or flooded;
- `bridge_status`: open or closed;
- `visibility`: clear or poor;
- the current episode and task.

It offers two executable actions, `good-route` and `bad-route`. Their names are labels, not instructions supplied to the brain about which choice is currently best. The environment returns a consequence of +1 or -1 based on the action and current conditions.

### Stages in the current trial

1. **Infrastructure failure:** the executor is unavailable. No route consequence is observed. This checks that an execution failure is not mislearned as evidence about route quality.
2. **Initial experience:** in the `navigation/route-selection` context, `good-route` has positive consequences and `bad-route` has negative consequences. The brain should learn a useful preference.
3. **Contradiction:** in the related `navigation/route-variant` context, conditions reverse. Early decisions can reflect prior learning, but observed consequences should cause a context-specific revision.
4. **Restart:** reconstruct the brain from the persistent journal and probe the original context, changed context, and a related context without direct experience.
5. **Transfer boundary:** probe an unrelated context to ensure navigation learning does not dominate unrelated choices.

## Run it

From the repository root, configure and build the C++ core, then run the targeted CTest:

```sh
cmake -S core/cpp -B build/jarvis-core -DBUILD_TESTING=ON
cmake --build build/jarvis-core --target jarvis_developmental_training_environment_suite -j2
ctest --test-dir build/jarvis-core -R '^jarvis_developmental_training_environment_suite$' --output-on-failure
```

The test prints episode-by-episode choices and observed consequences. Its assertions are behavioral acceptance criteria, not just checks that events were appended.

## What passing means—and does not mean

A passing run is evidence that this particular deterministic scenario can exercise action outcomes, context-specific strategy learning, contradiction handling, and replay. It does **not** establish broad autonomous learning, sensory grounding, robust exploration, or human-like cognition.

## Next experiments

After this baseline is stable, add one capability at a time to the environment while retaining the same end-to-end loop:

- partial or noisy observations, so the brain must manage uncertainty;
- a new route layout with different action labels, to test transfer beyond name matching;
- delayed consequences, to test temporal credit assignment;
- multiple competing goals and limited resources;
- repeated trials with varied seeds and quantitative measurements of learning speed, reversal time, and regression rate.

Avoid baking the correct choice into the brain or test assertions. The environment may define ground truth and consequences; the brain must choose actions and update its own internal state through the existing cognitive mechanisms.
