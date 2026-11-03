# JBP-004 — Memory, Learning, Persistence, and Evolution Integration Challenge

## Purpose

Evaluate whether the existing native cognitive architecture connects memory, experience-dependent learning, persistence/replay, and evolution into a coherent loop. This is a test specification, not a claim that the capabilities already work. Run against an exact, recorded commit; do not use results from another revision as substitutes.

Governing principle: **Engineer the mechanisms; let behavior be acquired through experience.**

This challenge complements JBP-003. JBP-003 already supplies bounded evidence for context-specific acquisition, reversal, control-context preservation, and fresh-process recall. JBP-004 must go further: trace the evidence and state transitions across mechanisms, then test whether the evolution subsystem has a demonstrated causal connection to future cognitive behavior rather than only storing proposals and history.

## Scope and safety rules

- Test branch must be based on the current `feat/jarvis-affective-state` head at the time the run starts. Record base SHA, tested SHA, workflow run ID/attempt, compiler/build type, and seeds.
- Test-only code/workflows belong on a separate test branch. Do not merge the test branch or change PR #97 / PR #100 as part of running this challenge.
- Keep the environment's hidden rule generator and evaluator oracle outside the learner's inputs, memory, prompts, and candidate-action metadata. The learner may receive observations and consequences only through the normal runtime interface.
- Use the existing native runtime, memory journal, developmental learning, prediction-feedback, evolution, and adoption/canary APIs. Do not replace them with a bespoke learner or a scripted answer policy.
- Never loosen thresholds after observing results. A failed seed is a failed challenge, not an outlier to average away.
- Every evaluation phase withholds consequence feedback unless the phase explicitly tests learning from feedback.
- Preserve raw per-episode action/outcome logs, prediction records, memory journal, evolution history/adoption journal, checkpoints, and a machine-readable summary.
- If an expected connection cannot be expressed through existing public APIs, record that as an architecture/integration gap; do not fake the connection in test code.

## Evidence contract: one episode must be traceable

For at least one episode in each tier, and for sampled episodes in long runs, produce a trace keyed by stable episode ID containing:

1. Observation and represented context actually delivered to the runtime.
2. Prediction(s) existing before the action, including key, predicted value, confidence, and sequence.
3. Selected action and decision evidence available to the learner at selection time.
4. Executed action, authorization/execution status, and authoritative observed consequence.
5. Prediction outcome / prediction error, including the exact source prediction sequence.
6. Learning updates attributable to that experience (strategy/association/belief/forecast metrics and their observation counts).
7. Memory event sequence and journal durability result.
8. Any fitness evidence, evolution proposal, safety evaluation, adoption/rejection, canary observation, or rollback linked to the same evidence window.
9. The next relevant decision, demonstrating whether the acquired/revised state actually influenced behavior.
10. After a fresh-process restart, the restored state and its behavioral effect, with no evaluation feedback.

A subsystem counter increment alone is not proof that the experience caused a later behavioral change. Each claimed causal link must identify the source event and before/after measurement.

## Tier 1 — Simple deterministic continuity

**Purpose:** Establish basic event correctness and the smallest complete memory-learning-persistence path.

- Two actions, one context, deterministic outcomes, one initially better action.
- Use a fixed seed and enough balanced exposures to observe both actions.
- Generate a prediction before each selected action and record its actual consequence.
- Restart the operating-system process after training; evaluate with feedback disabled.

**Required checks**
- A valid consequence produces one attributable update; duplicate or malformed feedback does not double-apply learning.
- Prediction resolution refers to the correct prediction sequence, not merely the most recent matching key.
- The selected action improves against the untrained baseline and matches the learned preference in at least 18/20 evaluation choices.
- A fresh process restores the relevant learned state and achieves at least 18/20 without feedback.
- Journal replay reconstructs equivalent action preference, prediction-resolution state, and relevant learning counts; compare normalized semantic state rather than timestamps.
- Unknown or unrelated contexts must not inherit the strategy without sufficient contextual evidence.

**Failure localization:** event validation, source-sequence matching, strategy update, journal append/replay, decision retrieval, or process-boundary restore.

## Tier 2 — Hard: contextual learning under noise and reversal

**Purpose:** Verify context specificity, evidence reliability, adaptation, and protection against catastrophic interference.

- At least three contexts with independently generated hidden action-reward rules.
- Stochastic outcomes with 15–20% outcome flips.
- Interleave contexts instead of training each in a single uninterrupted block.
- Reverse the mapping in one context, leave one context unchanged, and introduce one context after acquisition as a transfer probe.
- Use independent seeds 17, 29, and 43 at minimum.

**Required checks**
- Every seed independently reaches at least 16/20 correct choices in each trained context before reversal.
- After reversal, the changed context reaches at least 48/60 correct within the measured adaptation window; report episode count to recovery, not just terminal accuracy.
- The unchanged control remains at least 54/60 correct.
- Relevant restored contexts meet at least 16/20 after process restart; untouched contexts retain their prior behavior.
- Low-reliability/noisy evidence has less influence than repeated reliable evidence, without being silently converted into the opposite outcome.
- Report preference oscillations, reversal latency, confidence calibration, and any degradation in non-reversed contexts.

**Failure localization:** context representation/retrieval, reliability weighting, belief/strategy revision, cross-context leakage, prediction error attribution, replay ordering, or adaptation dynamics.

## Tier 3 — Very hard: delayed, contradictory, and interrupted experience

**Purpose:** Test long-horizon credit assignment and resilience to process boundaries.

- Four or more contexts and at least three actions.
- Consequences are delayed by a configurable number of episodes; intermediate observations must not be misattributed as the action's consequence.
- Mix reliable evidence, misleading/noisy evidence, neutral outcomes, and missing/unobservable consequences.
- Apply at least two reversals in different contexts at different times.
- Restart the process at least three times: after initial acquisition, during adaptation, and after later consolidation.
- Repeat at least three independent seeds.

**Required checks**
- Delayed outcomes resolve against the original action/prediction IDs; no future outcome is credited to a different action.
- Missing consequence is represented as missing/uncertain evidence, not fabricated negative reward.
- Contradictory evidence changes the affected strategy when sustained, while isolated noise does not cause uncontrolled oscillation.
- All restarts reconstruct behaviorally equivalent state; a checkpoint/journal mismatch is a failure.
- After each reversal, report episodes to 80% rolling accuracy and compare with the same phase without restart.
- Unchanged contexts retain at least 90% of their pre-reversal score, and each revised context reaches at least 80% rolling accuracy within its specified recovery budget.
- Duplicate replay, repeated outcome delivery, and replay of an already rolled-back evolution experiment must be idempotent.

**Failure localization:** delayed-credit association, source identity, event ordering, persistence consistency, duplicate suppression, consolidation, reversal learning, or context isolation.

## Tier 4 — Complex: end-to-end learning ↔ memory ↔ evolution loop

**Purpose:** Verify communication across subsystems and test whether evolution changes actual behavior safely.

Run the following as one instrumented simulation, not as unrelated unit-test assertions:

1. Acquire action preferences from hidden environmental consequences.
2. Record predictions and resolve them against authoritative outcomes.
3. Confirm learning changes the next decisions and that the evidence is journaled.
4. Derive candidate fitness from held-out behavioral measurements, not from the learner's self-reported confidence alone.
5. Propose a bounded evolution experiment using the existing evolution controller.
6. Evaluate the candidate against a baseline on matched held-out episodes, with randomized/interleaved order and no rule leakage.
7. Adopt only if the existing safety gates and independent candidate evaluation support improvement.
8. Run canary observations; trigger rollback when the predeclared degradation threshold is crossed.
9. Restart the process after evaluation, after adoption, and after rollback in separate runs. Confirm history, adoption journal, parameter state, and behavior are consistent.
10. Repeat the next learning cycle using fresh experience to establish whether the full loop continues rather than only replaying one successful result.

**Critical integration gate:** The current code exposes generic evolution parameters and separately exposes learned strategies/decision-making. Existing evolution integration tests establish proposal/adoption/history/persistence, but they do not by themselves prove that adopting a parameter causally changes the native runtime's action selection. The test must identify a real parameter-to-mechanism connection in production code and demonstrate a controlled before/after behavioral effect. If no existing public mechanism supports that connection, report **NOT DEMONSTRATED / ARCHITECTURE GAP**. Do not invent a fake binding inside the test harness or treat a changed stored number as improved cognition.

**Required checks**
- All training, evaluation, fitness, adoption, canary, rollback, and recall episodes have provenance and explicit split boundaries.
- No candidate is selected on the same data used to claim its improvement; use held-out episodes and report sample sizes.
- Adoption is rejected for insufficient evidence, unsafe confidence, invalid/non-finite values, or degraded candidate performance.
- A degraded adopted candidate is rolled back; rollback restores the prior effective behavior and persists across restart.
- An unrelated context does not change merely because an evolution experiment targets a different context/mechanism.
- The learned strategy, memory records, prediction metrics, and evolution records remain mutually consistent after replay.
- The next cycle must use new environmental evidence and show measurable change where justified; repeated replay of identical evidence must not inflate counts or fitness.
- Report the effect size and uncertainty, not only PASS/FAIL: baseline vs candidate accuracy, regret, reversal recovery, context retention, prediction error, and rollback recovery.

**Hard acceptance rule:** Do not declare the entire Tier 4 passed if the evolution parameter only persists in the journal but has no demonstrated effect on a real cognitive mechanism. Mark the evolution-to-behavior gate separately and fail the full integration gate if the connection is absent.

## Stress, fault, and adversarial checks

Run these as dedicated cases in addition to the four tiers:

- Empty journal and first experience.
- Truncated/corrupt journal and invalid metadata; startup must fail safely or recover according to the documented contract without silently inventing state.
- Repeated event delivery, duplicate prediction outcomes, stale sequence IDs, wrong context IDs, and outcomes referencing nonexistent actions.
- Non-finite/out-of-range confidence, reward, fitness, proposal values, and canary observations.
- Journal append failure / unwritable path where injectable; state must not report an update as durable when persistence failed.
- Restart immediately before and after adoption/rollback boundaries.
- Unrelated high-confidence memories competing with relevant low-confidence memory.
- Interleaved context updates with repeated contradictory evidence.
- Evolution proposals with insufficient evidence, misleading fitness, held-out regression, and canary degradation.
- Re-run with identical seeds: deterministic parts should reproduce; stochastic outcomes must be explainable from the seed.

Invalid evidence must not poison state, silently mutate an unrelated context, bypass safety gates, or create a false pass.

## Required report format

For each tier and seed, report:

- Exact tested commit and workflow run ID/attempt.
- Build/test command and exit status.
- Episode counts and the full phase schedule.
- Accuracy/reward/regret by context and phase; reversal recovery latency.
- Prediction counts by category: created, resolved, unresolved, rejected, and reason. Do not label every unresolved prediction a defect; explain its lifecycle and expected observability.
- Memory/journal counts before training, after training, and after each restore.
- Learning-state deltas and concrete examples of a later decision changed by earlier evidence.
- Evolution proposal/evaluation/adoption/rejection/canary/rollback state transitions.
- Before/after behavior for the real mechanism an evolution parameter is intended to influence.
- Any unrelated-context degradation or contamination.
- Raw artifact locations and concise evidence excerpts.
- Failures, known limitations, and the next defect to investigate. Do not weaken acceptance thresholds or aggregate away failed seeds.

## Interpretation

A passing Tier 1 does not imply Tier 2, Tier 3, or Tier 4 passes. A passing learning/persistence challenge does not prove evolution is integrated with behavior. The strongest evidence is a source-attributed chain from experience through memory and learning into a later changed decision, preserved across process restart, with evolution safely evaluated against held-out behavior.
