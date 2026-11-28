# DF-02 Memory Journal, Metadata Migration and Consolidation Variant Adjudication — 2026-11-27

**Scope:** nine exact `core/cpp/src/memory.cpp` blobs, candidate/donor `memory.hpp` and `memory_architecture_suite.cpp`. Cross-reference the separately audited historical framed-journal alternative.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor materially improves corrupt-tail preservation, metadata migration/atomic snapshot behavior, learned-tier rebuilding, consolidation and retrieval filtering. The frozen donor is still an unframed raw event journal (not the historical checksummed-frame implementation). Source/test inspection only.

## 1. Exact inventory

Nine source blobs:
- Candidate `ba72a897306d4761246d0deab2fbab37c49d372f` (133 tips; 428 lines).
- Donor `ab42bba1d32d6f48d091787491c72294a4a55bb5` (48 tips; 225 lines).
- Alternates: `0dd4b193c0e151fa856f17c913a5e320fc485b4d` (9 tips), `331429999fd3c3807c5d58366601e0fd7f51d740` (2), `537ea5bea3244ed51b1c44445c6a43047e4ee037` (10), `88314ed3a43c765f8a69255ace97afb7df1a6c5e` (1, framed journal), `bb2aee0eae27a667d64d7c32c2e2a8b613d35f16` (7), `e9f1eaa74961112c3f60974a1bf200bd2be752dc` (1), `fffb6c0ad6e43cb0b93b873969449e569b3d3f5e` (1).

Eight exact memory-architecture test blobs:
- Candidate `2a9eb061427c622260304d09f45089e1debef294` (133 tips).
- Donor `ecabc6af76c52ed1e4175b151e76fadecae7729d` (48 tips).
- Alternates `4416fda8a0c614f89ab0cdce4433fb5210ea9c5b`, `5d824f08437916e48749bf539cc94e10c9f44347`, `80695272ce5eb454ff720251b3a5a0b1d2d78c9d`, `852ac3730728e033b31269ba7678c73830577cc5`, `861ee2b5bb0ef400611e262bb0935183c8ea4ef0`, `9c8dcd89731c96eb69d7807d860d636796659342`.

Candidate `memory.hpp` SHA `d0f4cbbfb25b2b37903cb9b95dd7d155aefb2d3`; donor `5401d5bd236cca8d3a93f2815164a7734cf6990f`.

## 2. Candidate/donor behavior changes

- **Corrupt-tail recovery:** candidate stops at unreadable data and truncates active file to valid prefix; donor copies the unreadable suffix into `.corrupt` first and only truncates after successful quarantine. It preserves the suffix, but the legacy raw format has no resynchronization marker/checksum, so it cannot safely recover records after an unreadable record.
- **Metadata schema:** candidate metadata V1 stores sequence/tier/salience/confidence. Donor V2 adds consolidation score and reads V1 compatibly with consolidation default 0.
- **Metadata load atomicity:** candidate applies each valid record as it reads; later malformed input can leave partial in-memory metadata updates. Donor stages all records in a temporary map, rejects duplicate sequence IDs or malformed records, then applies only after the entire snapshot validates.
- **Metadata persistence:** donor writes snapshot to a temporary file and renames; candidate has rollback snapshot behavior but lacks the same explicit migration/staged load. Neither source fsyncs file and directory, so rename is not proven crash-durable.
- **Learned tiers/cursors:** donor rebuilds tier counts after load and updates learned tier counts and latest sequence by kind on append; candidate's append does not maintain those structures consistently. Donor adds `latest_sequence_by_kind`.
- **Consolidation:** donor tracks consolidation score; combines salience, novelty, error, confidence and source/kind recurrence; promotes memory tier when thresholds are crossed; persists consolidation. The recurrence signal is global to same source+kind, not context-specific, so unrelated same-kind events can contribute.
- **Retrieval:** donor filters kind and exact-match constraints before top-k ranking, adds consolidation as a ranking factor and makes evidence confidence distinct from operational reliability. Candidate does not provide those filters/score component.

## 3. Journal format qualification

Frozen candidate and donor main `memory.cpp` both serialize raw event records without per-record framing/checksum. Donor improves quarantine on parse/sequence failure but cannot detect every parseable bit corruption. The historical blob `88314ed3a43c765f8a69255ace97afb7df1a6c5e` is a separate framed/checksummed-journal alternative (owner branch `fix/memory-journal-framing-20261028`); it is **not** the frozen candidate/donor implementation or registered donor source. Its owner/authority and integration status remain open. Do not describe the frozen donor memory journal as checksummed.

## 4. Donor test evidence and gaps

Donor suite source asserts:
- append/sequence, latest-by-kind and ranked recall;
- promote, tier, salience and consolidation scoring;
- consolidation can outrank newer otherwise-equivalent memory;
- forget-working, reconstruction of tiers/consolidation and sequence continuity;
- missing metadata snapshot reconstructs tier distribution from journal;
- action-outcome evidence confidence prefers `evidence_reliability` over low execution `reliability`;
- corrupt suffix quarantine preserves exact suffix byte count, repairs active journal, continues append and survives reconstruction.

These tests are source inspected, not executed. They do not establish:
- fsync/power-loss durability, torn writes, concurrent processes or metadata/journal cross-file transactionality;
- corruption of parseable event values, metadata checksum, valid tail after corrupt event, quarantine destination collisions, permission/failure injection;
- cross-platform rename replacement semantics or atomicity under filesystem faults.

## 5. Five review lenses

1. **Semantics:** persistence recovery, metadata migration, consolidation and retrieval changes confirmed.
2. **Build/test:** candidate/donor test source inspected; no native CTest execution.
3. **Integrity:** quarantine preserves unreadable suffix; raw journal still lacks frame checksum/resynchronization and fsync durability.
4. **Cognition:** consolidation/retrieval affects learned memory tier/ranking; source/kind recurrence is a coarse signal, not contextual recurrence.
5. **Hostile review:** framed alternative explicitly separated from frozen donor; no claims of checksum or crash-proof persistence.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Nine source blobs / eight tests inventoried | Complete for slice |
| Candidate/donor metadata/retrieval/consolidation delta | Compared |
| Corrupt-tail quarantine | Source and test inspected |
| Raw journal checksum/frame durability | Gap confirmed |
| Metadata migration/load validation | Source inspected |
| Crash/fault/concurrency/cross-platform tests | Open |
| Framed historical alternative ownership/adoption | Open |
| Full consumers/authority/retention | Open |
| Native tests | Not executed |
| DF-02 | OPEN |

`core/cpp/src/memory.cpp` remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
