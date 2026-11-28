# DF-02 Evolution Controller Transaction, Idempotency and Rollback Lifecycle Adjudication — 2026-11-27

**Scope:** candidate/donor `evolution_controller.cpp`, adoption-journal state machine and donor controller/adoption tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor introduces staged adoption and compensating rollback paths; direct lifecycle is materially stricter. Transactional failure cases and idempotency mismatch remain open. Historical e737 third-lineage controller/tests #44 and #49 passed in five CI jobs; frozen candidate/donor controller refs and current PR #203 CTest not run.

## 1. Exact refs

- Candidate controller `01484ebf12fc3902bce749030a1f54610b26236a` (51 tips).
- Donor controller `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5` (16 tips; 315 lines).
- Candidate adoption-journal test `24a1be9541cc038518065724aef1968efc4dc595` (116 tips).
- Donor adoption-journal test `fc8ae17bb837831fef7bf69873ec0e5243e2bc22` (39 tips).
- Donor Brain integration test `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` (13 tips).
- Adoption journal source/header lineage has 11/10 blobs; exact cohort previously adjudicated in DF-02 adoption-journal/test-contract report.

## 2. Direct controller lifecycle

Donor controller separates record evaluation, validate-for-adoption, adopt, commit journal, append adoption history, compensate/restore previous model value, and rollback. Brain-bound adoption validates exact recorded evaluation/history/journal identity, recomputes experiment outcome and threshold, checks isolation/attestation and proposal safety, then commits.

Journal stages Pending→Adopted→RolledBack and uses experiment identity to reject mismatched reuse. Compensating transitions allow restoration to Pending or Adopted when later persistence/history steps fail. Donor tests cover identity conflict, replay idempotency, validation before mutation, compensation/restoration and history consistency.

## 3. Remaining direct-path gaps

- **Idempotent evaluation mismatch:** `record_evaluation` scans history for an Evaluated event with same experiment ID and returns true when journal state is Pending/Adopted, without comparing the supplied experiment to the historical/journal snapshot. It can report success for changed evidence under reused ID. Adoption validation later compares exact fields and blocks mutation, so the risk is false lifecycle success/selection rather than confirmed adoption bypass.
- **Rollback latest-active:** direct rollback validation requires target record Adopted and matching parameter key, plus model value not baseline, but does not require that target experiment be the latest active adoption for that parameter. The model rollback restores baseline; stale experiment rollback can leave newer journal record Adopted while parameter is reset. See replay-authority report.
- **Compensation return status:** controller attempts model and journal compensation on append/commit failures; several restoration results are not surfaced as a distinct recovery status. No evidence that compensation failure is impossible.
- **Multi-store transaction:** controller journal/history and Brain memory are separate in-memory/durable mechanisms. The code uses compensation, not atomic cross-store commit. Crash between writes is not tested.
- **No durability for controller journal itself:** adoption-journal state is reconstructed from Brain events; direct in-memory state is not a standalone durable journal.

## 4. Test contract and gaps

Donor adoption-journal suite source checks stage/commit/rollback, same-ID conflict, pending/adopted/rolled-back restoration, idempotent replay and history state. Brain integration checks strict adoption gates and legacy-event replay rejection.

No execution performed. Missing adversarial tests include evaluation same-ID/different-fields idempotency, stale rollback after multiple same-parameter adoptions, compensation failure injection, crash between model/journal/history/memory writes, journal replay without evaluation, rollback event key mismatch, and direct/controller return status under partial recovery.

## 5. Five review lenses

1. **Semantic:** staged lifecycle and compensation state transitions mapped.
2. **Build/test:** donor tests inspected; no native execution.
3. **Integrity:** exact experiment identity prevents journal ID reuse, but idempotent evaluation path lacks comparison.
4. **Evolution safety:** direct adoption gate is strict; replay and stale rollback paths separately documented.
5. **Hostile review:** compensation is not described as atomic/durable; no successful test run claimed.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor controller | Compared |
| Journal state machine | Source/test inspected |
| Compensation/idempotency tests | Source contract present |
| Same-ID evaluation content comparison | Gap |
| Stale active rollback | Gap |
| Compensation/crash/fault injection | Open |
| Native tests | Historical e737 alternate tests #44/#49 passed in five jobs; frozen candidate/donor exact refs and current PR #203 CTest not run |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Evolution controller remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Third-lineage e737 controller and historical execution — 2026-11-28

The e737cae7 branch contains a third controller lineage, distinct from both frozen refs:
- candidate controller: 01484ebf12fc3902bce749030a1f54610b26236a (82 lines);
- frozen donor controller: 4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5 (316 lines);
- e737 alternate controller: 4d910df0fc6626bd7fb55ee35522f7869b4aa13c (351 lines).

The e737 variant adds materially stronger replay checks:
- replay_evaluation requires candidate_executed, finite fitness/confidence/minimum-improvement/proposal fields, valid outcome, confidence range, isolation attestation policy, and recomputes EvolutionExperimentEngine::evaluate to confirm the recorded outcome;
- validate_adoption_for_brain compares evaluation procedure ID, evaluator executable fingerprint, baseline/candidate artifact IDs and other exact evaluated fields; it no longer recreates a private attestation from journal fields;
- replay_rejection persists rejected evidence into adoption journal/history;
- simulated evidence is accepted only when policy explicitly permits it; otherwise valid isolation attestation is required.

The e737 alternate test sources are also third-lineage:
- evolution_adoption_journal_suite.cpp ad3c58179cc150d303f5bcbbfa50beb40a1327c6 (CTest #49);
- evolution_brain_integration_suite.cpp b065a301397c83bcb460d43fa36421a7bebc9060 (CTest #44).

Both tests passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; all five jobs report 71/71. The e737 parent build graph is alternate CMake 33197 (64 TUs + OpenSSL Crypto), not frozen donor parent CMake bc264.

This historical result is evidence for the 351-line alternate controller and alternate tests, not the frozen donor 316-line controller, candidate 82-line controller, or current PR #203. The original gaps around same-ID evaluation-content mismatch, stale rollback after later same-parameter adoption, compensation failure and crash between stores remain to be checked against the exact e737 variant; do not assume the alternate diff resolves them.
