# JBP-002 — Deep Learning, Persistent Knowledge, and Cognitive Evolution

Status: specification / implementation contract  
Target: existing native cognitive architecture  
Deadline context: 31 October 2026  
Branch: `test/jbp-002-deep-learning-persistence`

## Purpose

Evaluate whether the existing brain can acquire non-trivial structure from training experience, reuse it in unfamiliar compositions, retain it across process restarts, revise it when evidence contradicts it, and improve subsequent performance through supported learning/evolution mechanisms.

This is not a replacement for DLT-002 or JBP LEARN-002. Those trials measure changing-context action learning. JBP-002 must test acquired knowledge and multi-step transfer, not merely extend the duration of the navigation environment.

## Non-negotiable constraints

- Test the existing cognitive architecture; do not implement the answers in the test harness or add a task-specific lookup table to the brain.
- Generated training examples may contain ground-truth labels for the evaluator, but those labels must not be passed to the brain before its prediction/action is recorded.
- Separate training examples, validation examples, and held-out evaluation examples by deterministic seed and explicit provenance.
- Record the exact tested commit SHA and all seeds/configuration in every artifact.
- Preserve existing memory journals and evidence; never silently overwrite a prior or interrupted run.
- Do not equate a successful build, a green workflow, an accepted evolution proposal, or a high training score with demonstrated learning.
- Reuse existing C++ interfaces and the current toolchain. Do not add languages or dependencies without explicit approval.
- If a capability is not exposed by the existing architecture, report it as a measured gap. Do not simulate it with hardcoded answers and call it learning.
- Keep this work isolated from PR #105 (short-horizon controlled learning stress test), PR #100 (learning diagnostics), and PR #97 (main cognitive/affective development).

## Required stages

### A. Concept/relationship acquisition

Use a deterministic generator to create an unfamiliar symbolic domain with entities, attributes, and relations. The brain receives examples as observations/experience and feedback only where the protocol permits it. Ground-truth labels stay evaluator-side.

Measure:
- training performance over time;
- held-out performance;
- performance on novel combinations of learned relations;
- examples/episodes required to reach a predeclared threshold;
- whether internal state actually changes after relevant experience.

The evaluator must verify that held-out items were never presented to the learner and that no answer mapping is embedded in the harness-to-brain input.

### B. Multi-step composition

Construct problems requiring multiple dependent inferences from separately acquired relations. Include irrelevant facts, ambiguous evidence, and contradictory evidence. Vary chain depth and branching factor by seed.

Measure final-answer correctness, intermediate-step correctness where exposed, error propagation, and performance as depth increases. Count useful correct outcomes, not internal operations alone.

### C. Recognition / language-like structure

Start with a bounded generated symbolic grammar or relation-recognition task only if existing input and learning interfaces can support it. Test unseen sequences and novel compositions rather than exact string recall. Do not claim natural-language learning unless the tested pathway actually accepts and learns natural-language structure.

### D. Persistent acquired knowledge

Train, stop the process, create a fresh process, restore from the persisted state, and evaluate with held-out prompts that require the pre-restart knowledge. Continue training after restoration and test both old and newly acquired knowledge.

Report separately: stored, restored, retrieved, used correctly, revised correctly, and retained after further learning.

### E. Contradiction and adaptation

After acquisition, change a subset of relationships and provide evidence incrementally. Measure how many observations are needed to revise behavior, whether stale knowledge is still used, and whether unrelated knowledge remains intact.

### F. Evolution and regression

Record baseline performance before an evolution/strategy change. If the existing system proposes or adopts a change, evaluate it on held-out tasks and on previously solved tasks. Report improvement, regression, rollback, and post-restart persistence. An accepted proposal is not itself evidence of improvement.

### G. Integrated end-to-end challenge

Trace at least one experience through the actual available mechanisms: observation/representation, prediction or inference, action/response, outcome feedback, learning-state update, persistence, restart, retrieval, and changed later behavior. Include an unrelated-context control.

## Experimental controls

- At least three independent deterministic seeds for the full trial.
- A feedback-enabled learner and a matched no-feedback/control condition where the existing interface makes that comparison valid.
- Training-only and held-out metrics reported separately.
- Evaluation labels withheld until the learner's output is recorded.
- Negative and contradictory examples.
- Fresh-process restoration, not only same-process reload.
- Per-stage and per-seed results; no aggregate score may hide a failed stage.
- Raw episode/task traces, checkpoints/journal metadata, prediction/error records where available, and a machine-readable summary.
- Any missing metric or unsupported interface must be reported as missing/unsupported, not silently omitted.

## Acceptance interpretation

JBP-002 is an evidence-gathering challenge, not a guarantee that every stage will pass. Each stage should return one of:
- PASS: required behavioral evidence is present and meets a predeclared threshold;
- FAIL: the task ran and the required behavior was not demonstrated;
- INCONCLUSIVE: evidence was insufficient, contaminated, or invalid;
- UNSUPPORTED: the current architecture exposes no honest path to test the capability.

Do not set arbitrary accuracy thresholds before running a baseline. Define task difficulty and baseline first, then record thresholds before evaluating the learner.

## Implementation gate before writing the executable

Before implementing a task harness, map the existing native APIs for:
1. representing/ingesting training examples;
2. retaining relations or learned representations;
3. retrieving and using them in inference/decision-making;
4. feeding evaluator-independent outcomes back into learning;
5. serializing and restoring the relevant learned state;
6. observing strategy/evolution changes and their effects.

If the architecture only supports fixed input-to-action learning in the relevant path, the test must state that limitation. Do not make a bespoke symbolic learner inside the test executable, because that would test the harness rather than JARVIS.
