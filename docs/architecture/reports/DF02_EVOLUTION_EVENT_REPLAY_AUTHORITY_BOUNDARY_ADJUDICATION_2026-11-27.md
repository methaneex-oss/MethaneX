# DF-02 Evolution Event Replay Authority-Boundary Adjudication — 2026-11-27

**Scope:** frozen donor Brain evolution-event replay, controller/journal replay APIs, public observation path and donor integration-test coverage.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** direct adoption APIs enforce evaluation evidence, but journal replay has a separate weaker path. Source-derived authority gaps are identified; no code change/test run.

## 1. Exact source refs

- Donor Brain replay source: `dec9e5442b3ca4b81a7879855c6146b2619934cc`.
- Donor controller: `4e77ec2e5daa09a964132ca486b8c5ee1cebf2f5`.
- Donor adoption journal: `d8df30a2902d3dac734fb1a571cbbecdd881b76f`.
- Donor model adoption: `7a3bc311034c48181cc9b9d4df81c308ebaa8f3d`.
- Donor integration suite: `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` (297 lines; exact test source).
- Existing controller/adoption-journal report provides the historical source/test cohort inventory; this is a bounded replay-authority review.

## 2. Runtime API preconditions versus replay path

Direct Brain/controller adoption is guarded by evaluation-history matching, independently recomputed experiment outcome, staged journal identity/state, isolation policy/attestation, proposal eligibility and exact evidence matching. The donor integration suite explicitly tests direct adoption rejection for missing evaluation, equal fitness labelled Improved, subthreshold gain, and post-record mutation.

However, donor `Brain::replay(evolution_adopt)` is a separate code path:
- requires a nonempty `experiment_id` (rejects unversioned legacy events);
- reconstructs an experiment from event fields and sets `candidate_executed=true`;
- re-attests if the event claims isolation;
- checks only whether the same ID is already Adopted/RolledBack;
- directly calls `EvolutionModel::adopt(proposal)`, then `EvolutionController::replay_adoption(experiment)`;
- does not require a matching durable `evolution_evaluated` record, independently recompute measured experiment outcome, or verify evaluation-history identity before replay adoption.

`replay_adoption` itself stages and commits the supplied experiment to the adoption journal; it does not validate evaluation-history evidence. `EvolutionModel::adopt` validates proposal eligibility/current value/confidence/expected gain, not trial execution or baseline-versus-candidate evidence. Therefore a versioned but malformed/inconsistent `evolution_adopt` event can potentially recreate a model mutation without the runtime adoption gate. The public `Brain::observe(Event)` path accepts event kinds without an evolution-event-specific validation gate, so the replay path is reachable through journal input as well as restart reconstruction.

The donor tests reject **unversioned** legacy adoption events and exercise the direct API evaluation preconditions. They do not inject a versioned adoption event with no matching evaluation, altered proposal/evaluation fields, invalid outcome or fabricated isolation metadata. This gap is not covered by those tests.

## 3. Rollback event identity gap

Donor `Brain::replay(evolution_rollback)` requires a nonempty experiment ID and an adoption-journal record in Adopted state, then calls `EvolutionModel::rollback(key)` using the event's parameter key and `replay_rollback(experiment_id)` using the event's experiment ID. It does **not** compare the event key to `record.parameter_key` before mutating the model.

A crafted/mismatched rollback event could therefore rollback parameter B while marking experiment A rolled back, if B is currently changed and A is Adopted. Direct `validate_rollback_for_brain` checks key/record correspondence, but replay bypasses that validation.

## 4. Stale direct rollback across successive adoptions

The controller allows multiple adopted records for one parameter and exposes `adopted_experiment_for_parameter` (latest revision), but `validate_rollback_for_brain` only checks that the target record is Adopted, its parameter key matches the requested key, and the current parameter is not baseline. It does not require the requested experiment to be the latest active adoption for that parameter.

The model's `rollback(key)` resets the parameter to baseline. If an older experiment's canary/rollback is invoked after a newer adoption on the same key, this can reset the newer value while leaving the newer adoption record Adopted. A sequential multi-adoption/stale-canary test is absent. This is a source-derived risk; do not claim exact reproduction without an executable regression test.

## 5. Five review lenses

1. **Semantic/authority:** direct API is strict; replay adoption/rollback bypasses some of the same exact-evidence and identity checks.
2. **Build/test:** donor integration test source inspected; explicit legacy and direct-API gate cases present; crafted versioned replay cases absent. No tests executed.
3. **Security/trust:** event-journal integrity alone is not a semantic authority check; external/public observation can append event kinds that replay interprets as control-plane mutation.
4. **Evolution safety:** rollback of stale/mismatched experiment IDs can desynchronize parameter value from journal lifecycle.
5. **Hostile review:** no claim of exploit execution; findings are source-level reachable paths requiring tests and policy correction.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Direct adoption gate | Source inspected; donor tests cover selected negative cases |
| Versioned adoption replay evidence check | Gap identified |
| Replay rollback parameter-key binding | Gap identified |
| Latest-active-adoption rollback precondition | Gap identified |
| Regression/fault-injection tests | Open |
| Native execution | Not performed |
| Full controller lineage/consumer/authority/retention | Open |
| DF-02 | OPEN |

**Disposition:** evolution-event replay remains **OPEN / NO AUTHORITY DECISION**. No implementation selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Alternate authenticated replay lineage — correction and residual rollback gap (2026-11-28)

The later historical branch fix/evolution-authenticated-replay-final-20261030 at HEAD e737cae7f907696ef787a4e85b0dee3a739d71b1 materially improves the donor replay path. It is not the PR #97 donor and is not the current PR #203 candidate.

Exact refs:
- Brain replay source: core/cpp/src/brain.cpp, blob 23080c58545d3f211a708b72952b1898f7c1991e.
- Evolution controller: core/cpp/src/evolution_controller.cpp, blob 4d910df0fc6626bd7fb55ee35522f7869b4aa13c.
- Integration test: core/cpp/tests/evolution_brain_integration_suite.cpp, blob b065a301397c83bcb460d43fa36421a7bebc9060.

### Adoption replay: demonstrated defect and fixed alternate lineage

At earlier commit cc00afaebb4da58eb75993f0386eaab333e8282d, validate_adoption_for_brain recreated a private isolation attestation from journal fields by copying the experiment and calling attest_isolated_result() when the journal record said isolated. The integration test at lines 418–421 explicitly checks that a replayed object without independently authenticated measurements cannot regain isolation trust from metadata. That assertion failed in CI.

The follow-up commit e737cae7 changed the controller to call EvolutionSafetyGate::approve(experiment, policy_) on the original instance and removed the metadata-driven private re-attestation. The exact diff is in evolution_controller.cpp; the source fix is 2 additions and 1 deletion. Post-fix Brain CI, JARVIS Brain Tests and Brain ThreadSanitizer all completed with 71/71 tests passed in every test job. Exact workflow run IDs and job summaries are recorded in DF02_EVOLUTION_TRUST_LIFECYCLE_EXACT_COMPARISON_2026-11-27.md.

The alternate Brain::replay(evolution_adopt) path at lines 548–616 now:
- restores trusted attestation only through EvolutionExperimentRunner::restore_trusted_attestation;
- rejects already terminal adoption-journal states;
- validates the experiment against durable evaluation/adoption evidence before model mutation;
- records a rejection when validation or model adoption fails;
- refuses unversioned legacy adoption events.

This closes the earlier donor's specific replay-adoption evidence bypass in this alternate lineage, subject to the remaining validation and authority gaps below. It does not change the disposition of the PR #97 donor or current PR #203 candidate.

### Residual rollback replay key-binding defect in the alternate lineage

The same alternate Brain::replay(evolution_rollback) path remains weaker than its direct controller validation:
- brain.cpp lines 619–625 fetches the adoption record by experiment ID and checks that its state is Adopted;
- line 626 calls evolution_.rollback(*key) using the event-supplied parameter key;
- line 628 calls replay_rollback using the event-supplied experiment ID;
- it does not compare the event-supplied key with record->parameter_key before mutating the model.

By contrast, EvolutionController::validate_rollback_for_brain checks record->parameter_key == parameter_key, but the replay branch does not call that validator. A mismatched rollback event can therefore mutate one parameter while transitioning a different experiment ID. This is a source-level authority defect; no exploit was executed.

The alternate replay path also does not require the requested experiment to be the latest active adoption for that parameter. A stale but still Adopted experiment record may therefore be used after a newer adoption on the same key unless the event ordering/other invariants prevent it. The direct validator checks that the target record is Adopted and matches the key, but not that it is the latest active record. A sequential multi-adoption/stale-canary test remains required.

### Updated replay disposition

| Item | PR #97 donor | Alternate e737cae7 lineage |
|---|---|---|
| Adoption replay requires durable evaluation evidence | Gap identified | Source gate added; CI regression test passes |
| Replay can recreate private attestation from serialized isolated flag | Present in donor replay path | Removed in follow-up controller fix |
| Unversioned adoption/rollback | Rejected by donor for legacy events | Explicitly rejected |
| Rollback event key bound to adoption record | Gap identified | Still not checked in Brain replay |
| Rollback must target latest active adoption | Gap identified | Still open |
| Native/sanitizer/TSAN test execution | Not executed in original donor report | 71/71 passed on each post-fix test job |
| Authority/baseline selection | Open | Open |

The authenticated alternate lineage materially improves adoption replay trust, but it does not fully close evolution rollback authority. No implementation was copied into PR #203; no donor was adopted; no baseline or retirement decision was made. DF-02 remains OPEN.
