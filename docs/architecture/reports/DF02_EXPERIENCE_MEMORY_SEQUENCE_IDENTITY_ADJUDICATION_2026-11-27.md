# DF-02 ExperienceMemory Sequence Identity and Resolution Adjudication — 2026-11-27

**Scope:** donor-only `ExperienceMemory` header and direct test; consumer/integration status.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** donor-added in-memory sequence store separates semantic key from experience sequence. Duplicate sequence handling and resolution evidence validation are missing.

## 1. Exact refs

- `core/cpp/include/jarvis/core/experience_memory.hpp`: `28cce354eb9db7e8ca292746fd14649debb7ab04` (donor-only).
- Direct test `core/cpp/tests/experience_memory_test.cpp`: `fe69fed346c9f843101fc3379d6d474f4a082651`.
- Consumer integration test `core/cpp/tests/cognitive_runtime_learning_integration_suite.cpp`: `656de56b1368e40afb090778a7a5504ab4208056`.

## 2. Contract

`record_prediction` requires nonzero created sequence and nonempty key; stores the experience in a sequence-keyed map and appends sequence to a semantic-key vector. `resolve` accepts a sequence once, stores actual/error and marks the prediction resolved. `latest_unresolved` scans a key's sequence vector backward; `for_key` returns all stored entries for that key.

The direct test covers two different sequences with the same semantic key, independent resolution, latest-unresolved and no unresolved result after both resolve.

## 3. Source-derived integrity gaps

- **Duplicate sequence overwrite:** recording the same sequence again overwrites `experiences_[sequence]` but appends another sequence to `by_key_[new_key]`. If key changes, old key's vector still points to the overwritten experience now carrying the new key. `for_key(old_key)` can return an experience with mismatched key; duplicate entries can appear under new key; latest-unresolved can be misdirected.
- **No exact idempotency:** duplicate sequence with same content also appends duplicate key-vector entry rather than returning a verified idempotent success.
- **Resolved prediction acceptance:** `record_prediction` accepts a Prediction already resolved; it marks experience resolved but leaves `actual` unset, inconsistent representation.
- **Resolution validation:** `resolve` accepts arbitrary/nonfinite error and actual value; no recomputation against prediction or type/metric policy. Sequence identity prevents resolving a different record but does not validate outcome semantics.
- **No durable state:** ExperienceMemory is an in-memory map/vector; durability is supplied only if its consumer also persists authoritative Brain events and reconstructs it. The direct class has no load/save/replay API.

## 4. Test evidence and limits

Direct test covers normal two-sequence same-key behavior only. Runtime-learning integration test exercises Brain prediction/outcome/memory/developmental learning loop, but does not establish that this standalone ExperienceMemory handles duplicate IDs or durable reconstruction.

No tests were executed. Missing tests: duplicate same/different content sequence, cross-key overwrite, vector deduplication, resolved prediction without actual, NaN/infinite error, wrong Scalar type, duplicate resolve, replay/restart, and thread safety.

## 5. Five review lenses

1. **Semantic:** sequence vs semantic-key separation is implemented.
2. **Build/test:** donor-only header/test source inspected; no native run.
3. **Integrity:** overwrite/index mismatch and nonfinite resolution can corrupt query semantics.
4. **Cognition:** this is a store primitive; it does not itself perform learning or generalization.
5. **Hostile review:** in-memory and test scope explicitly limited.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Exact donor header/test | Verified |
| Candidate path absent | Confirmed |
| Normal multi-sequence behavior | Test contract inspected |
| Duplicate sequence identity | Gap |
| Resolution semantic validation | Gap |
| Durable replay/thread safety | Open |
| Native tests | Not performed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

ExperienceMemory remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
