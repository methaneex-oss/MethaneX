# MethaneX JARVIS Architecture

MethaneX is built as a provider-neutral cognitive system, not as a permanently embedded chatbot.

## Core loop

```text
Perception -> Intent/Event -> Memory Retrieval -> Planning -> Intelligence -> Guarded Action -> Observation -> Learning -> Memory
```

## Components

- `brain.py`: orchestration and event handling.
- `memory.py`: persistent tiered memory and retrieval.
- `planning.py`: goals, tasks, dependencies and execution state.
- `intelligence.py`: replaceable intelligence providers and confidence routing.
- `learning.py`: bounded experience-to-lesson proposals.
- `safety.py`: deny-by-default capability authorization.
- `voice.py`: STT/TTS contracts and wake-word development adapter.
- `cognitive_loop.py`: planning/reasoning/execution cycle.
- `config.py`: environment-based runtime settings.

## Important boundary

The current repository deliberately contains provider interfaces and a deterministic fallback. It does not claim that microphone STT, neural TTS, computer vision, autonomous model training, device control, or self-healing are implemented. Those require separate adapters and verification.

## Memory tiers

1. Identity — foundational, immutable-by-policy information.
2. Approved knowledge/preferences — information that has passed an approval policy.
3. Experience — observations and lessons that may be revised or decay.

The implementation must not silently promote untrusted experience into immutable identity.
