# Priority-One Trust Boundary Contract

**Status:** Proposed engineering contract; not an implementation or acceptance claim.  
**Baseline inspected:** PR #159, `edacf39d91a086480358f6878ecb8461c3cbd7af`.  
**Scope:** durable memory integrity, host trust integration, knowledge adjudication, and calibration evidence quality.

This document converts the currently known Priority-One limitations into testable requirements. It deliberately does not select a deployment-specific key store or claim that the repository currently has a production trust root.

## 1. Current implementation boundary

At the inspected baseline:

- `Memory` stores an unframed binary event stream in the continuity journal.
- Replay checks nonzero, strictly increasing event sequence numbers, but does not authenticate event contents or prove that the journal has not been shortened.
- An unreadable suffix is copied to a `.corrupt` file and the active journal is truncated to the last readable record. This is best-effort legacy recovery, not tamper detection.
- The `.meta` sidecar is independently persisted and is not cryptographically bound to the journal.
- Persistence calls stream `flush()`; this does not by itself guarantee durable storage against power loss.
- The current process mutex does not coordinate independent processes or separate `Memory` instances that target the same journal.
- Feedback and provenance verification are host-supplied callbacks. Repository test callbacks are not production identity or key-management implementations.
- The Rust runtime currently has no dependencies and is a separate minimal state implementation; it is not a production C++ Brain host or a protected storage provider.

These are verified limitations, not hypothetical future concerns.

## 2. Threat model and guarantees

The journal-integrity design must state which attacker capabilities it covers. At minimum, evaluate:

1. Accidental corruption, partial writes, and process/power failure.
2. Modification, insertion, deletion, or reordering of records by an actor who can write the journal files.
3. Replacement of the journal with an older valid copy.
4. Truncation exactly at a valid record boundary.
5. Independent modification or rollback of metadata/state sidecars.
6. Concurrent writers and stale processes.
7. Loss, rotation, revocation, or unavailability of the host trust key/anchor.

A design may claim detection only for the attacker capabilities it actually covers. A digest or hash chain stored only beside the journal does **not** detect valid-tail truncation or whole-file rollback when the same actor can rewrite both files.

The intended security guarantee is: once a committed Brain state has been acknowledged, replay must either reconstruct that exact authenticated committed state or fail closed with an explicit integrity/recovery status. It must never silently accept an older or modified prefix as the latest committed history.

This is an integrity guarantee, not confidentiality. It does not prove that observations are true, that sources are independent, or that an evaluator made a correct adjudication.

## 3. Required storage architecture

### 3.1 Protected external anchor

The journal requires a trust anchor outside the attacker's journal/sidecar write boundary. The embedding host must provide protected storage for at least:

- Stable journal identity.
- Format and integrity-scheme version.
- Monotonic committed generation or equivalent rollback-resistant version.
- Last committed event sequence.
- Authenticated terminal record digest.
- Integrity binding for every durable state artifact that can affect cognition, including metadata, or a documented rule that such artifacts are untrusted rebuildable caches.

The protected anchor must not be a plain file in the same writable directory as the journal. A deployment may use an appropriate OS-protected keystore, hardware-backed facility, or equivalent host-managed trust service, but the core must not assume a particular platform before the deployment target is chosen.

### 3.2 Cryptographic primitives

- Do not implement a bespoke hash, MAC, signature, or key derivation primitive.
- Use a vetted cryptographic implementation with explicit algorithm/version identifiers and supported platform builds.
- The host owns key provisioning, access control, rotation, revocation, backup/recovery, and historical verification policy.
- A test-only deterministic fake provider may test protocol behavior, but must never be represented as production security.

### 3.3 Record framing and canonicalization

New journal formats must be self-framing and versioned. Each committed record must bind, at minimum:

- Journal identity and format version.
- Record sequence and generation.
- Previous committed record digest.
- Canonical serialized event payload, including all fields that affect replay.
- Integrity algorithm/version and resulting authenticated digest.

Canonicalization must be deterministic across supported builds and restarts. It must define map ordering, scalar encoding, integer width/endianness, floating-point handling, string encoding, and rejection of non-finite or unsupported values. Hashing an implementation-dependent in-memory representation is not acceptable.

### 3.4 Commit and crash consistency

The implementation must define and test the transaction boundary between journal bytes and the protected anchor. A successful append must mean both the record and the corresponding anchor advancement are durable.

Required outcomes:

- Crash before a record is durably written: previous committed state remains authoritative.
- Record durable but anchor not advanced: record is an uncommitted tail and must not be replayed as committed state.
- Anchor advanced but record missing or invalid: fail closed; do not silently roll back the anchor.
- Anchor and journal disagree: explicit integrity failure/recovery state; no automatic trust of the shorter side.
- Concurrent writers: serialized or compare-and-swap protected so two writers cannot commit the same generation or fork a journal.
- Durability: use platform-appropriate file and directory synchronization and document filesystem assumptions.

The implementation must not return append success before the durable commit protocol has completed.

### 3.5 Metadata and derived state

Every durable artifact that can change recall, salience, confidence, consolidation, trust, or replay behavior must be included in the integrity boundary.

Choose and document one of these approaches before implementation:

- Make state changes event-sourced in the authenticated journal and treat snapshots/sidecars as rebuildable caches; or
- Authenticate each snapshot and bind it to the exact journal generation/sequence through the protected anchor.

A sidecar that can be independently rolled back or edited must never silently alter cognitive state.

## 4. Legacy journal migration

Legacy journals have no authenticated historical anchor. Their existing contents cannot be retroactively proven authentic by hashing them today.

Migration must therefore:

1. Preserve the original journal and metadata read-only.
2. Verify structural readability and sequence continuity.
3. Require an explicit owner/host decision about whether the legacy history is trusted as the initial baseline.
4. Record a new journal identity, migration generation, baseline digest, and migration provenance in protected storage.
5. Never silently create a new trusted anchor from whatever files happen to exist at startup.
6. Keep a documented rollback/recovery procedure that does not weaken the integrity guarantee.

If the host cannot establish a trusted baseline, the system must report that the old history is unanchored and require an explicit recovery/acceptance decision.

## 5. Startup and runtime failure policy

The Brain needs a machine-readable persistence/integrity status, not only a constructor that quietly loads whatever prefix it can read.

At minimum distinguish:

- Trusted and current.
- Legacy/unanchored.
- Uncommitted tail recoverable under the protocol.
- Corrupt or unauthenticated record.
- Anchor missing, unavailable, or rolled back.
- Anchor ahead of journal.
- Metadata integrity failure.
- Unsupported format or algorithm.
- Key unavailable/revoked.

For integrity failures, the default must be fail-closed for learning, trust updates, and state mutation. Any restricted inspection or recovery mode must be explicit and must not append to or overwrite the source evidence. Recovery must preserve forensic copies and record the operator decision.

## 6. Evaluator identity and provenance trust

The production host integration must provide more than a caller-supplied evaluator string.

Required properties:

- Authenticated evaluator identity and authorization at the call boundary.
- Attestation binding to claim sequence, claim source, claim key/value, evaluator identity, correctness assertion, and relevant policy/version context.
- Deterministic historical verification across restart, with a defined policy for revoked or rotated keys.
- Protected trust configuration and auditable key lifecycle.
- Replay must apply the same authentication and authorization policy as live submission.
- Copied attestations, altered payloads, wrong-source binding, duplicate adjudications, and conflicting adjudications must be rejected deterministically.
- Distinct evaluator names or provenance IDs must not be treated as proof of independent evidence unless the host can establish distinct authenticated origins and the dependence model permits that inference.

A successful signature or attestation establishes the origin/integrity of an assertion. It does not establish objective truth.

## 7. Ground-truth adjudication

The host must define what evidence is sufficient to label a claim correct or incorrect. This policy must identify:

- The observable ground-truth source or measurement procedure.
- How conflicting or unavailable ground truth is represented.
- Evaluator qualification and conflict-of-interest controls.
- Evidence provenance and dependence.
- Time/version context for facts that can change.
- How corrections and later reversals are recorded without rewriting prior experience.

Unknown, disputed, stale, or unadjudicated evidence must not be silently converted into a negative or positive correctness label. The original observation remains in memory; confidence and evidential weight may change without deleting the experience.

## 8. Calibration policy requirements

The current three-outcome minimum is provisional, not a statistically justified universal threshold.

Before treating calibration as production trust evidence, define:

- The target being estimated (source accuracy under what claim population and time horizon).
- How correlated claims and repeated measurements affect effective sample size.
- Whether positive/negative outcomes are balanced or require stratification.
- Uncertainty intervals and minimum evidence needed before changing weight.
- Freshness semantics and the operational rationale for event-count horizons.
- How calibration behaves when evidence is sparse, biased, contradictory, or distribution-shifted.
- A neutral/fail-closed state when evidence is insufficient.

Do not let a raw count of adjudications imply independent samples. Preserve lifetime audit metrics separately from currently active calibration evidence.

## 9. Required adversarial verification

The independent tester must run exact-head tests and preserve reproducible fixtures for:

### Journal and anchor
- Modify one payload byte in a committed record.
- Insert, delete, and reorder records.
- Truncate at every record boundary, especially the last valid boundary.
- Replace journal with an older valid snapshot.
- Replace or roll back metadata independently.
- Corrupt frame lengths, versions, sequence values, digests, and scalar encodings.
- Crash at each write/flush/anchor-advance boundary.
- Simulate missing, stale, ahead-of-journal, unavailable, and revoked anchors/keys.
- Start two writers against the same journal and attempt a fork/race.
- Verify no failure path silently appends after an untrusted suffix.

### Evaluator/provenance
- Forge evaluator identifiers and attestations.
- Replay valid attestations against altered claim source, key, value, sequence, or outcome.
- Reuse attestations across claims and origins.
- Submit duplicates and conflicting adjudications in both journal orders.
- Rotate/revoke keys and verify historical replay policy.
- Restart with missing or changed trust configuration.

### Cognitive-state integrity
- Verify integrity failures cannot update knowledge calibration, memory consolidation, belief state, or downstream learning.
- Verify untrusted metadata cannot change recall ranking or salience.
- Verify trusted restart reconstructs the same state.
- Verify recovery preserves original evidence and does not silently train from a truncated history.

Tests must assert both expected outcomes and absence of unintended state mutation.

## 10. Acceptance gates

Priority One may be considered for closure only when all applicable gates are evidenced:

1. Protected trust-anchor contract implemented by the real embedding host.
2. Journal and all cognition-affecting durable state are authenticated and rollback-detectable.
3. Crash consistency and concurrency semantics are tested.
4. Legacy migration is explicit and auditable.
5. Evaluator/provenance authentication and key lifecycle are implemented in the host.
6. Ground-truth adjudication and evidence-dependence policy are documented and enforced.
7. Calibration threshold/freshness policy is justified and tested.
8. Exact-head native, sanitizer, and full CTest workflows pass.
9. Independent adversarial tester reports PASS with commands, environment, logs, and counterexamples.
10. Independent architecture/security reviewer reports PASS with file/line evidence.
11. All findings are resolved or explicitly accepted by the owner.
12. Owner authorizes the final acceptance/merge decision.

## 11. Explicit exclusions

- This contract does not implement the protected host trust root.
- It does not select a platform keystore, HSM, TPM, or deployment key owner.
- It does not claim cryptographic integrity from an in-file hash chain alone.
- It does not make an evaluator's assertion equivalent to objective truth.
- It does not prove independence from distinct names or signatures alone.
- It does not move Priority-Two planning/action-selection integration into Priority One.

**Current disposition:** Priority One remains open. This contract is a proposed implementation and verification boundary to prevent a cosmetic integrity patch from being mistaken for a security solution.
