# DF-02 Evolution-Brain Integration Test Variant Adjudication — 2026-11-28

**Scope:** exact 24-blob historical cohort for `core/cpp/tests/evolution_brain_integration_suite.cpp`, candidate/donor test-contract comparison and build registration.  
**Candidate:** frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Evidence:** discovery artifact #14956148301, archive SHA-256 `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Disposition:** test-contract and variant inventory source-inspected; no tests run.

## 1. Exact 24-blob ownership inventory

The path has 24 distinct blobs. Candidate-shaped version has 119 tip-presence rows; donor version 13. Branch/tip owner data is preserved in the discovery artifact and is provenance only.

| Blob SHA | Tip count | Lines | Assertions | Role |
|---|---:|---:|---:|---|
| `20826e72acc770b12f9f1553ff589fac77f3ee4b` | 1 | 340 | 100 | Alternate |
| `21519fb2a57458eb86d28ac72aeb9af7b39af249` | 1 | 228 | 78 | Alternate |
| `2829d0e738499bf0900ab0a322722b4aa9a1bcbf` | 3 | 403 | 103 | Alternate |
| `3164cbc19bfb056cdccfdd58f0be047226d41a86` | 119 | 46 | 7 | Candidate |
| `409ff5d17d3cee1bf20f2d0326805e5891ad541f` | 1 | 561 | 154 | Alternate |
| `44fb22084b1764373a63b4d892d50cc83dedac0a` | 1 | 409 | 107 | Alternate |
| `4629f77da66d4a98c36fd9f0c2d7e4278fa7edf5` | 1 | 315 | 95 | Alternate |
| `47406675314da24fb5a38e4e05574ce7e51a26f6` | 1 | 413 | 103 | Alternate |
| `58f3860ed443b5ec2f571b59e17d5795d5efc635` | 19 | 160 | 68 | Alternate |
| `59d7dd68c42eea18d488d8e5e6aa9f7a9a327ded` | 13 | 298 | 97 | Donor |
| `63285cc7595a5a612ec99cb9442393f72e69124d` | 1 | 46 | 7 | Alternate |
| `79d54b0a297dc9743c82a2c2d6bf406f8c6ed9af` | 1 | 301 | 100 | Alternate |
| `88286fe0a28b1dbbd99bab282821b63341455a1a` | 1 | 428 | 103 | Alternate |
| `8aff2cf35541b4d2a108c7982c4702ced9cb53ae` | 1 | 528 | 120 | Alternate |
| `8c91807fd46b75693291ca48a9959b732eb20d5b` | 1 | 338 | 101 | Alternate |
| `8cd7313723b63db8c3612880a7c61f22426eb9b4` | 1 | 420 | 103 | Alternate |
| `90b6c6246473428a00d38829495f9877cd1fa05f` | 3 | 360 | 112 | Alternate |
| `b065a301397c83bcb460d43fa36421a7bebc9060` | 3 | 445 | 105 | Alternate |
| `c6c776332f9614449d793b2a54efa31c8f303c7f` | 1 | 393 | 104 | Alternate |
| `d16dd66d87ade5c00d8a50d7e7746bfa2123676b` | 2 | 391 | 103 | Alternate |
| `d97ea5435baedd7ecad959aa49ec3ce5afff3fc0` | 1 | 365 | 109 | Alternate |
| `d9dc62b1c6aebdb4ab38f3d64150699d96f393c4` | 15 | 416 | 119 | Alternate |
| `e18fdf13a5063992004cb12734b13be86a3bd5e7` | 4 | 433 | 104 | Alternate |
| `eef75f0f65beb66d063057011aff560f6ea43a05` | 1 | 400 | 103 | Alternate |

The assertion counts were extracted from source text. They are not executed test counts or coverage metrics.

## 2. Candidate vs donor contract

### Candidate (46 lines, 7 assertions)

- Registers parameter, collects scalar fitness, creates a proposal and adopts a hand-constructed experiment.
- Records evolution history and feeds three canary observations, expecting rollback.
- Restarts Brain and checks the parameter resets to baseline.
- Does not exercise isolated evaluator attestations, durable evaluation-before-adoption, identity-conflicting experiments, legacy replay authority, rollback identity, prediction-feedback learning, malformed safety-gate input or canary persistence.

### Donor (298 lines, 97 assertions)

Adds source-contract scenarios for:
- persisted legacy adoption event without evaluation record is rejected during replay;
- unversioned legacy rollback cannot undo a newer adoption;
- prediction feedback updates the parameter's observations;
- isolated experiment evaluation is recorded before adoption and history shows Evaluated → Adopted;
- manual rollback is journaled and restores baseline;
- direct legacy adoption without a valid evaluated experiment is rejected;
- missing evaluation, equal fitness, subthreshold gain, and evaluation/candidate mismatch are rejected without mutation;
- canary evidence reaches sufficient-evidence/rollback behavior;
- pending canary and experiment-evaluation records survive restart and are resumed;
- duplicate evaluation recording is rejected;
- adoption and rollback state are reconstructed across restart.

These are stronger lifecycle/authority regression contracts. However, this integration test does not prove every safety gate is independent of caller-supplied flags, nor that OS isolation controls were applied.

## 3. Isolation fixture and test limits

Donor's test helper creates a command invoking `/bin/sh -c printf ...` with the candidate fitness, then calls `EvolutionExperimentRunner::run_isolated_command` to produce isolation attestation. It does not run an adversarial evaluator or inspect whether configured controls (namespace, seccomp, chroot, UID/GID or resource limits) actually succeeded. Process-isolation reports cover those limitations separately.

The suite uses fixed working-directory filenames for journal fixtures. Concurrent duplicate invocations of the same test process can collide unless the harness serializes them or each run uses a unique temporary directory. This is a test-isolation risk, not a production-journal finding.

The source asserts many transitions and persistence cases, but it does not cover cross-store crash/failure injection, torn journal writes, filesystem fsync/rename behavior, concurrency races, malformed attestation payloads, stale canary identity or all compensation failures. No test was executed in this audit.

## 4. CMake registration and consumer scope

Candidate and donor both register the same named evolution-Brain integration executable in their test-CMake files. The candidate CMake target exists but its test source is only the short smoke contract. The donor target builds the expanded lifecycle contract. Target registration is not proof of compilation or execution.

This cohort is a test file, not the production authority owner. The controller, experiment coordinator/runner, orchestrator, journal and Brain replay APIs determine actual lifecycle semantics. Existing bounded reports cover those adjacent files; their findings are not automatically closed by this suite.

## 5. Review lenses

1. **Semantic:** donor assertions substantially expand the tested lifecycle: evaluation gate, replay safety, identity, rollback, canary and persistence.
2. **Build/test:** CMake target registration confirmed at both frozen refs; no native build/CTest.
3. **Trust:** helper attestation is generated by the same code path under test; independent hostile evaluator and OS-control enforcement are not verified.
4. **Capability:** tests exercise adaptation/evolution persistence and state transitions, not objective model quality or long-run learning benefit.
5. **Hostile:** high assertion volume is not independent scrutiny; fixed paths, in-process fixtures, and lack of crash/concurrency injection remain.

## 6. Disposition

| Obligation | State |
|---|---|
| 24 exact blobs/owner-tip counts | Complete for this cohort |
| Candidate/donor test behavior comparison | Complete for bounded test files |
| CMake registration | Confirmed |
| Full historical semantic diffs | Partial; not closed |
| Cross-file lifecycle consumer/authority graph | Partial |
| Native build/test | Not run |
| Test concurrency/crash/failure injection | Open |
| Provenance/authority/retention | Open |
| DF-02 | OPEN |

**Disposition:** evolution-Brain integration test cohort documented, not accepted. No source selection/adoption, alternate retirement/deletion, path closure or Stage A authorization.
