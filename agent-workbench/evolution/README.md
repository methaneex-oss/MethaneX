# JARVIS Evolution Agent Workbench

This directory is the controlled work area for coding/building agents working on JARVIS evolution.

## Scope

Target repository: `methaneex-oss/MethaneX`

Agents working from this workbench are working on **JARVIS itself**, specifically the evolution subsystem. They must not modify unrelated projects or repositories.

## Isolation rule

Evolution work must remain isolated from `main` until it has passed the repository's normal review, build, test, sanitizer, and CI gates.

Preferred workspace identity:

`jarvis-evolution-sandbox`

Preferred branch family:

`agent/evolution/*`

The current orchestration branch for this workbench is:

`feat/agent-evolution-sandbox`

## Agent collaboration

Agents communicate through the engineering message bus. Every message should carry:

- run ID
- workspace ID
- sender
- recipient
- correlation ID
- message type

Agents should exchange evidence and artifacts rather than relying on implicit shared assumptions.

## Current mission

Continue the existing evolution implementation. Do not recreate existing evolution components.

Priority order:

1. inspect the current evolution implementation;
2. complete the autonomous evolution lifecycle integration;
3. strengthen statistical evaluation;
4. strengthen transactional adoption;
5. complete canary/monitoring/rollback lifecycle;
6. add durable evolution history/restart reconstruction;
7. connect normalized cognitive evidence to evolution opportunities;
8. feed learned evolution outcomes back into strategy/decision mechanisms.

Do not implement unrestricted self-modification or direct production mutation.
