# DF-02 Attention Salience, Feedback and Persistence Adjudication — 2026-11-27

**Scope:** candidate/donor `attention.cpp`, attention architecture and Brain learning tests.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor adds prediction-error and internal-activation salience inputs; feedback changes policy weights and replay persists them. Source/test inspection only.

## 1. Exact refs

- Candidate `attention.cpp`: `58f734dbe9772675d687752026231297f289e770` (135 tips, 69 lines).
- Donor `attention.cpp`: `67def4987f4a49a852bd2e4c9760f05c2ee15216` (76 tips, 99 lines).
- Candidate attention architecture test: `3a5609ed29e117c2241ce3f23543c8042f5815b2` (136 tips, 61 lines).
- Donor architecture test: `4b6f4ad50b9706e372c51e21803e57438d99d155` (76 tips, 75 lines).
- Donor Brain-attention learning test: `1fa972d9ecffdae8dce49b17356f6f4dc274d1a3` (77 tips, 38 lines; candidate path absent).

## 2. Candidate/donor behavior

Candidate salience uses novelty, uncertainty and urgency. Donor adds prediction error and internal activation as weighted features; each feature is clamped and weights are normalized by total configured weight. Policy reinforcement/suppression changes bounded component weights. The donor Brain test records a prediction, resolves it with error, verifies attention weights change, and reconstructs Brain to verify replay persistence.

## 3. Source-derived gaps

- **Nonfinite policy/input:** `normalized_weight` uses `max(0,value)` without a finite guard; `score` clamps event urgency/error and policy components without rejecting NaN/Inf. NaN can make total weight and salience NaN; `focus` sorts with `salience >`, which is not a reliable strict-weak-order comparator for NaN. `reinforce` similarly accepts nonfinite reward/signal components. Public methods need finite-domain validation.
- **Focus novelty is constant:** `focus(events)` calls `score(event, novelty=1.0, ...)` for every event, so its ranking does not use per-event novelty. It may over-prioritize all events as maximally novel; the API contract should clarify or supply per-event novelty.
- **Feedback direction:** `reinforce` accepts only positive reward; negative feedback must route through `suppress`. Tests cover monotonic reinforcement and suppression bounds but not invalid/nonfinite signals or unintended reward routing.
- **Weight interpretation:** weights are individually bounded but only normalized at scoring; repeated reinforcement changes relative feature balance. No calibration/utility or adversarial stability evaluation is established.

## 4. Test evidence and gaps

Donor tests assert feature-driven salience, policy changes from feedback, internal activation, attention-state ranking/priority learning, and persistence after Brain reconstruction. Source inspected, not executed. Gaps: NaN/Inf weights/events/rewards, focus ordering with varied novelty, repeated reinforcement saturation/oscillation, event-type fairness/starvation, policy recovery from corrupt journal, and calibrated attention utility.

## 5. Five review lenses

1. **Semantic:** donor prediction-error/internal-activation expansion confirmed.
2. **Build/test:** source and two donor tests inspected; no native test execution.
3. **Integrity:** nonfinite inputs can contaminate attention policy/scores.
4. **Cognition:** adaptive salience mechanism exists; attention ranking isn't calibrated relevance and focus novelty is constant.
5. **Hostile review:** no claims of effective real-world attention; gaps explicit.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Candidate/donor source/test blobs | Verified |
| Prediction-error/internal-activation behavior | Inspected |
| Policy persistence | Test contract inspected |
| Nonfinite validation | Gap |
| Per-event novelty focus | Gap/contract |
| Adversarial and behavioral utility tests | Open |
| Full consumers/authority/retention | Open |
| Native tests | Not performed |
| DF-02 | OPEN |

Attention remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.

 
## Historical execution evidence for donor attention-learning suite — 2026-11-28

The donor-only Brain attention-learning test blob 1fa972d9ecffdae8dce49b17356f6f4dc274d1a3 is present unchanged on historical alternate branch e737cae7f907696ef787a4e85b0dee3a739d71b1 and is registered as CTest #14 by donor tests/CMakeLists.txt. It is absent from candidate CMake. The test records a prediction, resolves it with error, verifies attention policy weights change, and reconstructs Brain to verify replay persistence.

CTest #14 passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer, and Brain ThreadSanitizer #957; all five jobs report 71/71. The attention architecture suite at CTest #13 also passed in the same jobs. This is execution evidence on the historical alternate branch, not current PR #203 or frozen candidate evidence.

The passing test does not close the source-derived gaps: nonfinite input validation, constant novelty in focus ranking, calibration/utility of attention weights, event starvation/fairness and corrupt-journal recovery remain untested or unresolved.
