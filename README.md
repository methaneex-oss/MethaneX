# MethaneX — JARVIS Prototype

MethaneX is the clean prototype repository for the JARVIS system. This repository intentionally starts from an empty foundation rather than importing the older JARVIS repository files.

## Prototype goals

- Event-driven assistant core rather than a chat-box-only design.
- Pluggable perception, reasoning, memory, and action layers.
- No permanently embedded third-party AI model.
- Provider/model adapters can be added later without changing the core.
- Explicit safety boundaries around actions.
- Persistent experience memory with confidence and provenance.
- Fast local orchestration; external intelligence remains replaceable.

## Run

Requires Python 3.11+.

```bash
python -m methane_x
```

Then try:

```text
Hey Jarvis
status
remember that the prototype is called MethaneX
what do you remember
exit
```

## Test

```bash
python -m unittest discover -s tests -v
```

## Architecture

```text
Input -> Intent/Event -> Brain -> Memory/Reasoning -> Action -> Observation
                         |              |
                         +---- adapters/providers
```

The prototype is deliberately small. It establishes the core contracts that later voice, vision, device, web, coding, and external-model adapters can implement without rewriting the brain.
