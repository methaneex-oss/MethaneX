# Independent Review — Phase 2 Whole-Brain Capability-to-Source Integration Map

**Review date:** 2026-11-06  
**Repository:** methaneex-oss/MethaneX  
**Verdict:** REVISE — useful and substantially evidence-backed investigation, but not yet reliable enough for Phase 2 acceptance  
**Review scope:** Static independent review of the complete Phase 2 report, its pinned source claims, the accepted mechanism specification, the applicable repository governance artifact, and PR #180  
**No production code, tests, build configuration, workflows, donor branches or shared runtime state were modified. No build or test execution is claimed.**

---

## 1. Exact repository state reviewed

The review was performed against live repository references fetched for this review, not inherited commit assumptions.

| Item | Exact reference / state |
|---|---|
| PR #179 | Open, draft, unmerged; branch `docs/jarvis-phase-2-whole-brain-integration-map-20261105`; HEAD `6f2c2cf05196e69a48f5deefcc3f4609e258c19a`; base branch `docs/jarvis-project-governance-rules-20261105` at `39fe09dcf13496f5f0005ccf3f00739303e29f88` |
| Primary report | `docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md`; blob `cc772cf571a7f9bf3ee3df2c1e392a8a392903a3`; 3,187 lines |
| PR #180 | Open, draft, unmerged; branch `research/phase-2-brain-integration-map-20261105`; HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`; base branch `spec/brain-mechanism-specification-20261103` at `0811a59e46bf934e32e794f90e4e7d18d4e2bd97` |
| Current main | `1273ddbcd0087d189e01388ded2d362fb1e058d2` |
| Accepted Brain mechanism specification | `docs/architecture/specifications/00_BRAIN_MECHANISM_SPECIFICATION.md`; commit `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`; blob `3b6a53c8a295fa0d9fc29bbb6c7688b61d1dcdb1` |
| Governance artifact | `docs/governance/JARVIS_PROJECT_GOVERNANCE_AND_BUILDER_RULES.md`; blob `e4315956cfb1ed075b508af3053601fed345f0a5` at PR #179's base |

PR #179 currently changes one file, the report. Its PR metadata reports 66 commits and 3,186 additions. PR #180 changes the same report path with one commit and a 311-line initial report. Neither PR is merged.

The governance document on PR #179's base explicitly labels itself a **proposed project-wide governance baseline**. PR #179 also correctly describes PR #178 governance as proposed and unmerged. I therefore treated the accepted PR #174 specification as the architecture authority and the proposed governance text as a working standard, not as an already-approved authority. Relevant proposed rules include whole-system dataflow (Rule 5.2), action/consequence evidence (Rule 6.4), held-out evaluation (Rule 6.5), persistence/recovery (Rule 8.4), exact test/run identity and no fabricated evidence (Rules 9.2–9.6), genuine independent review (Rule 11.8), and phase exit approval (Rules 12.3–12.4).

The repository tree inspected for this review did not expose a separate tester-specific governance file. This review does not substitute for the Independent Tester role or claim that runtime tests were executed.

---

## 2. Executive assessment

The report is materially stronger than a module inventory. It traces actual call paths, distinguishes current main from donor code, identifies state ownership and persistence boundaries, records exact source identities, and repeatedly distinguishes source-derived risks from reproduced incidents. Its central conclusion is justified:

**The pinned main implementation does not demonstrate the accepted specification's complete integrated Brain or the minimum cross-mechanism developmental learning lifecycle.**

The most important confirmed integration findings are supported:

- In main `CognitiveCycle::run`, memories are retrieved into cycle context but are not passed to `ReasoningProblem`; reasoning output is stored but not consumed by later planning or decision logic. Main source: `core/cpp/src/cognitive_cycle.cpp`, blob `3df14c552f2048b0394dc362f7ee7a654a93fb32`, lines 35–44 and 119–134.
- The main reasoning engine is a narrow keyed-belief consistency check and bounded causal-link traversal, not evidence of the full BM-12 contract. Main source: `core/cpp/src/reasoning.cpp`, blob `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`, lines 40–113.
- Main causal links are formed from a changed belief paired with other post-transition beliefs; the source does not establish intervention, confounder or counterexample control. Main source: `core/cpp/src/causal_model.cpp`, blob `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d`, lines 47–70.
- Main goal selection uses eligible supplied goals; the inspected cycle does not establish experience-acquired candidate-goal formation. Main source: `core/cpp/src/cognitive_cycle.cpp`, lines 63–71.
- Main `CognitiveCycle` does not call the compiled `PerceptionPipeline` utility. Its standalone compilation and test registration do not establish production-path integration.

The report also correctly refuses to equate donor code, successful compilation, registered tests, or narrow synthetic task performance with current-main capability acceptance. It correctly leaves Phase 2 IN PROGRESS, Gate A NOT CLEARED, Gate B unassessed, and implementation authorization separate.

However, four corrections are required before the report itself should be accepted. Two are material source/reconciliation defects; two expose reasoning API behaviors that should be recorded explicitly.

---

## 3. Findings

### R-01 — Mainline journal failure handling is omitted from the report's donor-scoped persistence finding

**Severity:** Medium  
**Confidence:** High for the source behavior; operational impact remains conditional on the filesystem failure occurring.  
**Status:** Confirmed source-scope omission; no fault-injection reproduction claimed.

The report's §32, lines 2472–2511, presents P2-I-014 as an issue at donor HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Its stated weaknesses include unchecked append rollback, unchecked startup tail truncation, and the absence of a poisoned/recovery-required state that prevents later appends after failed repair.

The same relevant failure semantics are present in the pinned **main** Memory implementation:

- Main `core/cpp/src/memory.cpp`, blob `ba72a897306d4761246d0deab2fbab37c49d372f`, lines 154–158: startup tail repair calls `std::filesystem::resize_file(..., error)` but does not inspect the resulting error.
- The same file, lines 192–213: append failure calls `resize_file(journal_path_, original_size, rollback_error)`, ignores `rollback_error`, and returns false without placing the Memory instance into a failed/poisoned state.
- Main `Memory::append`, lines 119–127, permits subsequent appends when `persist` returns success; it has no visible state guard tied to a failed rollback or failed startup repair.

The donor implementation has diverged: its memory source blob is `ab42bba1d32d6f48d091787491c72294a4a55bb5`, whereas main is `ba72a897306d4761246d0deab2fbab37c49d372f`. The donor-specific quarantine details must not be copied wholesale onto main. Nevertheless, the unchecked rollback and truncation semantics are independently visible in main.

**Why this matters:** The report's persistence/recovery discussion is intended to establish the current-main and donor boundaries. Recording this failure only as donor evidence under-reports a weakness in the pinned main baseline. It also means that a future main implementation decision could overlook an existing journal failure contract simply because the report's detailed finding is donor-scoped.

**Required correction:**

1. Add a main-specific source finding or expand the existing persistence analysis with separate main and donor subsections.
2. Keep the implementation differences explicit: main's inspected loader does not have the donor quarantine behavior described in §32.
3. Define the supported durability model (process restart versus OS crash/power loss) without using “durable” ambiguously.
4. Require fault injection for write failure, append rollback failure, startup tail-truncation failure and restart/replay. A failed repair must not allow later events to be acknowledged behind an unrepaired malformed suffix.
5. Keep this finding separate from the donor multi-event learning transaction finding P2-I-023.

**Acceptance evidence:** exact main and donor source references; deterministic fault-injection tests at the Memory boundary; proof that later appends are rejected or safely repaired after an unsuccessful rollback/truncation; restart checks showing every acknowledged event is recovered exactly once.

### R-02 — The PR #180 comparison contains a false statement about PR #180's contents

**Severity:** Medium  
**Confidence:** High  
**Status:** Confirmed report error.

PR #179 §12.5, line 1029, states:

> PR #180's BM-02 section labels contextual language/operator-intent grounding as F-02, and BM-12 labels downstream reasoning integration as F-03.

That statement does not match PR #180 at its exact HEAD `6ca140300b914ed981a50301bbf1d82a5bfe4d8b`. I fetched the complete 311-line report at that commit and searched its full text. It contains no F-02 or F-03 labels and no contextual-language/operator-intent-grounding discussion. Its six findings are P2-I-001 through P2-I-006:

1. retrieved memory omitted from reasoning premises;
2. reasoning result not consumed downstream;
3. supplied-goal lifecycle is not candidate-goal formation;
4. causal links may overstate causality;
5. sequential cycle is not full recurrent/concurrent cognition;
6. journal and metadata use separate persistence paths.

The report's own table in PR #179 §12.5, lines 1016–1027, correctly maps those six findings to IF-02, IF-03, IF-06/P2-I-015, IF-05, IF-08 and IF-10/P2-I-023/P2-I-016. It also correctly records that all 20 distinct 40-character blob identities found in PR #180 occur in the current PR #179 report. I independently reproduced that hash-set check.

The separate four-obligation provenance discussion in PR #179 §45.3, lines 3107–3123, may be based on the Phase 1 reconciliation and the unavailable PR #174 follow-on review artifact. It must not be attributed to PR #180.

**Why this matters:** This is not a cosmetic typo. It assigns review-finding content to the wrong source artifact and undermines the provenance reconciliation that is supposed to keep PR #173 F-02/F-03 separate from later PR #174 follow-on obligations.

**Required correction:**

1. Remove the claim that PR #180 labels its BM-02/BM-12 findings as F-02/F-03.
2. State that PR #180's six findings are the P2-I-001–P2-I-006 set listed above and that their technical content is incorporated into PR #179.
3. Keep the PR #173 F-02/F-03 and PR #174 follow-on F-02/F-03 provenance discussion tied to its actual correction/reconciliation records; retain the explicit limitation that the original PR #174 follow-on artifact has not been recovered.
4. Recheck all statements about which report introduced each finding against the exact source artifact.

**Acceptance evidence:** corrected §12.5 and any dependent summary; exact PR #180 HEAD and blob retained; no unsupported attribution of the missing PR #174 artifact to PR #180.

### R-03 — Public ReasoningEngine::infer can silently overwrite contradictory premises

**Severity:** Medium  
**Confidence:** High  
**Status:** Confirmed public-API behavior; not currently shown as the path used by `CognitiveCycle::run`.

The report's BM-12 section correctly says that `consistent` detects different values for the same belief key and that contradiction handling is limited. It does not identify that the separately public `infer` method does not enforce that consistency check.

Evidence at pinned main:

- `core/cpp/include/jarvis/core/reasoning.hpp`, blob `5c6f82797d4f5052ad5d71a25624de192a2c87d9`, lines 20–30: `infer` is a public method with no documented precondition requiring consistent premises.
- `core/cpp/src/reasoning.cpp`, blob `feec78b2e8a1f2b0b58733fd509e4e5a750258fc`, lines 50–57: `infer` initializes `known` using `known[belief.key] = belief.value`. Duplicate keys overwrite earlier values according to input order. It does not call `consistent` or preserve a contradiction result.
- In contrast, `solve`, lines 82–98, does call `consistent` and returns a contradiction result before invoking `infer`.
- The registered `reasoning_architecture_suite` directly exercises `infer` (lines 23–28) but only with a single, non-contradictory premise. It tests contradictory input through `solve` (lines 36–40), not through direct `infer`.

A direct call with two contradictory values for the same key can therefore produce order-dependent inferred state rather than an explicit conflict. For example, premises containing both `system.enabled=true` and `system.enabled=false`, together with a link from the latter to `system.ready=true`, allow the last value assigned to the map to control the inference path.

**Why this matters:** The accepted specification requires contradictory premises to remain visible and prevent unsupported conclusions from being treated as settled. It also requires explicit handling of premise status and inference lineage. A public inference entry point that silently overwrites conflicting input is not protected by the safer `solve` wrapper.

**Required correction:**

1. Either make `infer` enforce and return explicit contradiction/insufficient-evidence status, or make it a non-public helper with a documented, enforced precondition.
2. Do not resolve duplicate-key conflicts by vector order.
3. Add tests that call the public inference API with conflicting premises in both input orders and assert that no unsupported conclusion is emitted.
4. Preserve the distinction between a contradiction, an empty/incomplete premise set, and a valid derivation.

**Acceptance evidence:** public API contract and tests establish order-independent contradiction handling; no inference result silently selects the last duplicate value.

### R-04 — Reasoning confidence is not semantically qualified for a consistency-only result

**Severity:** Low to Medium  
**Confidence:** High for the source behavior; meaning of the field remains unresolved because the API does not define it.  
**Status:** Confirmed contract ambiguity; do not label it a demonstrated downstream incident.

The report notes in §3 BM-12, lines 425–435, that empty premises can produce `valid=true` with zero confidence and that this is not a substantive inference. It does not record a second, distinct result case:

- Main `core/cpp/src/reasoning.cpp`, lines 98–112: when premises are non-empty and consistent but no new conclusion is derived, `solve` returns `valid=true`, kind `consistency`, and `confidence=1.0`.
- `core/cpp/include/jarvis/core/reasoning.hpp`, lines 14–25: the result exposes one unqualified `double confidence`; it does not identify whether this is confidence in internal consistency, evidential support, the inference operation, or a conclusion.
- The test at `core/cpp/tests/reasoning_architecture_suite.cpp`, lines 42–45, checks the consistency kind and one retained conclusion but does not assert or define the confidence meaning.

The accepted specification explicitly requires BM-12 to distinguish logical validity, evidential support, plausibility, confidence and truth (specification lines 520–523). It also requires empty premises to yield an explicit insufficient-evidence/unresolved result, not a successful substantive inference (line 531; acceptance scenario 28 at lines 801–805).

The current report recognizes the empty-premise issue but should also call out the consistency-only confidence semantics. A value of 1.0 may be intended to mean “the supplied premises did not contradict each other”; if so, the contract must say that and must prevent consumers from interpreting it as confidence in a derived conclusion or in the truth of the premises.

**Required correction:**

1. Define `valid` and `confidence` independently and state the scope of confidence for each result kind.
2. Represent “consistent premises, no new inference” separately from “successful substantive inference”.
3. Add tests for empty premises, consistent premises with no derivation, successful derivation and contradiction.
4. Ensure downstream consumers cannot treat a consistency-only result as high-confidence evidence for a new conclusion.

**Acceptance evidence:** result semantics documented in the public interface and test assertions that distinguish consistency from evidential support and substantive inference.

---

## 4. PR #179 versus PR #180 — independent comparison

**Classification:** Complementary in origin, substantially overlapping in technical content, and not safe to merge as two independent reports without explicit disposition.

Both PRs add the same path:
`docs/architecture/reports/PHASE_2_WHOLE_BRAIN_CAPABILITY_TO_SOURCE_INTEGRATION_MAP_2026-11-05.md`.

Their histories are not a linear sequence:

- PR #179 is based on the proposed PR #178 governance branch.
- PR #180 is based on the accepted PR #174 specification branch.
- Their exact merge base is current main `1273ddbcd0087d189e01388ded2d362fb1e058d2`.
- Comparing PR #180 HEAD to current PR #179 HEAD reports **81 commits ahead and 13 behind** in that direction; the branches have diverged.
- PR #180 is the compact 311-line initial evidence batch. PR #179 is the 3,187-line expanded report with the BM-01–BM-12 map, larger finding register, donor comparison, CI provenance, persistence/recovery findings and closure handoff.
- All 20 distinct blob SHAs extracted from PR #180 are present in PR #179. This verifies source-identity inclusion, not textual equivalence or correctness of every conclusion.
- PR #179's mapping of PR #180's six findings in §12.5, lines 1016–1027, is broadly correct. Its additional statement at line 1029 about PR #180 mislabeling F-02/F-03 is incorrect and must be corrected under R-02.

**Decision:** PR #179 is the more complete working investigation. PR #180 is a preserved initial research artifact whose substantive findings and source identities are incorporated. The two PRs are not independent competing technical conclusions, but they are also not merge-equivalent branches. Preserve both histories. Do not merge PR #180 into PR #179 or close either PR as a reviewer action; the Project Director should decide the documentation/branch disposition after the report correction.

---

## 5. Claims independently supported

The following material claims in PR #179 were checked against the pinned source and are supported within the stated scope:

| Report claim | Independent check |
|---|---|
| Main cycle retrieves memories but does not pass them into reasoning premises | Confirmed: main `cognitive_cycle.cpp` lines 35–44 |
| Main cycle does not consume the reasoning result in later planning/decision steps | Confirmed in inspected `CognitiveCycle::run`: lines 44–134 |
| Main ReasoningEngine is narrow and does not satisfy the full BM-12 contract | Confirmed by `reasoning.cpp` lines 40–113 and accepted specification lines 485–531 |
| Main causal learning has a co-state/causal-attribution limitation | Confirmed by `causal_model.cpp` lines 47–70; report's IF-05 is directionally justified |
| Main goal selection is not candidate-goal formation | Confirmed for the inspected cycle path: `cognitive_cycle.cpp` lines 63–71 |
| Compiled perception utility and registered unit target do not prove production call-path integration | Confirmed by main `core/cpp/CMakeLists.txt` lines 8–66, test CMake registration, and the inspected main cycle source |
| Donor PR #97 must not be counted as main capability | Correctly separated throughout the report |
| PR #179's documented build run is build evidence, not a CTest pass | Correctly qualified in the report; no test execution is inferred from a build-only workflow |
| Narrow DLT-002 evidence is not general intelligence or exact-current-main proof | Correctly qualified in the report's experimental-limit discussion |

These confirmations do not mean that every source claim or every finding in the 3,187-line report was independently reproduced. They establish that the report's central integration diagnosis is not merely unsupported narrative.

---

## 6. Required corrections and acceptance criteria

The following corrections are required before this review can change from REVISE:

| ID | Required correction | Minimum acceptance evidence |
|---|---|---|
| R-01 | Extend persistence analysis to the pinned main Memory implementation; distinguish main and donor behavior | Exact source anchors; deterministic write/rollback/tail-repair failure tests; restart/replay proof; no acknowledgement behind unrepaired tail |
| R-02 | Correct the false PR #180 F-02/F-03 attribution in §12.5 | PR #180 exact-head content checked; six actual findings mapped; PR #174 follow-on provenance kept separate |
| R-03 | Close the public `ReasoningEngine::infer` contradiction bypass | API contract plus contradictory-premise tests in both orders; no order-dependent inference |
| R-04 | Define `ReasoningResult.valid` and `confidence` semantics for consistency-only and substantive results | Explicit result contract and tests for empty, consistent/no-derivation, derivation and contradiction |

The Independent Tester should verify the runtime/test portions after the relevant implementation or test-preparation authorization. This reviewer did not run builds, CTest, sanitizers, fault injection, benchmarks or learning experiments.

In addition to these corrections, Phase 2 acceptance still requires the report's own open exit items to be closed with evidence, including:

1. BM-01/BM-02 acquisition and representation integration, including provider-failure truthfulness.
2. End-to-end reasoning/memory dataflow and downstream use by the owning mechanisms.
3. Explicit authoritative state ownership and dependency/freshness behavior.
4. Action execution, verified consequence, persistence acknowledgement and partial-effect semantics.
5. Journal and multi-event recovery, interruption, retry and idempotency behavior.
6. Evidence that an accepted learning update persists and changes later computation, with matched learning-disabled controls, held-out contexts and counterexample/regression checks.
7. Donor/main compatibility and selective-port decisions based on exact revisions.
8. The human-cognition/MCU comparison artifact or explicit Project Director-approved deferral.
9. The missing PR #174 follow-on review artifact recovered, or its unavailability explicitly accepted by the Project Director as a bounded provenance limitation.
10. A separate independent review of the corrected report and a separate Project Director phase/gate decision.

A report correction does not itself close a runtime defect. A passing test does not itself establish a learning capability. A completed Phase 2 investigation does not itself clear Gate A or Gate B.

---

## 7. Final decision

**Verdict: REVISE.**

The Phase 2 report is a substantial and generally careful source investigation. Its central conclusion—that main is not yet an integrated specification-complete Brain—is supported. Its separation of main and donor capability, its treatment of test/build evidence, and its recognition of persistent learning and recovery as cross-mechanism requirements are appropriate.

It is not yet fully reliable as an acceptance artifact because it omits the mainline form of a material journal failure weakness, contains a demonstrably false statement about PR #180's contents, and does not fully expose two reasoning API contract problems.

**Phase 2:** NOT ACCEPTED COMPLETE.  
**Gate A:** NOT CLEARED by this review.  
**Gate B:** NOT ASSESSED OR CLEARED by this review.  
**Implementation baseline:** Not selected.  
**Production implementation authorization:** None.  
**PR #179 / PR #180:** Both remain open/draft/unmerged; no status was changed by this review.

This document is an independent review artifact, not a Builder self-check and not an Independent Tester execution report.