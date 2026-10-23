# JARVIS Developmental World

This is a runnable, controlled environment for observing JARVIS's existing cognitive and developmental mechanisms together. It is deliberately a small first world, not a claim that the brain is complete.

## World rules

- JARVIS observes route conditions, bridge status, and visibility.
- It chooses between `good-route` and `bad-route`; the environment does not label the correct action in the observation.
- The environment reports the consequence of each executed action.
- Episodes 0–7 use clear conditions. Episodes 8–23 reverse the consequences, so the route that was previously useful becomes harmful.
- JARVIS's journal records the experience. A supplied journal path lets you inspect persistence across separate runs.

## Build and run

From the repository root:

```sh
cmake -S core/cpp -B build/jarvis -DJARVIS_BUILD_EXAMPLES=ON -DBUILD_TESTING=ON
cmake --build build/jarvis --target jarvis_developmental_world
./build/jarvis/examples/jarvis_developmental_world
```

For a specific journal path:

```sh
./build/jarvis/examples/jarvis_developmental_world ./jarvis-developmental-world.bin
```

The no-argument run starts from a clean temporary journal so the first experiment is repeatable. Passing a path reuses that journal and allows you to inspect how prior experience influences a new run.

## What to watch

The output prints each episode, the observed condition, selected action, and observed consequences, followed by learned strategy values. The intended behavior is not a hard-coded sequence: the initial preference should emerge from feedback, and contradictory outcomes should change the local preference in the flooded context while preserving the useful strategy for the clear context.

This environment is a controlled starting point. It does not yet model open-ended natural-language perception or arbitrary real-world actions. Those should be added only after this end-to-end loop is observable and reliable.
