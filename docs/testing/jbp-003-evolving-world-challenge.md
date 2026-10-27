# JBP-003 — Evolving Virtual World Challenge

Status: executable challenge / evidence gate  
Target: existing native cognitive architecture  
Branch: `test/jbp-003-evolving-world-challenge`

## Purpose

Test whether the existing brain learns context-sensitive action consequences in a generated virtual environment, adapts after a targeted environmental reversal, preserves an unrelated context, and can use the acquired behavior after a fresh operating-system process restores the journal.

This deliberately goes beyond checking that information is stored. The learner must select actions; the environment alone determines consequences; the evaluator measures choices against a hidden rule.

## Protocol

For each deterministic seed (default: 17, 29, 43):

1. Generate a hidden action/reward mapping. The evaluator knows it; the brain does not receive it.
2. Train across two observable contexts (`sim/clear`, `sim/storm`) with 15% stochastic outcome flips.
3. Evaluate the final 20 acquisition episodes in each context. Require at least 12/20 correct in each context.
4. Reverse only the storm-context mapping while leaving clear unchanged.
5. Continue learning for 60 episodes per context. Require at least 36/60 correct in each context; report the separate values so degradation cannot hide in an aggregate.
6. Stop the training process. Start a new process and restore the same journal.
7. Evaluate 20 episodes per context without delivering outcome feedback. Require at least 12/20 correct in each context.
8. Preserve logs, tested commit, and a copy of each journal as workflow artifacts.

The hidden rule is generated from the seed and kept inside the environment/evaluator. The brain receives the visible weather/context, candidate actions, and (during training) consequences of the action it actually selected.

## What this can demonstrate

- acquisition from action consequences rather than a supplied answer table;
- context-specific behavior under stochastic outcomes;
- response to a targeted reversal;
- retention of an unchanged-context control;
- persistence and behavioral recall in a fresh process without evaluation feedback.

## What this cannot demonstrate

A pass does not prove general-purpose reasoning, broad compositional concept learning, natural-language acquisition, visual recognition, or open-ended self-improvement. The task is still a bounded action-learning environment. Results must be reported per seed and per stage. Do not weaken thresholds after observing the results; a failure is useful evidence of a current limitation.

## Execution

The dedicated workflow builds `jarvis_jbp_003_evolving_world_suite`, runs `train` and `verify` as separate processes for each seed, and uploads raw evidence. The executable refuses to overwrite an existing training journal.
