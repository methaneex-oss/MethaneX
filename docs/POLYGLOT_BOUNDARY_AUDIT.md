# Polyglot Boundary Audit

This audit records the ownership cleanup performed after the autonomous evolution work.

## Removed from C++

- `process_isolation.cpp`
- `process_isolation.hpp`
- `process_isolation_suite.cpp`
- `process_isolation_syscall_suite.cpp`

These implemented OS-level process isolation, privilege handling, resource limits and Linux syscall filtering inside the cognitive core. That is a security/runtime responsibility, not cognitive reasoning. The evolution sandbox already accepts an injected `CandidateExecutor`, so removing the unused concrete backend does not remove the core's execution contract.

## Rust boundary

Rust now owns the security policy contract through `runtime/rust/src/security.rs`. The policy layer fails closed when a required isolation capability is unavailable. The actual host-specific enforcement backend will be attached behind this boundary rather than reintroducing OS security code into C++.

## Rust duplication removed

The previous Rust `BrainRuntime` and `CognitiveState` duplicated the C++ cognitive substrate. They were removed. Cognitive state remains owned by the native brain; Rust is reserved for safety-sensitive runtime responsibilities.

## Still intentionally in C++

- cognitive state and world representation
- deterministic evidence and adoption gates
- evolution orchestration
- trial coordination
- evolution history/provenance
- lifecycle control
- rollback/canary coordination
- capability contracts

These are core cognitive substrate responsibilities and do not become Python/Rust merely because another language could implement them.

## Future external-learning boundary

Python should be introduced when the evolution learner needs scientific/ML/optimization tooling. The current deterministic history and safety machinery stays native. We should not replace deterministic C++ policy with Python just to satisfy a language rule.
