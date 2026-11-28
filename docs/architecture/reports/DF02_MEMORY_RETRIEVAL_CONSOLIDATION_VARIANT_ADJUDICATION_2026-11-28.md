# DF-02 Memory Retrieval, Consolidation and Metadata Variant Adjudication — 2026-11-28

**Scope:** frozen candidate/donor `memory.cpp`, `memory.hpp`, memory architecture test and CMake registration. Candidate `caf87986dfea7aca75728818651c8687e9f5faf0`; donor `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`. Source inspection plus historical CI evidence for quarantine and preserve-corrupt-tail variants; the framed-journal variant remains untested; no current-candidate CTest.

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

 
## Historical execution of exact donor memory variant — 2026-11-28

The e737cae7f907696ef787a4e85b0dee3a739d71b1 alternate branch contains the exact frozen donor blobs:
- memory.cpp ab42bba1d32d6f48d091787491c72294a4a55bb5;
- memory.hpp 5401d5bd236cca8d3a93f2815164a7734cf6990f;
- memory_architecture_suite.cpp ecabc6af76c52ed1e4175b151e76fadecae7729d;
- parent CMake 33197f92141a241ff0546af1bf81fbf177a1f3ab (64-source alternate with OpenSSL dependency);
- tests CMake cbfd1fde52fffa6eeac025da2b7ddcb5ab493261.

CTest #9 jarvis_memory_architecture_suite passed in Brain CI #1826 native/sanitizer, JARVIS Brain Tests #975 brain/sanitizer and Brain ThreadSanitizer #957; all five jobs report 71/71. The exact donor memory implementation and donor memory test were executed in that alternate branch. This is not a test result for the frozen candidate memory.cpp ba72a897 or candidate memory.hpp f3662038, and not a current PR #203 CTest result.

The test validates retrieval-kind filtering, exact match, consolidation score and ranking, recurrence, metadata persistence/restore and working-tier transitions. It does not cover the main event journal's raw framing/checksum/record-length integrity, fsync/directory durability, corruption quarantine, concurrent multi-process writers, torn writes, crash injection or journal/metadata divergence. Those risks remain open.

 
## Memory journal integrity variants and exact CI provenance — 2026-11-28

Three additional memory.cpp lineages were compared. They are distinct designs and must not be collapsed into a single "journal fix".

### 1. Preserve-corrupt-tail variant

- Branch: fix/memory-journal-preserve-corrupt-tail-20261028.
- HEAD: 292f406d0ce5bfae85d96e188822212f571750eb.
- memory.cpp blob: fffb6c0ad6e43cb0b93b873969449e569b3d3f5e.
- memory_architecture_suite.cpp blob: 5d824f08437916e48749bf539cc94e10c9f44347 (139 lines / 58 assert expressions).
- It detects that the legacy journal has no record framing/checksum and cannot safely resynchronize after a corrupt middle record. Before truncating to the verified prefix, it copies the complete original file to a collision-avoiding .recovery-backup path. If copying fails, it leaves the original source untouched.
- The test corrupts the middle record's length field, verifies the active journal retains only the verified prefix, verifies the complete original file is preserved byte-for-byte in the backup, appends a new record, and verifies restart continuity.
- CTest #9 passed in Brain CI #1532 native/sanitizer, JARVIS Brain Tests #682 brain/sanitizer and Brain ThreadSanitizer #663; all five jobs report 70/70. Exact run IDs: 40710174257, 40710174249, 40710174245. Native Build #907 and Core Verification #1202 also succeeded (run IDs 40710174339 and 40710174287).

### 2. Frozen donor quarantine variant

- Branch: fix/memory-journal-quarantine-20261028.
- HEAD: 0c1d0b5f01fb448a07e9ca1c091285bc01830845.
- memory.cpp blob: ab42bba1d32d6f48d091787491c72294a4a55bb5 (the frozen donor source blob).
- memory_architecture_suite.cpp blob: ecabc6af76c52ed1e4175b151e76fadecae7729d (188 lines / 70 assert expressions; the frozen donor test blob).
- It preserves the unreadable suffix to a .corrupt file before truncating the active journal to the verified prefix. If quarantine creation/copy/flush fails, it leaves the original journal untouched. The test corrupts the second record's sequence, verifies the first record remains active, verifies the unreadable suffix is quarantined, appends a new record, and verifies restart.
- CTest #9 passed in Brain CI #1541 native/sanitizer, JARVIS Brain Tests #691 brain/sanitizer and Brain ThreadSanitizer #672; all five jobs report 70/70. Exact run IDs: 40717995663, 40717995648, 40717995783. Native Build #916 and Core Verification #1211 also succeeded (run IDs 40717995627 and 40717995706).
- This proves the exact frozen donor memory.cpp/test blobs were executed in a historical branch. It does not prove frozen donor parent CMake bc264 was built; the branch used its own CMake variant.

### 3. Framed V2 journal variant — untested

- Branch: fix/memory-journal-framing-20261028.
- HEAD: b0560edaa72b6d455001be51695731cf988b43b2.
- memory.cpp blob: 88314ed3a43c765f8a69255ace97afb7df1a6c5e.
- It adds a V2 magic header, per-record uint64 length, FNV-1a 64-bit checksum, maximum frame size, safe parsing boundaries, legacy unframed read/migration via temporary file and rename, and a fail-closed append guard that refuses to append to a non-V2 existing journal.
- It skips complete frames with invalid checksum/decoded event while continuing at the declared next boundary; incomplete trailing frames are truncated to the last complete frame.
- The checksum is FNV-1a 64-bit: useful for accidental corruption detection, not cryptographic integrity/authentication.
- The branch has no workflow runs or combined status. Its 58-assert memory_architecture_suite blob 5d824 is registered but contains no dedicated assertions for frame magic, length bounds, checksum mismatch, interior-frame corruption recovery, truncated-frame recovery, legacy migration or append refusal. Therefore the core framing behavior is not behaviorally verified.

### Technical comparison and remaining risks

| Property | Preserve-corrupt-tail | Frozen donor quarantine | Framed V2 |
|---|---|---|---|
| Record framing/checksum | No | No | Length + FNV64 |
| Corrupt middle record | Preserve full original backup; truncate active to verified prefix | Quarantine unreadable suffix; truncate active to verified prefix | Skip bad complete frame and continue at next boundary |
| Incomplete tail | Prefix recovery; original backup retained | Prefix recovery; suffix quarantined | Truncate incomplete trailing frame |
| Legacy journal | Native format | Native format | Read + attempted atomic V2 migration |
| Append to legacy file | Existing legacy behavior | Existing legacy behavior | Fail closed if V2 migration did not produce V2 file |
| Dedicated corruption/framing tests | Middle-record invalid-length test | Middle-record invalid-sequence test | No dedicated framing/corruption test found |
| Historical CI | 70/70 in five jobs | 70/70 in five jobs | No runs/status |

The framed V2 design is directionally stronger because it supplies explicit resynchronization boundaries and accidental-corruption detection. It is not ready for adoption: FNV64 is not cryptographic, the test suite does not exercise framing, incomplete-tail and migration failure paths, and no CI evidence exists. It also lacks fsync/fdatasync and parent-directory durability guarantees; a successful stream flush/rename is not proof of power-loss durability. The preserve-corrupt-tail and quarantine variants have actual corruption tests and CI, but remain legacy unframed formats.

No implementation was copied or adopted. The candidate remains the frozen candidate. These branches are evidence-only; baseline, retention and adoption remain Director decisions.

 
## Self-review finding: recovery truncation errors are ignored — 2026-11-28

A further failure-path review found a concrete persistence defect shared by all three journal recovery variants:
- Preserve-corrupt-tail fffb6c0ad6e43cb0b93b873969449e569b3d3f5e line 84 calls filesystem::resize_file(journal_path_, valid_end, error) and does not check error.
- Frozen donor quarantine ab42bba1d32d6f48d091787491c72294a4a55bb5 line 61 makes the same unchecked call after copying the suffix to .corrupt.
- Framed V2 88314ed3a43c765f8a69255ace97afb7df1a6c5e line 140 makes the same unchecked call after detecting an incomplete trailing frame.

The Memory header blob 5401d5bd236cca8d3a93f2815164a7734cf6990f exposes void load() and has no recovery-required/read-only status. In the legacy variants, Memory::persist at fffb line 158 / ab42 line 135 opens the journal for append without checking that load-time truncation succeeded. In the framed variant, persist validates the V2 magic but does not validate that the existing file ends at the last verified frame.

Failure consequence (source-level, not dynamically fault-injected): if quarantine/backup succeeds but resize_file fails, the object still finishes construction with only the verified prefix in memory while the on-disk journal retains the corrupt suffix. A later append can succeed at the file end; the next restart stops at the corrupt record and cannot reach the newly appended event. This can produce silent loss of post-recovery events. In the framed variant, an incomplete trailing frame can similarly remain before newly appended frames if truncation fails, making subsequent frames unreachable on replay.

Required corrective behavior for any future implementation:
1. Treat truncate failure as a hard recovery failure.
2. Keep the Memory instance read-only/recovery-required; reject append until the journal is repaired or an explicit recovery action succeeds.
3. Preserve a durable recovery artifact and report the exact path/size/hash.
4. Add fault-injection tests for quarantine/backup failure, resize_file failure, append after failed recovery, and restart replay.
5. For framed V2, add corruption tests for bad checksum, invalid length, invalid payload, incomplete header/frame, interior bad frame followed by valid frame, and legacy migration failure.

Additional forensic issue: the frozen donor quarantine code opens the fixed .corrupt path with ios::app. Repeated recoveries append multiple unreadable suffixes without a generation header or manifest; this is less traceable than the preserve-corrupt-tail branch's collision-avoiding .recovery-backup.N filenames. The current tests remove .corrupt before each run and do not test repeated quarantine generations.

This defect was found during Builder self-review. It is not fixed because the active authorization prohibits runtime/source implementation changes. It remains an explicit technical blocker; the passing CI tests exercise successful recovery, not failure of the recovery operation itself.

 
## Metadata-sidecar loss semantics — 2026-11-28

A final test-contract review corrected the interpretation of the "rebuild learned tiers" comment:
- The 58-assert test blob 5d824f08437916e48749bf539cc94e10c9f44347 lines 90–133 promotes an experience to Semantic, appends a second event of the same kind, deletes the .meta sidecar, reconstructs Memory, then explicitly asserts tier_of("learned-kind") == Episodic at lines 126–133.
- The frozen donor 70-assert test blob ecabc6af76c52ed1e4175b151e76fadecae7729d has the same expectation at lines 129–134.
- Therefore the test does **not** prove learned tier restoration from the journal. It proves that when metadata is missing, the event journal restores event/sequence history but all records fall back to default Episodic tier. Previously learned Semantic/Procedural tier, salience, confidence and consolidation are lost.
- This is an explicit degraded-mode behavior in the tests, not an accidental claim of successful learned-state restoration. The comment "Rebuild the learned distribution from journal records" is semantically misleading: the journal has no learned tier data; only default tiers are reconstructed.
- load_metadata() returns on invalid magic/count, truncated/invalid record, duplicate sequence or non-finite values without exposing a degraded-memory status or quarantining the bad sidecar. The constructor then calls rebuild_learned_tiers() over default metadata records. The test covers a missing sidecar, not a corrupt/truncated sidecar.

Capability implication: event recall survives sidecar loss, but learned memory organization does not. This may be acceptable as a documented fallback only if the system surfaces degraded memory state and the user/agent knows that semantic/episodic organization and salience/ confidence/consolidation have been lost. Current API/test contract does not surface that distinction. A future authorized fix needs either journal-backed learning metadata, validated replay/reconstruction rules, or explicit degraded-state reporting plus recovery tooling; corrupt-sidecar fault injection is required.

No runtime change was made. This is a technical capability gap for future Builder implementation authorization and remains open.
