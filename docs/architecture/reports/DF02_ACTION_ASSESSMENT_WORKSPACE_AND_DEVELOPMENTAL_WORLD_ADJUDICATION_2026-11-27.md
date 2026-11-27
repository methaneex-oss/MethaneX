# DF-02 Action Assessment, Strategy Workspace and Developmental-World Primitive Adjudication — 2026-11-27

**Scope:** candidate/donor ActionModel, strategy/workspace APIs, goal-outcome evidence, and donor developmental environment/world primitives.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** action assessment, strategy formulation, workspace snapshot and test-world primitives are bounded mechanisms. A concrete action-confidence/risk validation defect is identified. Source/test inspection only.

## 1. Exact refs

- ActionModel header candidate `6a3b1720d5b58630faf320ba1e3c082cb417b7a9`; donor `a4e67038e57eb7637e53a532b8da62f2d0f68727`.
- ActionModel test candidate `24f419a4ff469995bbc5961974c7ee3b869c9911`; donor `e2e0ecf121ab866f5793bb63c2f605ec5f68dafa`.
- CognitiveWorkspace header candidate `b015d44e332ea2511d29e607495714d0b982d44e`; donor `e002025dd69183311b41afa9d57c2b0780b7f7f8`.
- Workspace test candidate `ae938f5df02d8f907a548c446c01e17fbd2f1470`; donor `b29e75aa8b0e289c01f2e9188d26c639cfa1f22d`.
- Donor strategy header `a5b153e9e4044cda97f261a053786b38fc70e76e`; source `5406a341cd4b3f42e16166f6122a0cb580aee298`.
- Donor goal-outcome header `c986480d82b9951177031f3387169819c3856234`.
- Donor developmental environment `913c8cca2a03499249b834a890812c57b9aa4b1a`, world `2ba5bdbfc6db1f24eff8eb0a20ee145d0efc16cf`.
- Donor world/environment/training tests: `bd8f6767cdcf6513674730f24c184bac6600e116`, `a3fa73f78b56a3ea04cdfb6b1bf16739f0894d5d`, `62a0ee4f8ec966e48a45848217ba7a6d6e96196f`.

## 2. Action assessment defect

`ActionModel::assess` computes confidence as `unit(1-risk) * unit(score >= 0 ? 1 : 0)`. It does not use `CandidateAction.confidence`, expected value, or score magnitude. A low-confidence action with nonnegative decision score and zero risk can receive confidence 1 and disposition Execute/permitted. A nonfinite action risk is converted to zero by `unit`, so NaN risk can be treated as safest risk.

The model checks maximum risk and optional reversibility, but does not enforce required permissions, resource cost, capability availability or output schema; these belong to later execution/authorization layers. The ActionModel test covers basic risk/reversibility and only checks finite confidence for one NaN input; it does not assert rejection or low-confidence behavior.

## 3. Strategy/workspace semantics

`StrategyModel::formulate` copies intent and derives planning context from attention, threat, uncertainty and resource budget. Inputs use `std::clamp` without explicit finite guards; NaN salience/threat/uncertainty may propagate. Resource budget uses `std::max(0,value)`, which can convert NaN to zero depending comparison behavior.

`CognitiveWorkspaceStore` is a mutex-protected value snapshot with replace/clear; it is not persistent, versioned or a consistency transaction across Brain state. Runtime tests assert basic observation/representation/attention/cycle fields.

`GoalOutcomeEvidence::normalize` clamps progress/confidence and recomputes delta but lacks finite guards; NaN can persist. `GoalProgressModel` counts only positive/negative deltas for confidence averaging; neutral evidence does not increase the denominator, though progress is overwritten with the latest value. It is a lightweight feedback accumulator.

## 4. Developmental environment/world contract

Donor `DevelopmentalEnvironment` and `DevelopmentalWorld` are test/evaluation primitives, not cognitive policy:
- the environment owns transition callbacks and exposes observations/outcomes; execution failure yields unobserved consequence;
- the world supports seeded randomness, hidden state, filtered observations, action availability, resources, state updates, exogenous dynamics, terminal conditions and episode reset;
- callback failure in world transition fails closed; dynamics failure preserves action consequence and records an event.

Source-derived gaps:
- `DevelopmentalWorld` constructor normalizes invalid initial resources to 0, but `reset_episode()` without explicit resources can restore the invalid `config.initial_resources` (negative/NaN) instead of normalized 0;
- world `set_state` and transition/dynamics state updates accept arbitrary keys/scalars without validation;
- `observation_filter` exceptions are not caught;
- simple `DevelopmentalEnvironment::step` transition callback exceptions are not caught (unlike DevelopmentalWorld);
- fixed transition functions are test-fixture rules, not evidence of fixed cognitive outcomes; no test-world isolation is provided against callback capture of external state.

Donor world/environment tests assert hidden-state filtering, resource use, unavailable/unknown action neutrality, state-dependent outcomes, exogenous dynamics, terminal/reset, contradiction across contexts and learning-loop behavior. Source/test inspection only.

## 5. Five review lenses

1. **Semantics:** assessment and strategy/workspace contract compared; world is external fixture.
2. **Build/test:** donor source/test inspected; no native execution.
3. **Integrity:** ActionModel confidence ignores action confidence and treats nonfinite risk as zero; strategy/goal evidence and world state inputs need finite/schema checks.
4. **Cognition:** workspace is snapshot storage; world is synthetic evaluation, not autonomous perception.
5. **Hostile review:** test transition rules not misrepresented as cognitive hardcoding; no safety/effectiveness claim.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| ActionModel candidate/donor/test | Compared |
| Confidence/risk defect | Gap |
| Strategy/workspace | Source/test inspected |
| Goal outcome finite validation | Gap |
| Developmental world/environment | Source/test inspected |
| Reset/callback/input validation | Gaps |
| Native tests | Not performed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Action-assessment/workspace/world primitives remain **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
