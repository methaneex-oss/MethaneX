# DF-02 Self-Test Diagnostic Validity and Healing-Transaction Adjudication — 2026-11-27

**Scope:** donor-only self-testing model, Brain self-test/heal adapter and phase-9 test.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** self-test/heal APIs exist but the current diagnostic suite is weak; the phase-9 test does not verify the repaired condition, and recovery persistence is not reflected in the return result.

## 1. Exact refs

- `core/cpp/include/jarvis/core/self_testing.hpp`: donor-only `3dee193f773b068cf2c67fce7afeba04981f4fd4`.
- `core/cpp/src/self_testing.cpp`: donor-only `30b5af95ba1785120a10097767e28a9f3b67a8ce`.
- `core/cpp/src/brain_restored_api.cpp`: donor blob `7155d4d9c8eef527836fb79bf901aa32ddbae38`.
- `core/cpp/tests/self_testing_healing_phase9_suite.cpp`: donor `1e0c13c6de2843771d63389ddc338617a04af632`.
- CMake target `jarvis_self_testing_healing_phase9_suite` is registered.

## 2. Diagnostic coverage

Brain `self_test()` builds six checks:
1. memory event sequence monotonic/nonzero;
2. cycle >= events_seen or zero events;
3. “journal-readable” returns true unconditionally;
4. “goal-state-readable” returns `!goals.empty() || true`, unconditionally true;
5. self-model health bounded;
6. cognition novelty/attention/threat bounded.

The diagnostic runner catches check exceptions and records generic failure. Empty check list reports healthy (zero failures). The six checks do not validate journal integrity/metadata/checksum, Brain replay equality, prediction/goal dependency invariants, capability/action/evolution consistency, or concurrency.

## 3. Healing contract

`SelfTestingModel::heal` requires component and repair/verify callbacks, executes repair then verification, and returns Recovered if both booleans true. It does not catch callback exceptions, rollback partial repair, isolate callbacks, enforce timeout, or record diagnostic evidence.

Brain `self_heal` calls the model and, on Recovered, invokes `recover(component,1.0)` to append a resilience-recovery event; the boolean result is ignored. Therefore a repair can return Recovered even when recovery-event persistence fails and resilience state is not restored. The generic callback can mutate arbitrary captured state outside Brain synchronization.

## 4. Test evidence

Phase-9 test:
- checks self-test has at least six checks and zero failures;
- observes degraded database health and sees recovery options;
- repair callback only confirms the component string and sets a Boolean;
- verify callback reads capability pointer but discards it, then returns component string plus repair Boolean—it does **not** assert health actually recovered;
- expects Recovered and repaired flag;
- reconstructs Brain and verifies recovery options no longer include database and self-test is healthy.

The test verifies callback sequencing and persisted recovery event, not repair correctness or failed-persistence behavior. Tests inspected, not executed.

## 5. Five review lenses

1. **Semantics:** self-test checks and callback healing contract mapped.
2. **Build/test:** donor phase-9 test and CMake registration confirmed; no native execution.
3. **Integrity:** two diagnostic checks are tautologies; repair verification is weak; recover append status ignored.
4. **Autonomy/safety:** self-heal is caller-provided in-process callbacks, not autonomous diagnosis or safe repair.
5. **Hostile review:** “healthy” and “recovered” are qualified to actual checks; no verified repair claim.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| SelfTestingModel source/header | Verified |
| Brain self-test/heal adapter | Inspected |
| Phase-9 test/CMake | Inspected |
| Diagnostic check validity | Gaps |
| Repair outcome verification | Gap |
| Recovery-event persistence result | Gap |
| Exception/partial-repair/rollback tests | Open |
| Native tests | Not performed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Self-test/healing remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
