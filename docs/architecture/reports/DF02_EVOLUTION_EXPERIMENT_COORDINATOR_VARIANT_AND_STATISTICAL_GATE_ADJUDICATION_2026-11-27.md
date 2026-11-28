# DF-02 Evolution Experiment Coordinator Variant and Statistical-Gate Adjudication — 2026-11-27

**Scope:** thirteen exact coordinator source blobs, thirteen test blobs, candidate/donor headers and `EvolutionTrials` contract.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor materially strengthens trial-start/isolation requirements and attestation, but the confidence metric is a heuristic, not a statistical confidence interval. Source inspection only; tests not run. Path remains OPEN.

## 1. Exact source inventory

Thirteen source blobs (candidate, donor, 11 alternates) were captured and inspected in the frozen artifact.

| SHA | Role | Tips | Representative branch | Lines |
|---|---|---:|---|---:|
| `c689d16b31c039a7be9ab5c9bde0de49e677b32d` | Candidate | 137 | architecture/brain-foundation-planning20261103 | 75 |
| `93d2e01c785ed4867efec07673cd802afbe27427` | Donor | 33 | ci/priority-one-provenance-validation20261031 | 84 |
| `17a5e826ef3c95592e057f9eb51bfdf043e6fb81` | Alt | 9 | feat/prediction-developmental-validation20261030 | 166 |
| `4f9cbbe9d6f9df093345a5bd5eb23465fde43493` | Alt | 3 | fix/evolution-lifecycle-final-review20261029 | 161 |
| `555d0a5ed164294424aefdbcd0bd81a1382e7d57` | Alt | 3 | fix/evolution-lifecycle-ready20261029 | 153 |
| `74005da8d126159d599c2ddce14837cbe39d6b8f` | Alt | 3 | feat/evolution-statistical-gates | 90 |
| `76db9b56d6ad3ea34b99754fcb1e9ac02d0e2212` | Alt | 1 | feat/evolution-statistical-evaluation | 90 |
| `8d5b1a37425302b1c774efb547a951bfe7f268d3` | Alt | 1 | fix/evolution-lifecycle-review20261029 | 119 |
| `941dc0567178f9e517d831adee5b888d7709d001` | Alt | 1 | fix/evolution-trustworthy-lifecycle20261029 | 105 |
| `acee94e698f96d72d261fe919d327b096eca439e` | Alt | 2 | fix/evolution-evaluation-lifecycle-ci20261029 | 152 |
| `af22ef9413d059428a25108c5f19ae736dac1994` | Alt | 1 | fix/evolution-lifecycle-verified-final20261029 | 163 |
| `bd09173b144168eccfdd1107ac17afc381c410a4` | Alt | 1 | fix/trusted-evolution-lifecycle20261029 | 155 |
| `bdb75242f16364df14993ffac194257e4eeaf936` | Alt | 1 | fix/evolution-evaluation-lifecycle20261029 | 146 |

Owner counts/branch names do not prove authority or semantic ancestry.

## 2. Candidate/donor exact delta

Candidate coordinator SHA `c689d16b31c039a7be9ab5c9bde0de49e677b32d` runs baseline and candidate trials, validates completion/timeout/output cap/finite fitness, summarizes, requires at least two samples, and gates on gain plus confidence threshold. It does not check `started`, enforce isolation, bind an isolation attestation, or set experiment isolation provenance.

Donor coordinator SHA `93d2e01c785ed4867efec07673cd802afbe27427` adds:
- checks `started` for each baseline/candidate result;
- default `require_isolation=true` and rejects non-isolated results when required;
- tracks isolation across **all** trials and stores `experiment.isolated`;
- creates an isolation attestation only when all trials were isolated and the outcome is not Invalid;
- retains an explicit `require_isolation=false` mode for controlled simulation/testing, with adoption safety policy expected to independently decide admissibility.

Candidate header SHA `2fde3fdf0b3e6772f11358385e069f9b94af34d0`; donor header SHA `b7bf85429096b4d3b50c417b929564c2b15ed826`. Donor adds the default-on isolation requirement and explicit simulation/testing comment. The `EvolutionTrials` header blob is identical at both frozen refs (`12555232deb8612abef0afee27cfc5ff5cb1fab6`).

## 3. Confidence semantics — material finding

Candidate/donor exact `evolution_trials.cpp` blob SHA `4e6192c3d06560c826f8beaf507a546d4c56952a` computes:
- mean and sample variance (Welford);
- standard error;
- `confidence = clamp(1 / (1 + standard_error), 0, 1)`;
- `supports_adoption` when candidate mean gain strictly exceeds minimum improvement and the **minimum of the two individual heuristic confidence scores** meets the configured threshold.

This quantity is a monotonic heuristic based on standard error, not a calibrated probability, hypothesis test, p-value or confidence interval for the difference. Constant fitness values yield standard error zero and score 1.0; low sample counts can pass if dispersion is small. No statistical guarantee follows from the field name `confidence`.

Historical variants `74005da8...` and `76db9b56...` expose comparison-evidence/difference-confidence-interval paths; `941dc056...` includes a statistical-evaluation branch. Those are distinct content families. Their existence does not establish they are valid statistical methods, but the exact frozen donor has no such difference-CI field/path in this coordinator. The method should not be described as statistical significance without a validated design.

Another experimental-design concern: coordinator runs all baseline trials before all candidate trials. Without randomization/interleaving or environment controls, time-varying conditions can confound the difference. Trial executor independence, distribution assumptions, reproducibility and sample-size adequacy are not established here.

## 4. Test contract and reachability

Candidate test blob `83d884dd97cbcf2d002249a70e44bb29e6ac0560`; donor test blob `5b410197e3c5e48acb381e274ae22e8ba037aa84`. Both are 31 lines and assert a single deterministic positive case: four baseline fitness results at 0.70, four candidate results at 0.80, minimum gain 0.05, minimum confidence 0.5, expected Improved outcome and counts.

The donor test explicitly sets `require_isolation=false` (controlled fixture); returned SandboxResult values still mark isolated=true. This test does not cover default-on isolation, failed/not-started trial, timeout/output cap, nonfinite fitness, minimum count, variance, neutral/degraded outcome, attestation invalidation, or order/environment bias.

Candidate and donor test CMake register the coordinator suite; registration is not test execution. No tests were run in this audit.

## 5. Five review lenses

1. **Semantic:** start/isolation provenance delta and statistical-gate semantics confirmed.
2. **Build/test:** candidate/donor test source and registration inspected; one deterministic positive fixture only, no execution.
3. **Security/trust:** isolation bit is backend-reported; enforcement and attestation depend on sandbox/backend contracts. Simulation override must remain separately policy-gated.
4. **Evaluation quality:** mean/variance/SE computed; heuristic score is not inferential confidence. Sequential runs risk confounding; statistical validity and evaluation design open.
5. **Hostile review:** no claim that donor is canonical; historical CI variants are not automatically better; safety and confidence naming gaps surfaced.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| 13 exact source blobs inventoried | Complete for slice |
| Candidate/donor source/header delta | Complete for bounded comparison |
| Confidence semantics assessed | Heuristic, not statistical confidence |
| Test variants and CMake reachability | Source-inspected; not executed |
| Failure/isolation/variance/design tests | Open |
| Consumer/API/owner authority/retention | Open |
| DF-02 | OPEN |

`core/cpp/src/evolution_experiment_coordinator.cpp` remains **OPEN / NO AUTHORITY DECISION**. No implementation selected, adopted, retired or deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
