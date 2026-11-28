# DF-02 Canary Isolation, Evidence Semantics and Operational-Canary Adjudication — 2026-11-27

**Scope:** exact candidate/donor `evolution_canary.cpp`, controller header/source behavior, and 17 exact canary-controller test blobs.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor corrects per-experiment canary state and adds worst-case regression handling; orchestration still does not supply independent live canary observations. Static concerns recorded; no tests executed. Path remains OPEN.

## 1. Exact implementation inventory

Three `evolution_canary.cpp` blobs:

- Candidate `b40c2eec58db1a3f7d3007781f0a5e6abe8c70a9` (119 tips, 44 lines).
- Donor `8773507b4bc5842c60b78bcb384f09ea4c4caa2b` (76 tips, 53 lines).
- Alternate `f1b57709bd57e2457e7a500b389712a96daae960` (1 tip, isolation-boundary branch).

Candidate controller source/header uses one canary instance. Donor controller source uses an experiment-ID keyed map; donor header SHA `c1af30f84f03d87d151fe3c5fbfd89ef39fbe34e` adds preview and Brain/replay methods; candidate header SHA `e06441d23685093a3c533498a09adf3a8baf5914` exposes a smaller direct controller contract.

## 2. Candidate/donor semantic delta

Candidate canary tracks observation count and mean candidate-minus-baseline delta; rollback occurs after sufficient observations when the mean exceeds the regression threshold.

Donor adds:
- **worst-observation regression** tracking; once minimum observations are met, a single delta below `-abs(maximum_regression)` triggers regression detection even if the mean is positive;
- a `preview` operation using a copied canary state (no mutation);
- per-experiment canary state in `EvolutionController`, avoiding the candidate's single shared canary accumulator across experiment IDs.

The donor test has a cross-experiment isolation scenario: preview does not consume an observation, observations for another experiment do not contaminate the first, and the correct three observations reach sufficient evidence. Candidate test does not cover that identity isolation.

## 3. Exact test-blob inventory

The artifact records 17 distinct `evolution_canary_controller_suite.cpp` blobs. Candidate and donor:
- Candidate `6acd8aedb7520aebe745b15a2a10c527262f28e0` (119 tips, 38 lines).
- Donor `80cac5df347987a9074e1ced43202f8759f797d7` (17 tips, 104 lines).

Historical alternates:
`07ec45d42cf8f489dedb22d4b68776622fbebe60` (20 tips), `0f183d232d421ffab50a02ca9caa2311885f1c54`, `1ba14b57f79f600599765910162d8a6736af3037`, `4620512b67abf3b388ed5e112e44dba258e22c45`, `4b867af52e11a15e9d867a35cdefbf9c83333a2a` (8 tips), `7a8b80f06552311c0103290392df82ca435bc5ea`, `825bdea8219f6fdb32fe9e724ab44e94bfad1d45` (2 tips), `90ed434d378d2ea50f2cdc17a7ff8a51fdbf0816`, `ba151311659a47f042454325181cd2c354d1e393`, `bb97b6cf1f047bce4e00b622001595f784a50917` (3 tips), `cb47cecb081dbd134d529fa248c1ed9498df365e`, `ceac4fa28fdfceae298f07a5e4924f9f666d1aa5`, `e06244456a8ef4df70f1688c0c5c9af99f7ba777`, `f5058d77ba40f407c4ff3db4d09b2862c63d128e`, and `f6fbbaa54771aa1ee3665148ce638d4e9aa390ae` (17 tips).

Exact-content variants cover rollback, replay, adoption journal, isolation attestation, per-experiment canarying and persistence assertions. Blob/branch counts are not authority.

## 4. Controller/orchestrator behavior — operational gap

The donor `EvolutionController::observe_canary` evaluates the per-experiment canary and calls rollback when the decision says rollback. It returns the `CanaryDecision` regardless of whether the controller rollback call succeeded. The orchestrator treats `decision.rollback` as successful rollback and marks lifecycle `RolledBack`; it does not inspect the rollback return/result. Therefore rollback *decision* and rollback *transaction success* can be conflated in lifecycle reporting. Failure-injection coverage is required.

The orchestrator's post-adoption loop currently calls `observe_canary` three times with the **same stored baseline/candidate trial fitness pair**. These are repeated historical evaluation values, not independently collected observations from an operating candidate. They can satisfy minimum observations and retain an adopted change without monitoring real live consequences. The canary is therefore a synthetic repeated-score check in this orchestration path, not a live production canary/monitoring system.

Canary accumulators are controller-local memory. The adoption journal/history records evaluation/adoption/rollback lifecycle, but the inspected canary state and observations are not durably recorded for restart recovery. A restart during canarying loses its observation count/worst/mean state; the parameter and adoption record may remain adopted. Restart/recovery policy for this state is not demonstrated.

## 5. Test contract and limits

Candidate suite: record an evaluation, adopt, then provide three decreasing candidate-vs-baseline deltas and assert rollback restores baseline and appends rollback history.

Donor suite adds:
- isolation attestation setup before record/adoption;
- adoption-journal and history state assertions;
- preview non-mutating behavior;
- separate experiment canary state;
- three observations within policy for one experiment and an unrelated experiment observation;
- replay of evaluation/adoption/rollback and idempotency assertions.

The donor tests still use direct synthetic fitness pairs. They do not cover orchestrator repeated-value false retention as a live-canary claim, rollback failure with lifecycle falsely reporting RolledBack, restart during a canary, or real production telemetry.

## 6. Five review lenses

1. **Semantic:** mean vs worst regression and shared vs experiment-keyed canary state compared.
2. **Build/test:** 17 exact test variants enumerated; donor assertions inspected; no test execution.
3. **Trust/authority:** rollback transaction result must be distinct from threshold decision; canary is not live deployment authority.
4. **Capability:** bounded regression detector exists, but orchestrator's repeated benchmark pair is not live operational monitoring.
5. **Hostile review:** per-experiment isolation improvement credited; failure and restart gaps remain; no acceptance or implementation selection.

## 7. Open obligations / disposition

| Item | State |
|---|---|
| Three exact canary source blobs | Complete for slice |
| Candidate/donor state isolation and regression semantics | Compared |
| 17 exact test blobs | Enumerated |
| Cross-experiment state isolation | Donor test source present |
| Rollback failure/lifecycle reporting | Open |
| Live canary input and restart persistence | Open |
| Consumer/authority/provenance/retention | Open |
| Native tests | Not executed |
| DF-02 | OPEN |

`core/cpp/src/evolution_canary.cpp` and its controller integration remain **OPEN / NO AUTHORITY DECISION**. No source selected, adopted, retired or deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
