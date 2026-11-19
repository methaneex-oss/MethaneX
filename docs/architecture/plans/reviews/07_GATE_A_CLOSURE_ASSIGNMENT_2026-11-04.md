# Gate A Closure Assignment — Risk-Based Evidence Completion

**Date:** 2026-11-04  
**Applies to:** PR #175 — `plan/brain-implementation-roadmap-20261103`  
**Assignment baseline:** PR #175 HEAD `b4ffa1ea27dadd02cbe8f9246bd96fecc26c450c`  
**Governing specification:** Accepted PR #174 HEAD `0811a59e46bf934e32e794f90e4e7d18d4e2bd97`  
**Status:** Assigned for documentation/static-review work; Gate A remains NOT CLEARED  
**Authority:** Project Director's "Ok proceed" to prepare and execute a focused Gate A closure assignment  
**Scope:** Evidence reconciliation, static compatibility analysis, workflow disposition, defect planning, and independent-review readiness only

---

## 1. Purpose

Convert the latest independent Gate A review into a bounded closure programme. Establish whether the candidate implementation tree has sufficiently explained provenance, API compatibility, workflow continuity, and candidate-specific risk to support a defensible baseline decision.

The purpose is not to prove that every inherited commit has a standalone prose record. The purpose is to explain the final candidate tree and investigate changes whose origin, semantic effect, compatibility, or verification path could change the baseline decision.

**Current disposition remains: GATE A NOT CLEARED. No implementation baseline is selected. PR #156 remains a candidate only.**

## 2. Binding authority limits

This assignment authorizes:
- static repository inspection and source/API/workflow comparison;
- risk-based provenance analysis of existing history and final-tree paths;
- documentation of findings, evidence, unresolved questions, and proposed dispositions;
- preparation of an independent-review package.

It does **not** authorize:
- runtime source or test changes;
- builds, tests, benchmarks, fuzzing, sanitizers, or workflow execution;
- API/schema/dependency/technology selection;
- cherry-picking, rebasing, merging, history rewriting, or changing PR #156;
- implementation, release, deployment, or external-world execution.

The two candidate defects remain recorded findings. This assignment may specify remediation and acceptance criteria, but must not implement them or claim they are fixed.

## 3. Closure workstreams

### A — Risk-based provenance and final-tree integrity

**Question:** Is every material part of the candidate tree attributable to a known origin or explicitly identified as unresolved, and have all unexplained/high-risk overlaps been investigated?

**Starting evidence:**
- 1,416 inherited commit SHAs enumerated;
- 165-path final-tree delta reconciled (145 PR #97-only, 14 modified in both PR #97 and post-PR #97 segments, six first introduced after PR #97);
- 172-commit post-PR #97 segment decomposed into 10 preparation, 153 PR #148, and nine PR #155 integration commits;
- PR #156 contains 12 code-bearing commits plus one documentation commit;
- exhaustive per-commit origin/path/hunk attribution remains incomplete, especially across the 1,244-commit PR #97 history.

**Required work:**
1. Reconcile the 165 final-tree paths against the recorded origin categories and integration segments.
2. Identify paths with multiple origins, overlapping edits, replacements, deletions, conflict resolutions, or semantic adaptations.
3. Prioritize provenance review for Brain public interfaces, authoritative state owners, journal/replay/persistence, learning/evolution, execution evidence, and CI/workflow gates.
4. For each prioritized path, record source origin(s), relevant commit/PR segment(s), final candidate blob, semantic change summary, and whether the path's integration is explained.
5. Classify remaining history gaps as: decision-relevant unresolved; bounded low-risk/unexplained; or adequately explained by final-tree and integration evidence.
6. Do not assert complete commit-to-hunk attribution. If GitHub pagination/tooling prevents a complete ledger, state the exact coverage boundary and evidence that remains unavailable.

**Exit evidence:** A path-level provenance matrix covers all 165 paths, with deeper commit/hunk evidence for every unexplained, overlapping, or high-risk path. Every residual gap has an explicit risk and decision impact. The reviewer can trace the candidate's material code-bearing areas to evidence without relying on Builder assertions alone.

**Decision rule:** Individual attribution for all 1,416 commits is not an automatic prerequisite. It becomes necessary where a commit or group of commits is needed to explain a material final-tree change, a conflict/overlap, a suspicious provenance break, or a high-risk semantic change. No unexplained high-risk path may be waived by aggregate counts.

### B — API declaration, caller, and compatibility assessment

**Question:** Are the candidate APIs compatible with their declarations, callers, overloads, and integration expectations, beyond matching method names?

**Required work:**
1. Reconcile candidate and current-main declarations for all 64 common unique Brain method names and all overload/definition occurrences relevant to the 24 classified body differences.
2. Assess `register_evolution_parameter()` bool-versus-void return change: declarations, direct callers, wrappers, callbacks, function-pointer/member-pointer uses, templates, and any ABI-sensitive boundary visible in source.
3. For each of the seven candidate-only APIs, identify declaration, definition, call sites, tests, persistence/replay implications, and whether it is internal, public, compatibility-sensitive, or orphaned.
4. Identify removed/renamed/changed signatures and any call-site adaptation required by candidate integration.
5. Separate source-level compatibility conclusions from ABI/build compatibility, which cannot be certified without authorized compilation/linking.

**Exit evidence:** A compatibility matrix records symbol/signature, candidate and comparison declarations, caller inventory, overload/function-pointer evidence, impact, and disposition. Any item that requires compilation or runtime proof is explicitly marked unverified rather than inferred safe.

### C — Workflow continuity and verification entry points

**Question:** Does the candidate preserve the verification capabilities supplied by the five current-main workflows, whether unchanged or through an equivalent/adapted workflow?

**Required work for each workflow:**
1. Record its trigger, inputs, source-ref behavior, seeds/configuration, build/test commands, test targets, artifacts, and purpose.
2. Map each behavior to an existing candidate workflow or documented adaptation.
3. For `.github/workflows/jbp-mem-001.yml`, explicitly disposition missing `source_ref` and tested-commit metadata.
4. For `.github/workflows/jarvis-learning-mechanisms.yml`, map all 35 target names and the integrated changing-environment trial. Target-name presence in CMake is only static wiring evidence, not proof of build/pass equivalence.
5. For `.github/workflows/jbp-brain-int-001.yml`, map all five integrated suites, persistence, and DLT-002 coverage; do not call the candidate persistence/DLT-002 overlap equivalent to the five suites.
6. For `.github/workflows/jbp-learning-002.yml`, map the three independent DLT-002 trials, source-ref control, seed-base control, and whether candidate seed sweep behavior is equivalent.
7. Preserve the exact unchanged DLT-002 workflow where already identical; do not copy workflows blindly or alter workflow files under this assignment.

**Exit evidence:** A five-row workflow continuity matrix gives each workflow one disposition: unchanged, equivalent existing coverage, adaptation required, or capability not preserved. Each claimed equivalence is supported by matching trigger/configuration/coverage semantics, not merely matching filenames or CMake target names. Required adaptations are specified as future work, not applied.

### D — Candidate correctness risks and remediation acceptance criteria

**Question:** Are the two independently confirmed candidate defects fully specified so they cannot be lost or mistaken for baseline rejection/approval?

**Defect D1 — Learned-strategy context mismatch**
- Candidate `Brain::choose()` and `choose_with_affect()` use `eligible.front().id` for learned-strategy retrieval.
- `GoalModel::eligible()` includes pending and active goals; `IntentModel::select()` selects among active goals using its own scoring.
- Required remediation concept: derive strategy context from the actually selected active intent; define an explicit fallback when no intent is selected.
- Required future regression acceptance: a high-priority pending goal and a different selected active goal must not cause strategy retrieval from the pending goal; no-active-intent behavior must use the documented fallback; both choose paths must be covered.

**Defect D2 — Non-finite goal creation can be journaled**
- `Brain::create_goal()` can append a goal event before `GoalModel::create()` rejects non-finite values; NaN is the demonstrated persistence-integrity case because it can survive `std::clamp()`.
- Positive and negative infinity are clamped by the inspected code, but the consistent contract is to reject all non-finite priority/progress values before event construction/journaling.
- Required remediation concept: validate finiteness before any event creation or append.
- Required future regression acceptance: NaN, positive infinity, and negative infinity for each applicable numeric field must be rejected without journal mutation, replay-visible event, or goal-state mutation.

**Required work:** Maintain separate defect records with exact source blob references, affected symbols, failure mechanism, remediation invariant, regression acceptance criteria, and explicit status "confirmed; not fixed; runtime work unauthorized."

**Exit evidence:** Both defects have complete, reviewable remediation specifications and remain visible in the Gate A disposition. They are not treated as automatic proof that PR #156 must be rejected; their severity, fixability, and verification burden inform the candidate assessment.

### E — Independent-review readiness and review request

**Question:** Can an independent reviewer assess the complete closure evidence at one pinned PR head?

**Required work:**
1. Assemble links to the Gate A checkpoint, final disposition, semantic addendum, this assignment, API matrix, provenance matrix, workflow matrix, and defect records.
2. Pin the exact PR head and list all documents/blobs reviewed.
3. State which findings are independently confirmed, Builder-only, inferred, or unverified.
4. Request review only when the Project Director supplies an actual GitHub username/team with repository access, or an authorized independent reviewer is otherwise identified.
5. Do not treat the supplied independent-review report as a submitted GitHub review. Do not invent an identity or claim a formal review request was sent.
6. Ask the reviewer to challenge the risk-based provenance threshold itself, not merely accept it.

**Exit evidence:** A complete review packet is available at one exact head and the actual reviewer identity/request state is accurately recorded. Formal independent review remains an external dependency until a real reviewer is identified and submits a verdict.

## 4. Required consolidated evidence artifacts

Create or update separate files under `docs/architecture/plans/reviews/`:

1. `08_GATE_A_RISK_BASED_PROVENANCE_MATRIX_2026-11-04.md`
2. `09_GATE_A_API_COMPATIBILITY_MATRIX_2026-11-04.md`
3. `10_GATE_A_WORKFLOW_CONTINUITY_MATRIX_2026-11-04.md`
4. `11_GATE_A_CANDIDATE_DEFECT_DISPOSITION_2026-11-04.md`
5. `12_GATE_A_INDEPENDENT_REVIEW_PACKET_2026-11-04.md`

Do not populate a matrix with unsupported assumptions. Use "not yet inspected", "not available from current tooling", or "requires authorized runtime verification" where appropriate. A blank or unresolved cell is preferable to fabricated certainty.

## 5. Final Gate A exit criteria

Gate A may be recommended for clearance only when all of the following are true:

- **Provenance:** all final-tree paths are accounted for at path level; all unexplained, overlapping, and high-risk changes have sufficient deeper attribution; remaining gaps are explicitly bounded and not decision-critical.
- **API compatibility:** declaration/caller compatibility has been assessed for changed and candidate-only APIs; unresolved ABI/build questions are called out and have an appropriate later verification gate.
- **Workflow continuity:** all five workflows have explicit evidence-based dispositions; no critical verification capability is silently lost.
- **Defects:** D1 and D2 have explicit remediation and acceptance criteria, remain recorded as unfixed, and are assigned to the correct later implementation/verification authorization.
- **Independent review:** an actual independent reviewer has examined the complete evidence and challenged the proposed baseline disposition.
- **Project Director decision:** the user explicitly accepts the recommendation and selects or rejects a baseline. Reviewer approval alone does not select it.

If a technical issue is remediable but cannot be verified under current authorization, record it as a conditional implementation prerequisite rather than pretending it is closed. If an issue is baseline-critical and unresolved, Gate A remains NOT CLEARED.

## 6. Execution order and boundedness

1. Produce the four technical matrices/defect disposition from existing source and documentation evidence.
2. Reconcile all 165 final-tree paths against the provenance matrix; deepen only unexplained/overlapping/high-risk paths.
3. Assemble the independent-review packet at the verified PR head.
4. Obtain a real reviewer identity from the Project Director if one is not already available.
5. Request and await independent review; record the actual review state.
6. Present a concise Gate A decision brief to the Project Director.

Do not restart the 1,416-commit enumeration, repeat already completed comparisons, or expand into a general architecture redesign. Stop investigating a historical detail when its origin and effect are sufficiently established and further detail cannot change the baseline decision. Do not stop where a material path remains unexplained.

## 7. Current known state at assignment

- PR #175: `b4ffa1ea27dadd02cbe8f9246bd96fecc26c450c` at assignment preparation; verify live head before each write/review request.
- Gate A: NOT CLEARED.
- PR #156: candidate only; not selected.
- Gate B: static traceability for BM-01 through BM-12 complete; mechanism capability acceptance not passed.
- Two candidate defects: independently confirmed by the supplied review; not fixed.
- Full per-commit origin/path/hunk ledger: incomplete; replace unbounded requirement with the risk-based criterion above, subject to independent challenge.
- Formal GitHub review: no independent reviewer identity supplied; no formal review request or submitted review may be claimed.
- Runtime modifications, builds, tests, history operations, and implementation: not authorized.

---

**Builder instruction:** Execute the documentation/static-analysis workstreams above against the pinned candidate and comparison refs. Keep every conclusion tied to exact paths, blobs, signatures, call sites, or workflow definitions. Update the separate evidence artifacts and handoff. Return Gate A as NOT CLEARED unless every exit criterion is evidenced and the independent review plus Project Director decision have occurred.
