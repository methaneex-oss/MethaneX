# MethaneX Coding-Agent Contract

## Mission
Build JARVIS as a real, testable, polyglot software system. Coding agents work on infrastructure, tooling, tests, integrations, documentation, CI, adapters, and other non-core surfaces unless a task explicitly delegates core cognition work.

## Non-negotiable
- No hard-coded intelligence, phrase-to-action maps, fake learning, or placeholder cognition.
- Do not modify JARVIS core cognition merely to make an external agent task easier.
- Do not claim completion without compilation, relevant tests, and repository verification.
- Preserve C++20, CMake, CTest, warnings, sanitizers, and deterministic tests.
- Prefer small, reviewable commits and isolated branches.
- Never overwrite another agent's work. Rebase or coordinate through GitHub when necessary.

## Agent roles
- Builder: implements the assigned feature or integration.
- Test/QA: adds or strengthens tests and reproduces failures; does not silently change production behavior to make tests pass.
- Reviewer: inspects diffs for correctness, architecture, security, regressions, and missing tests.
- Integration agent: resolves branch/CI conflicts and prepares merge-ready changes.
- Research agent: investigates libraries, APIs, models, and implementation options and records evidence.

## Handoff protocol
Every agent handoff must state:
1. task scope
2. files changed
3. tests/commands run
4. failures and unresolved risks
5. commit/branch
6. exact next action

## JARVIS boundary
External agents may build the machinery around JARVIS: connectors, CI, deployment, test infrastructure, adapters, developer tools, observability, benchmarks, and orchestration. The cognitive core remains governed by the repository's architecture and explicit task assignment.
