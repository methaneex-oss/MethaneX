# DF-02 Action Execution and Consequence-Persistence Contract Adjudication — 2026-11-27

**Scope:** exact candidate/donor action-execution source/API, Brain execution adapter, phase-7 test suite and donor action-consequence integration.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds observed-consequence capture and learning feedback; tests specify useful behavioral effects. Persistence failure is not reflected in the action result. Source/test inspection only; no execution.

## 1. Exact source blobs

| Path | Candidate | Donor |
|---|---|---|
| `action_execution.cpp` | `c2f8653eb755fa2790a88e49bc8b0b9c3077e439` | `af5bed6cec9ed1309b24ed3d50241fb4c0d33bff` |
| `brain_action_execution.cpp` | no candidate blob | `3b66bafb438cd28790e6f25611b96c86f1eff05c` (candidate branch has alternate `0c5fcb...`) |
| `action_execution.hpp` | `38ff7033e7621db8f05cc1edc4bf59cb899ccdd3` | `04c73d02bdd4e1154be142dfeb024fc07ad432f8` |
| `action_execution_phase7_suite.cpp` | `b4a0060596c91c67080ac0a2db324f720d760fbe` | `db11ac95d26a97b01dfeb67cfb85194dc284ffb8` |

The artifact also contains two historical Brain execution adapter blobs, three ActionExecutor source blobs, four header blobs and three phase-7 test blobs. Full source lineage/authority remains open.

## 2. Execution lifecycle and candidate/donor delta

Both executor versions authorize before invoking the execution callback, distinguish rejected/prepared/executed/verified/failed/rolled-back states, catch execution/verification/rollback callback exceptions and optionally rollback after a failure.

Donor adds:
- records the expected consequence in the result even before any execution attempt;
- accepts a separate optional consequence observer, only after the action callback reports executed;
- clamps finite observed consequence to [-1,1] and derives consequence error from observed minus expected (bounded [-2,2]);
- keeps consequence observation independent from verification status: a verification failure or successful rollback can still have a real consequence that must be learned;
- Brain integration issues a prediction for the expected consequence before execution, binds it to exact prediction sequence/context/action, persists the action outcome, derived affective evidence and learning evidence, then resolves the exact prediction only when an actual consequence was observed.

The donor test asserts verification-failure rollback, observed consequence despite a verified action, expectation/actual/error, learned developmental consequence changing the subsequent cycle choice, and reconstruction preserving learned action preference. Donor action-consequence integration further tests an unobserved outcome (not a numeric zero), partial verification failure with a real observation, and persistence/replay.

## 3. Material persistence/return-contract gap

`Brain::execute_action` returns the `ActionExecutionResult` produced by the executor regardless of whether journal persistence succeeds. The result's status may be `verified`, `executed` or `rolled_back`; but the Brain adapter appends the `action_outcome` event and only proceeds with learning/affective updates if append returns a nonzero sequence. It does not expose a separate persistence status/failure to the caller.

Consequently, if the physical action executes/verification succeeds but the journal append fails, the returned result still reports execution success while the prediction remains unresolved and outcome/learning evidence may be lost. Subsequent affective/learning event appends are separate and can partially fail after the authoritative outcome was recorded. No transactional journal batch or explicit partial-persistence contract is demonstrated.

This is source-derived; tests do not inject journal write failures, append failure between event types, or recovery after an action succeeded but evidence persistence failed.

## 4. Test limits

The phase-7 test source asserts:
- authorization rejection never executes;
- successful verification has no rollback;
- execution failure reports failure and no execution;
- verification failure invokes rollback and reports rolled-back state;
- expected/actual consequence and error values are correct;
- negative observed consequence updates affective/developmental evidence and changes the next planning choice;
- persisted learning changes behavior after reconstruction.

It does not test authorization/execute/verify/rollback/observer exceptions, invalid/nonfinite observer values, rollback failure, queue/cancellation/timeouts, real external adapter, action idempotency, concurrent execution, or journal write failure. These sources were inspected, not run.

## 5. Five review lenses

1. **Semantic:** execution/verification/rollback are distinct from observed consequence; donor consequence feedback is a material addition.
2. **Build/test:** exact donor test contracts inspected; no native build/CTest.
3. **Trust/authority:** authorization happens before callback; no proof of adapter safety. Result status does not indicate evidence-persistence success.
4. **Cognition:** observed consequence can influence later action choice and replay in synthetic fixture; external execution and observation reliability remain unverified.
5. **Hostile review:** no claim that action tests executed or that successful action equals persisted learning; partial-write and exception gaps retained.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor executor source/API | Compared |
| Brain action-execution adapter | Source-inspected |
| Consequence-feedback behavioral test | Source-inspected |
| Journal append failure/partial persistence contract | Gap identified |
| Exception, rollback failure, idempotency/concurrency/adapter tests | Open |
| Full owner/consumer/authority/retention | Open |
| Native test execution | Not performed |
| DF-02 | OPEN |

Action execution remains **OPEN / NO AUTHORITY DECISION**. No implementation selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Builder reachability recheck — donor action-consequence integration suite (2026-11-28)

A basename-aware CMake recheck confirms the donor-only integration test is registered; the prior full-path reference scan did not surface it because CMake names the source by basename rather than repository-relative path.

Exact evidence:
- Test source: core/cpp/tests/brain_action_consequence_integration_suite.cpp, donor blob 7616082579d53e3579cae8e87895bdb3dadba66f (316 lines, 95 assert expressions). Two historical alternate blobs are 4fb2c5377034f41b6190cf49c700ac9364fe182a (289 lines / 85 asserts) and 93fb8bbdde9cd7fbb28becfdebc4d01a7eae4e3e (293 lines / 88 asserts). No candidate blob exists.
- Candidate core/cpp/tests/CMakeLists.txt blob dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3 does not register the integration test.
- Donor core/cpp/tests/CMakeLists.txt blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 registers jarvis_brain_action_consequence_integration_suite at lines 187–189 and CTest at line 285.
- Donor core/cpp/CMakeLists.txt includes CTest and add_subdirectory(tests) under BUILD_TESTING at lines 79–81.
- The separately scoped action_execution_phase7_suite is registered in both candidate and donor CMake; donor target lines 76–78 / CTest line 248, candidate target lines 70–72 / CTest line 162.
- The 95-assert integration contract covers: negative surprise increasing prediction-error attention; unobserved/NaN consequence not being treated as zero or learned as neutral; explicit unknown optional consequence; observed consequence surviving verification failure; context preservation in the authoritative action_outcome event; strategy changes on the next cycle; persistence of affect/attention/strategy/forecast across restart; and resolution of a world-variable forecast by the next observation.

This corrects the reachability record: the donor integration suite is a registered CTest target, not an orphan. It remains source-inspected only. No CI workflow runs were returned for donor frozen HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25, and no native build/CTest was executed for it in this run. Therefore 95 assertions are an executable test contract in the donor build graph, not passing test evidence.

 
### Historical alternate-branch execution of the action-consequence integration suite

The donor action-consequence source/test/CMake blobs are also present unchanged on historical alternate branch fix/evolution-authenticated-replay-final-20261030 at HEAD e737cae7f907696ef787a4e85b0dee3a739d71b1. In that branch, brain_action_consequence_integration_suite.cpp blob 7616082579d53e3579cae8e87895bdb3dadba66f and tests/CMakeLists.txt blob cbfd1fde52fffa6eeac025da2b7ddcb5ab493261 are built and registered. CTest #64 passed in:
- Brain CI #1826 native-brain and sanitizer jobs;
- JARVIS Brain Tests #975 brain and sanitizer jobs;
- Brain ThreadSanitizer #957 TSAN job.

All five jobs reported 71/71 tests passed. This is executed behavioral evidence for the exact test and CMake blobs on the e737cae7 alternate branch, not on frozen donor HEAD c1da222 or current PR #203. The donor c1da222 itself returned no workflow runs/status. The test uses deterministic callback fixtures; it does not validate real external adapters or production hardware.
