# DF-02 Memory Retrieval, Consolidation and Metadata Variant Adjudication — 2026-11-28

**Scope:** frozen candidate/donor `memory.cpp`, `memory.hpp`, memory architecture test and CMake registration. Candidate `caf87986dfea7aca75728818651c8687e9f5faf0`; donor `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Source inspection only; no native build/CTest.

## Exact blobs
- Candidate `memory.cpp`: `ba72a897306d4761246d0deab2fbab37c49d372f`; donor `ab42bba1d32d6f48d091787491c72294a4a55bb5`.
- Candidate `memory.hpp`: `f3662038237246efa51155f940d77564f144d6d9`; donor `5401d5bd236cca8d3a93f2815164a7734cf6990f`.
- Candidate memory test: `2a9eb061427c622260304d09f45089e1debef294`; donor `ecabc6af76c52ed1e4175b151e76fadecae7729d`.
- CMake source/test registration: candidate `c51816888e1bddb7bc00c59e72529524e27a0717`/`dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3`; donor `bc264ce7b4ae489404ca03ea6d9676d0330a6a56`/`cbfd1fde52fffa6eeac025da2b7ddcb5ab493261`.

## Material semantic delta
- Candidate ranked recall uses matching/overlap, recency, salience, confidence. Donor adds optional event-kind filtering **before** ranking and optional exact-match requirement. Filtering before top-k prevents unrelated records consuming the result window.
- Donor adds consolidation score to `MemoryRecord` and metadata serialization; consolidates salience/novelty/error/confidence/recurrence and uses the score as a retrieval component. Consolidation updates are finite-validated, clamped, transactionally rolled back in memory if snapshot persistence fails.
- Donor adds latest sequence by event kind, rebuilt during journal load and updated on append; this supports durable lifecycle cursor lookups.
- Donor confidence defaults recognize `evidence_reliability`, `confidence`, then `reliability` (double and integer); candidate uses only double-valued `reliability`. Donor metadata format supports prior V1 and V2 with consolidation; parsed updates are staged before applying. Candidate only accepts its existing metadata magic.
- Donor's memory architecture suite expands 61→188 lines and asserts kind-cursor, consolidation/retrieval ranking, recurrence, metadata persistence, restore behavior and working-tier transitions. CMake already registers the memory suite at both refs; no test execution.

## Risks / open questions
1. The main event journal remains raw unframed binary without checksum/version/record length. Loader truncates at invalid/incomplete tail; corruption may destroy recoverable trailing data rather than quarantine it.
2. Metadata snapshot uses temp + rename, but no fsync/directory sync; crash durability and platform replacement semantics are not established. Legacy metadata failure/migration behavior and corruption quarantine need adversarial testing.
3. Consolidation uses source+kind recurrence and fixed weighted formula; it is a heuristic score, not statistically calibrated memory importance. The tier promotion thresholds are fixed and could over-generalize.
4. `forget_working` only changes tier metadata; it does not erase continuity records. Its name must not imply secure deletion or memory removal.
5. `tier_of` depends on learned per-kind counts, so event-kind categorization is a shared aggregate, not individual record identity. Unknown kinds default Episodic.
6. Snapshot persistence rollback restores in-memory state, but concurrent multi-process writers, torn writes, failure injection, journal/meta divergence and recovery semantics are untested.
7. Candidate/donor CMake compiles the source and registers the same memory architecture target; registration is not execution.

## Disposition
Exact candidate/donor content and tests compared. Retrieval and metadata feature deltas identified; persistence/trust/authority and complete historical variant/consumer closure remain OPEN. No implementation selected/adopted/retired/deleted. DF-02 and Foundation gates remain open.
