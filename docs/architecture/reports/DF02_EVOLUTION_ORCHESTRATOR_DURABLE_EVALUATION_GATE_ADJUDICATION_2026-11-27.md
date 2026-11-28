# DF-02 Evolution Orchestrator Durable-Evaluation Gate Adjudication — 2026-11-27

**Scope:** ten exact `core/cpp/src/evolution_orchestrator.cpp` blobs, candidate/donor headers and opportunity-orchestration tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds a durable-evaluation precondition before winner adoption; candidate source contains a path that can proceed to adoption after evaluation-record failure. Source inspection only; tests not executed. Path remains OPEN.

## 1. Exact source inventory

Ten exact source blobs, all contents in the frozen discovery artifact:

| Blob SHA | Role | Tips | Representative branch | Lines |
|---|---|---:|---|---:|
| `efd55281ba7d2edf95c6a9f6537ed2944022617e` | Candidate | 110 | architecture/brain-foundation-planning20261103 | 154 |
| `c913ff0f42fc4647605376579b3f343b5c12c387` | Donor | 34 | ci/priority-one-provenance-validation20261031 | 162 |
| `937306ae95bfa3584dd60c41847586a6abd2e087` | Alternate | 18 | feat/prediction-developmental-validation20261030 | 300 |
| `c0f4a3f7b69bfaf365c6a23b91787b8fa63acd81` | Alternate | 21 | feat/dlt-002-adaptive-trial | 161 |
| `a6ed61020b2354329bd84492b4dc71a9c20ab066` | Alternate | 3 | feat/evolution-statistical-gates | 154 |
| `b36cd71c75df0616ea2260853e3f54c77d018baa` | Alternate | 1 | fix/evolution-lifecycle-review20261029 | 272 |
| `cc16288dccf4a42fdea01a7073470ba447a2fdbd` | Alternate | 1 | fix/evolution-trustworthy-lifecycle20261029 | 163 |
| `73c07694e0f2a0b023113cb1e53ad4a2563f95d0` | Alternate | 1 | fix/evolution-evaluation-lifecycle20261029 | 176 |
| `78e0abfdf7afaa5892654a1d48f7742e1e908959` | Alternate | 1 | feat/evolution-statistical-evaluation | 157 |
| `94aeee47e934a1473d802409e8581049fbb45f8b` | Alternate | 5 | feat/evolution-adoption-journal | 73 |

Tip sightings and branch names are provenance only, not authority or semantic ancestry.

## 2. Candidate/donor difference and defect/risk

Both versions schedule, validate generated proposals, rank them, evaluate a bounded number of trials, identify the empirical winner, record evaluations through the controller, supersede non-winners, and then adopt/canary the winner.

Candidate source SHA `efd55281ba7d2edf95c6a9f6537ed2944022617e` records evaluation attempts for all executed experiments, but after `controller->record_evaluation(experiment)` fails it marks that experiment `EvaluationRejected` and continues. Winner selection was already computed; candidate then proceeds to the adoption path without checking that the selected winner remains `CandidateEvaluated`. This is a concrete source-level authority defect: **the candidate can attempt adoption even when its durable evaluation record was rejected**.

Donor SHA `c913ff0f42fc4647605376579b3f343b5c12c387` adds the explicit precondition after evaluation recording:
- if the selected winner lifecycle is not `CandidateEvaluated`, reject and return before any adoption;
- only then supersede other evaluated candidates and attempt adoption.

The donor also allows an `EvolutionTrialConfig` constructor parameter (coordinator configuration) and stores it for the experiment run. This is configuration plumbing; the substantive safety correction is the durable-record precondition.

## 3. Test contract and cross-file evidence

Candidate orchestrator test SHA `4ef1dc80a85a8e9247c5816bdb73c6876d3a1b22` is a 97-line fixture; donor SHA `24d6dd905cb537cc6c14e329db6a7d52d49c97b8` is 162 lines. Both assert scheduling, two proposals evaluated, a positive winner retained, loser superseded, one parameter changed, and idle scheduling blocked. Donor adds checks around adoption-journal records and history for the selected experiment. Both use simulated evaluators with isolation disabled in the safety policy/config.

**Gap:** neither exact suite injects controller evaluation-record failure for the selected winner and asserts no adoption/no mutation. Thus the donor correction is source-visible but its specific failure precondition lacks a dedicated behavioral test in this suite. Existing adoption-journal test reports cover other journal cases; they do not replace this orchestrator-specific failure injection.

## 4. Five review lenses

1. **Semantic:** durable-evaluation lifecycle state is an explicit pre-adoption authority gate in donor; candidate can bypass it after record failure.
2. **Build/test:** exact test source inspected; donor adds journal/history assertions. No execution.
3. **Security/trust:** evaluation-record persistence failure must block model mutation; donor enforces this branch in source.
4. **Cognition/evolution:** candidate selection and canary mechanics remain bounded; one winner is adopted at a time, but safety depends on correctly persisted evaluation evidence.
5. **Hostile review:** source correction not overclaimed as verified; specific injected-failure regression test absent; donor not selected by authority.

## 5. Open obligations / disposition

| Item | State |
|---|---|
| Ten source blobs inventoried | Complete for slice |
| Candidate/donor durable-evaluation precondition comparison | Complete for source slice |
| Candidate failure path identified | Confirmed by source inspection |
| Donor corrective precondition | Confirmed by source inspection |
| Specific record-failure regression test | Open |
| Native build/test execution | Not executed |
| Consumer/API/owner authority/retention | Open |
| DF-02 | OPEN |

`core/cpp/src/evolution_orchestrator.cpp` remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation gate clearance, or Stage A authorization.
