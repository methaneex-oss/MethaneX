# JARVIS Agent Workbench

The repository uses multiple coding agents as parallel engineering contributors. They do not become part of JARVIS cognition.

## Work lanes

| Lane | Responsibility | Typical output |
|---|---|---|
| build | feature implementation | code + tests |
| qa | verification | tests, reproducers, reports |
| review | independent review | findings and required fixes |
| integration | branch/CI integration | conflict resolution, merge readiness |
| research | technical investigation | evidence-backed implementation brief |
| infra | CI/deployment/observability | workflows, adapters, deployment tooling |

## Parallelization rule

Agents should work on disjoint file surfaces. Shared files such as CMake manifests, public headers, and central runtime files require an integration owner.

## Definition of done

A task is merge-ready only when:
- implementation is present
- tests cover the new behavior
- existing relevant tests remain green
- sanitizer impact is checked where applicable
- no architectural boundary is violated
- the handoff contains branch/commit/test evidence

## Recommended JARVIS engineering loop

Research -> task specification -> parallel build/QA -> independent review -> integration -> CI -> merge.

This loop is for building JARVIS. It is not an implementation of JARVIS's cognitive core.
