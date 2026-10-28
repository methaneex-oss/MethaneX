# JBP-004 — Unseen Combination Transfer Challenge

Status: executable behavioral challenge / evidence gate  
Target: existing native cognitive architecture  
Branch: `test/jbp-004-unseen-transfer`  
Baseline commit: `92cce78985f2630f62a6e0beb49ac725623d7d85`

## Purpose

Test whether the existing brain can acquire a reusable relationship from experience and apply it to a combination of observable factors that it has never encountered during training. This is deliberately harder than learning a separate action mapping for each familiar context.

## Environment and protocol

For each deterministic seed (default: 17, 29, 43), the evaluator generates a hidden base preference and uses two observable binary factors: weather (clear/storm) and terrain (flat/rugged). The preferred action follows a two-factor parity relationship. The environment supplies 15% noisy outcomes.

The brain trains in exactly three combinations:

- clear + flat
- clear + rugged
- storm + flat

The combination storm + rugged is withheld from training. The learner is not given the hidden rule or answer table.

After training, the process stops. A fresh process restores the journal and evaluates all four combinations without outcome feedback. Familiar combinations are scored separately from the held-out combination.

## Gates

- Acquisition: at least 12/20 correct in the final training window for each of the three trained combinations.
- Fresh-process familiar recall: at least 12/20 correct for each trained combination.
- Unseen transfer: at least 12/20 correct in the held-out storm + rugged combination.
- All three seeds must pass independently. The workflow records every seed's result rather than stopping at the first behavioral failure.

## What a pass means

A pass is evidence that the tested runtime acquired behavior from consequences and generalized the hidden two-factor relationship to the held-out combination after process restart.

## Limitations

This is still a small, bounded task with two actions and two binary factors. It does not prove broad compositional reasoning, general intelligence, language learning, or open-ended self-improvement. Failure is valuable evidence that should be reported honestly; do not relax thresholds after observing results.

## Evidence

The dedicated GitHub Actions workflow uploads configure/build logs, per-seed behavioral logs, metadata, and journals.
