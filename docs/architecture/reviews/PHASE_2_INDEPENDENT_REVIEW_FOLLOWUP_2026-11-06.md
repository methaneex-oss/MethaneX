# Independent Review — Phase 2 Whole-Brain Capability-to-Source Integration Map (Follow-up)

**Review date:** 2026-11-06  
**Repository:** `methaneex-oss/MethaneX`  
**Primary report:** `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md`  
**Primary PR:** [#179](https://github.com/methaneex-oss/MethaneX/pull/179)  
**Comparison PR:** [#180](https://github.com/methaneex-oss/MethaneX/pull/180)  
**Review type:** Independent source/specification/test/governance review; documentation-only publication  
**Review baseline:** Exact repository state listed below

## 1. Verdict

**REVISE — the Phase 2 report is a technically substantial and generally careful investigation, but it is not yet sufficiently complete or reliable to accept as the final Phase 2 integration map.**

The report's central architecture conclusions are supported by the inspected evidence: the main CognitiveCycle is a bounded single-pass path; retrieved memory is not a premise to its reasoning call; the reasoning result is not used by later stages in that function; the main perception pipeline is not connected to that production path; and the current main learning mechanisms do not establish the full BM-09 developmental lifecycle. The report also correctly separates main from donor code, test registration from execution, and source-derived failure paths from reproduced incidents.

This review identifies two additional mainline persistence/state-consistency findings that are not adequately represented in the current finding register:

1. Main Brain goal lifecycle methods mutate the in-memory GoalModel before attempting to append the corresponding event. If the append fails, the method returns failure but leaves the live Brain mutated; restart/replay cannot reconstruct that unjournaled transition.
2. The journal rollback and malformed-tail repair weaknesses described as donor finding P2-I-014 also exist in the audited main baseline. Main's startup repair path is weaker in one respect: it truncates the malformed tail without first quarantining it, and ignores the truncation error.

These are conditional filesystem-failure paths, not claims of reproduced incidents. They matter because the report's own core question is whether persistent experience and future computation remain coherent across failure and restart.

**Phase 2 is not accepted complete. Gate A is not cleared by this review. Gate B is not assessed or cleared. No implementation baseline, donor approval, merge, or runtime implementation authorization is granted.**

## 2. Exact repository state and scope

The following live refs were re-fetched for this review:

| Item | Verified state |
|---|---|
| `main` | `1273ddbcd0087d189e01388ded2d362fb1e058d2` |
| PR #179 | Open, draft, unmerged; HEAD `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`; base branch `docs/jarvis-project-governance-rules-20261105` at `39fe09dcf13496f5f0005ccf3f00739303e29f88` |
| Primary report blob | `cc772cf571a7f9bf3ee3df2c1e392a8a392903a3`; 3,187 lines |
| PR #180 | Open, draft, unmerged; HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`; base branch `spec/brain-mechanism-specification-20261103` at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` |
| Accepted mechanism specification | `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`; blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1` |
| PR #97 donor | Inspected reference HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`; remains a separate donor line |
| PR #178 governance document | Branch head `39fe09dcf13496f5f0005ccf3f00739303e29f88`; document blob `e4315956cfb1ed075b508af3053601fed345f0a5`; explicitly proposed, not accepted governance |

The complete 3,187-line primary report was fetched and read, including the BM-01–BM-12 map, cross-mechanism findings, evidence sections, finding register, closure plan, ownership handoffs and prior review-response sections. The PR #180 report and changed-file metadata were also inspected.

The PR #179 and PR #180 review-submission collections were empty at the time checked. This review is therefore a new review record, not an assumption that either PR already has an independent review.

The PR #178 governance document is explicitly marked as a proposed baseline pending owner review. Its evidence and testing standards are used as a working review rubric; this review does not promote that document to accepted authority. The accepted PR #174 mechanism specification remains the requirements reference at its exact historically accepted revision, subject to its recorded open correction obligations.

### Verification limits

- The current PR #179 HEAD has a successful GitHub Actions `Native Brain Build` job: run `42189761736`, job `127798604055`, exact head `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`. The job steps are Configure and Build; **there is no CTest step**. This is exact-head build evidence only, not a test pass.
- No local build, CTest run, sanitizer, runtime experiment, filesystem fault injection, or end-to-end test was executed by this reviewer.
- Source conclusions below are source-derived unless explicitly stated otherwise. Operational impact under injected failures remains to be reproduced by the Independent Tester.

## 3. Findings

### R1 — Main goal lifecycle mutates live cognitive state before journal acknowledgement

**Severity:** Medium (provisional)  
**Confidence:** High for source ordering; Medium for operational impact until fault injection  
**Classification:** Mainline persistence/state-consistency defect; new finding

**Affected baseline:** main `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Source identities:**
- `core/cpp/src/brain.cpp` — blob `e9f3758fcc9c0e89b7280ce376db9033d547682d`
- `core/cpp/src/goals.cpp` — blob `778a829de8314e83b095af2f2c2a6b83baa769f4`
- `core/cpp/src/memory.cpp` — blob `ba72a897306d4761246d0deab2fbab37c49d372f`

**Direct source evidence**

At main `brain.cpp` lines 157–161, the wrappers perform the GoalModel transition before calling `memory_.append`:

- `Brain::activate_goal`: calls `goals_model_.activate(id)`, then appends `goal_activate`.
- `Brain::update_goal_progress`: calls `goals_model_.update_progress(id, bounded)`, then appends `goal_progress`.
- `Brain::complete_goal`: calls `goals_model_.complete(id)`, then appends `goal_complete`.
- `Brain::abandon_goal`: calls `goals_model_.abandon(id)`, then appends `goal_abandon`.
- `Brain::set_goal_priority`: calls `goals_model_.set_priority(id, bounded)`, then appends `goal_priority`.

The GoalModel methods mutate their stored `Goal` directly: `goals.cpp` lines 26–57. In contrast, main `Memory::append` at `memory.cpp` lines 119–128 returns zero immediately when `persist(event)` fails; it does not append the event to its in-memory continuity or metadata vectors.

Therefore, when persistence fails after one of those GoalModel mutations:
1. the wrapper returns `false`;
2. the in-memory GoalModel has already changed;
3. no corresponding event is committed to Memory;
4. a subsequent cycle in the same process can observe/use the changed goal state;
5. a reconstructed Brain cannot replay the missing transition and can return to the prior goal state.

This is not the same as donor P2-I-036. P2-I-036 concerns the donor's two-event `goal_progress(1.0)` / `goal_complete` protocol. R1 concerns main's single-event wrappers and their mutation-before-append ordering.

**Test coverage checked**

Main `core/cpp/tests/brain_failure_suite.cpp` lines 21–33 injects a journal-parent failure and verifies that `Brain::observe` does not acknowledge or mutate event counters/memory. It does not exercise any goal lifecycle wrapper under append failure. The target is registered in `core/cpp/tests/CMakeLists.txt` lines 10–12 and 142. The existing test therefore does not close this goal-state failure path.

**Required correction / acceptance evidence**

1. Establish a single explicit commit protocol for every GoalModel mutation: either persist-before-apply with validation/preparation that cannot fail after append, or apply-with-verified-compensation and a structured failure state. Do not merely reorder code without considering event replay and duplicate IDs.
2. For activation, progress, completion, abandonment and priority update, inject an append failure after the attempted transition.
3. Assert the method result, live GoalModel state, Memory sequence/content, Brain counters and reconstructed state all agree.
4. Include a successful append control for each transition.
5. Retry the same logical operation after failure and prove idempotent, deterministic recovery.
6. Review other Brain wrappers for the same mutation-before-append pattern (including capability isolation/recovery and resilience transitions); record each disposition rather than assuming the goal methods are unique.

### R2 — Mainline journal rollback and startup tail-repair errors are unchecked; P2-I-014 is under-scoped

**Severity:** Medium (provisional)  
**Confidence:** High for source-level behavior; Medium for data-loss sequence until fault injection  
**Classification:** Mainline persistence failure-contract finding; extends P2-I-014

**Affected baseline:** main `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Source identity:** `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`

The report's §32, lines 2472–2511, documents P2-I-014 against donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. The central append rollback weakness also exists in the audited main baseline:

- Main `Memory::persist`, lines 192–212, flushes the stream and checks the stream state. If the write/flush fails, it calls `std::filesystem::resize_file(journal_path_, original_size, rollback_error)` but never checks or surfaces `rollback_error`.
- Main `Memory::load`, lines 131–158, scans to the last valid record and calls `resize_file(journal_path_, valid_end, error)` when a malformed suffix exists. It does not check the result after that call and does not quarantine/preserve the suffix before truncation.
- Main `Memory::append`, lines 119–128, has no poisoned/recovery-required state. If `persist` returns false, it returns zero; if rollback failed and left a malformed suffix, later appends are not prevented by an explicit journal-health state.

The donor implementation at `c1da222e...` has a quarantine-copy step before startup truncation (`memory.cpp` lines 40–62), but still does not inspect the final truncation error. Main's simpler load path does not perform that quarantine step.

This means P2-I-014 is not solely a donor concern. The same append rollback issue, and an unchecked startup-repair operation, are present on main. Under a failed rollback/truncation, later acknowledged records may be appended behind an unreadable tail and then be discarded from the recovered in-memory prefix on restart. This is a conditional source-derived failure path, not a reproduced incident.

**Required correction / acceptance evidence**

1. Extend P2-I-014's affected-revision matrix to include main and distinguish main's load behavior from donor quarantine behavior.
2. Define the journal's failure state. If rollback or tail repair cannot be verified, Memory must not accept further appends until a recovery operation establishes a valid append point.
3. Make rollback and repair errors observable to the owning Brain/caller; do not silently continue with uncertain journal integrity.
4. Add deterministic fault injection for partial event write, append rollback failure, malformed-tail quarantine/copy failure (donor), and startup truncation failure (main and donor).
5. After each injected failure, attempt another append, restart, and verify that every acknowledged event is recovered exactly once and that no unacknowledged event is presented as committed.
6. State the intended durability guarantee precisely. Stream flush is not equivalent to stable-storage durability after power loss or kernel crash.

## 4. PR #180 comparison

**Classification: materially overlapping and competing duplicate deliverables, not independent complementary maps that should both be merged as-is.**

Verified facts:

- PR #180 adds the same path as PR #179: `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md`.
- PR #180's report is 310 lines and is an initial evidence batch. PR #179's current report is 3,187 lines and contains extensive later tracing, failure-path analysis, test/CI provenance and closure handoffs.
- PR #180 is based on the specification branch at `0811a59e...`; PR #179 is based on the proposed governance branch at `39fe09dc...`.
- A live compare of PR #180 HEAD as base and PR #179 HEAD as head reports `diverged`, with common merge base `1273ddbcd0087d189e01388ded2d362fb1e058d2`: PR #179 is 81 commits ahead and 13 commits behind PR #180 in that comparison direction.
- Both PRs are open, draft and unmerged. Neither has a submitted review record at the time checked.

The initial claims substantially overlap: memory is not supplied to the main reasoning premises; the reasoning result is not used downstream in the inspected cycle; the main reasoning engine is narrow; goal creation APIs do not prove experience-acquired candidate-goal formation; and causal-link learning requires stronger causal evidence. PR #179 preserves these findings and expands the evidence scope substantially.

**Disposition:** PR #179 is the more developed working report. PR #180 remains a separate historical branch/report and should be preserved until the Project Director decides whether to close it as superseded, retain it as a parallel research record, or request reconciliation. Do not merge both additions to the same path without an explicit content/ancestry reconciliation. This review does not make that Project Director decision.

## 5. Assessment of the report's principal conclusions

### Supported by the inspected evidence

1. **Main perception integration gap.** Main `CognitiveCycle::run` at `core/cpp/src/cognitive_cycle.cpp` lines 27–44 calls `Brain::observe`, retrieves memory and constructs reasoning premises from beliefs/causal links. It does not invoke `PerceptionPipeline::process` or `RepresentationEngine::normalize`. Main compiles and registers a standalone perception utility/test; that does not establish a production caller. PR #97 has a separate donor call path.
2. **Memory/reasoning disconnect and reasoning non-consumption.** The main cycle does not pass retrieved memories into `ReasoningProblem`; its reasoning result is not consumed by later code in the inspected `run` function.
3. **Narrow reasoning scope.** The inspected main engine implements keyed-value consistency and bounded causal-link traversal. It is not evidence of the complete BM-12 specification.
4. **Candidate-goal formation distinction.** A GoalModel API and supplied-goal selection are not evidence of an experience-derived candidate-goal generator.
5. **Causal inference caution.** The inspected main causal model forms links from changed belief snapshots and other current values. Source presence does not establish intervention semantics, confounder control or counterexample handling.
6. **Main/donor boundary.** PR #97's richer perception, affective and action/consequence paths must not be attributed to main or treated as an approved port.
7. **Learning evidence limits.** The report is correct to state that DLT-002 run #8 is at earlier donor commit `82c49a75bd30de2962879f044776f4bf2391970a`, not current donor HEAD; the experiment did not run matched learning-disabled or transfer-disabled controls. The observed reversal and first-choice held-out probe are evidence consistent with adaptation/transfer in that harness, not a causal estimate of learning benefit or broad generalization.
8. **Recovery and execution findings.** P2-I-023, P2-I-029, P2-I-030, P2-I-035, P2-I-036, P2-I-037 and P2-I-038 describe distinct boundaries. Their source-derived status should remain separate from reproduced incident status.

### Severity and reasoning judgement

The report generally handles severity and confidence conservatively. In particular, keeping the host authorization lifecycle P2-I-038 as an unresolved system-boundary question rather than asserting an exploitable vulnerability is justified by the absence of the deployment host from the inspected repository. The conditional scheduler starvation and feedback-loss risks are also correctly not described as reproduced incidents.

The main correction needed is not to inflate severity across the board. It is to ensure the report's persistence map covers mainline mutator ordering and mainline journal failure behavior, not only the donor's later code paths.

## 6. Required corrections and acceptance criteria

The following are required before the report can be accepted as a reliable Phase 2 map:

| ID | Required action | Evidence required |
|---|---|---|
| R1 | Add the main goal mutation-before-append finding and inspect sibling Brain mutators | Source-backed transition table; deterministic append-failure tests; live/replay/retry equivalence |
| R2 | Extend P2-I-014 to the main baseline and distinguish main vs donor repair semantics | Exact main/donor source anchors; injected rollback and tail-repair failures; restart proof |
| R3 | Preserve PR #179/#180 as a single-path conflict requiring Project Director disposition | Explicit decision on #180; no silent branch deletion or duplicate-path merge |
| R4 | Retain the report's current distinction between Phase 2 mapping completion and capability/gate acceptance | Explicit statement that a complete map can still contain open technical defects, and that Gate A/Gate B require separate authority/evidence |

Additional acceptance checks remain valid from the report and are not waived by R1/R2:

- Complete the acquisition/perception production boundary and contextual language/operator-intent grounding trace.
- Trace reasoning conclusions to their actual downstream consumers, with memory/premise provenance and invalidation dependencies.
- Establish candidate-goal formation as a separate developmental requirement; do not count externally supplied goals.
- Map state ownership across Brain beliefs, WorldModel facts/relations, memory metadata and donor-only state.
- Verify action execution, external consequence observation, authorization grant freshness/revocation, partial/unknown side effects and caller-visible completion.
- Execute deterministic failure injection for all durable append, compensation, multi-event feedback, goal completion, queue shutdown/saturation and restart/retry boundaries.
- Demonstrate learning through the chain experience/evidence → attributed update → durable state → changed future computation, and use matched controls/ablations for claims of learning benefit or transfer.
- Preserve exact-commit CI identity. A successful build-only job must not be described as a CTest pass.
- Obtain a genuinely independent review of the corrected report and record the Project Director's separate Phase 2 disposition.

## 7. Final decision boundary

**Review verdict: REVISE.**

The report is a valuable and substantially source-backed Phase 2 investigation. Its main architectural conclusions and its cautious treatment of donor evidence are largely justified. However, the two additional mainline persistence/state-consistency findings above are material omissions from a whole-Brain integration and recovery map. The report should be corrected and independently re-reviewed before Phase 2 documentation acceptance.

This review does **not**:
- clear Gate A or Gate B;
- accept Phase 2 as complete;
- approve PR #97 or any donor port;
- select an implementation baseline;
- authorize production/runtime changes;
- claim that either newly identified failure path has been reproduced by execution.

No production source, tests, build configuration, workflows or shared runtime state were modified by this review. The only intended repository change is this review document.
