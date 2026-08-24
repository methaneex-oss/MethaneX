# JARVIS Prototype

This repository contains the clean JARVIS prototype foundation. It intentionally starts from an empty foundation rather than importing the older JARVIS repository files.

## Prototype goals

- Event-driven assistant core rather than a chat-box-only design.
- Pluggable perception, reasoning, memory, and action layers.
- No permanently embedded third-party AI model.
- Provider/model adapters can be added later without changing the core.
- Explicit safety boundaries around actions.
- Persistent experience memory with confidence and provenance.
- Fast orchestration; external intelligence remains replaceable.

## Run

Requires Python 3.11+.

```bash
python -m jarvis
```

Then try:

```text
Hey Jarvis
Jarvis status
Jarvis remember that the prototype is called Jarvis
Jarvis what do you remember
exit
```

## Test

```bash
python -m unittest discover -s tests -v
```

## Architecture

```text
Input -> Perception -> Cognitive Core -> Memory/Reasoning -> Action
                         |                    |
                         +---- Planning ------+
                         |                    |
                         +---- Learning ------+
                         |                    |
                         +---- Verification -+
```

The prototype establishes core contracts so voice, vision, devices, web, coding, and external-model adapters can be added without rewriting the cognitive core.

## Naming

`jarvis` is the canonical Python package and CLI namespace. The older `methane_x` package remains as an internal compatibility namespace during the migration so existing tests and integrations do not break abruptly.
