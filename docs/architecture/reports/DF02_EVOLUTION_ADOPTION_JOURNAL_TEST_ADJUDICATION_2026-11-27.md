# DF-02 Evolution Adoption Journal Test Adjudication — 2026-11-27

**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Disposition:** materially different journal compensation/replay and controller-contract test obligations identified. Source inspection only; tests not run.

## Exact files

- Candidate `core/cpp/tests/evolution_adoption_journal_suite.cpp`: blob `24a1be9541cc038518065724aef1968efc4dc595`
- Donor `core/cpp/tests/evolution_adoption_journal_suite.cpp`: blob `fc8ae17bb837831fef7bf69873ec0e5243e2bc22`

Both were fetched from their exact frozen refs and inspected in full.

## Candidate coverage

Candidate journal test covers:
- stage → Pending;
- commit → Adopted, including repeated commit;
- rollback → RolledBack, including repeated rollback.

It does not cover restoration/compensation transitions, identity-conflict stage reuse, controller evaluation evidence/validation, unsafe adoption rejection before journal mutation, or replay compensation.

## Donor additions and contract implications

Donor test adds:

1. **Compensation after history append failure:** adopted journal state is restored to Pending; a subsequent commit is possible.
2. **Restoration after rollback-history failure:** RolledBack is restored to Adopted before retrying rollback.
3. **Terminal identity conflict:** after rollback, re-staging the same experiment is rejected; a restoration API can explicitly restore Adopted state for the covered scenario.
4. **Controller validation:** duplicate evaluation is idempotently accepted; Neutral and Pending experiments do not enter adoption; unsafe confidence and unrecorded/mutated experiment evidence are rejected before a pending journal entry or model mutation.
5. **Compensating adoption:** model and journal are returned to a coherent Pending state after compensation; the experiment can then be adopted and rolled back with corresponding history.
6. **Replay compensation:** replayed adoption and rollback preserve baseline restoration in the fixture.
7. **Model rollback:** previous model value restoration is asserted.
8. **History idempotency:** appending the same history record twice yields one record.

## Adjudication

The candidate suite establishes basic journal state transitions and repeated commit/rollback behavior only. The donor suite asserts recoverability around history failures, experiment identity, validation, model/journal coordination, replay and idempotency. These are materially distinct safety and durability contracts.

**Open risks:** these tests use in-memory journal/controller fixtures; they do not establish crash-consistent disk persistence, torn-write behavior, process termination at every transition, fsync durability, or concurrent writer correctness. Such cases require separate fault-injection and persistence integration tests.

## Verification / authority boundary

The exact test contents were fetched and inspected. No native compilation or test execution was performed by this audit. No implementation was selected or modified. This closes only the source-inspection adjudication for this exact test pair—not the full historical variants, owner/provenance/retention ledger, reverse-consumer matrix, independent review, DF-02, gates, or Stage A.
