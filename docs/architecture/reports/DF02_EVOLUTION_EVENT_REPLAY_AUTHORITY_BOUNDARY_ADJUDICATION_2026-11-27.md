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
