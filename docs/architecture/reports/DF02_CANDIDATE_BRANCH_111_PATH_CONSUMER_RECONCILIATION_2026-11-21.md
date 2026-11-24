# DF-02 — Candidate-branch 111-path consumer reconciliation

**Date:** 2026-11-21  
**Repository:** `methaneex-oss/MethaneX`  
**Candidate branch scan tip:** `84dd10094cac675b97b1ab2d45b36618d61efe38`  
**Candidate PR #192 source base:** `61311fe5b44c81c4409c8ba8dc581a83bdd5dd2c`  
**Donor PR #97 HEAD:** `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`  
**Refined all-ref artifact:** workflow `44799437811`, artifact `14659828741`, SHA-256 `3a7d90b475564097a2ccf1de3f4492659b4417a7d46d3e193d9c95ff7b78ab22`

## 1. Exact artifact integrity and scope

The downloaded ZIP was independently hashed; its SHA-256 matches the PR #199 artifact digest exactly. The archive contains the complete 8-file scan output, including `candidate_symbol_consumer_matches.csv` (40,032 rows), `consumer_blob_sources.jsonl` (1,208 full text blobs), `donor_path_presence.csv` (159 paths) and the exact-ref matrix.

The artifact reports 254 remote branch refs, 213 unique branch tips, 1,397 unique text blobs, 724 extracted donor identifiers, 40,032 lexical candidate rows, 1,208 matched consumer-blob contents and 1,134 exact consumer-blob/path/category versions. The scan itself explicitly says lexical matches are discovery evidence, not semantic proof.

## 2. Candidate-branch reconciliation

The exact candidate branch tip `84dd100...` was isolated from the full artifact by exact tip SHA, not inferred from branch names. The resulting path matrix contains **111 of the 118** donor paths that had all-ref lexical candidates. The seven other-ref-only paths are already separately adjudicated in `DF02_COMPILED_CONSUMER_AND_ALTERNATE_BRANCH_ADJUDICATION_2026-11-20.md`.

For those 111 candidate-branch paths:

- **76** have a divergent same-path candidate artifact.
- **35** have no same-path candidate artifact; their lexical hits must not be mistaken for an implementation successor.
- **107** have source-category lexical hits; **85** have a hit in a directly compiled translation unit (the existing include-graph report verifies compile reachability separately).
- Candidate-branch consumer evidence comprises **128 source-category paths** (123 C++ headers/translation units plus five TypeScript/Rust source files), **50 test paths**, **11 workflow paths**, **2 build paths**, **14 documentation paths**, and **1 other path**: 206 unique path/category occurrences in total.
- The exact candidate-branch consumer corpus contains 206 distinct blob/path occurrences. The per-donor-path matrix preserves each donor blob, candidate same-path blob/status, matched identifier set, source/test/build/workflow/documentation consumer paths, candidate-branch exact consumer-blob/path versions and line-class counts.

A 111-row machine-readable evidence matrix was generated from the verified artifact and retained as a local CSV export for this Builder session. It includes one row per donor path, exact donor/candidate blob identities, matched identifier sets, candidate-branch source/test/build/workflow/documentation consumer paths, exact consumer-blob/path versions and line-class counters. The matrix is an analysis aid; it is not represented as a committed repository artifact.

## 3. What the evidence establishes—and what it does not

This pass resolves the candidate-branch location and content identity of the 111-path lexical set. It makes it possible to separate:
1. same-path divergent artifacts with actual candidate source/test consumers;
2. donor-only paths that receive generic-token or incidental lexical matches elsewhere;
3. donor-only APIs referenced by uncompiled/orphaned source such as `brain_restored_api.cpp`;
4. donor-only test files whose symbols occur in unrelated candidate test helpers;
5. workflow/build references that describe a donor path but do not compile or execute it.

The exact line-class counters are diagnostic aids, not semantic verdicts. Common identifiers such as `restore`, `restored`, `observe`, `complete`, `number`, `output`, `constexpr`, `neutral` and `make_input` can create lexical hits without preserving the donor contract. A path is not considered integrated merely because it appears in a source file, a test, a workflow, or a comment.

The already completed focused reports remain the semantic evidence for material mechanisms: action consequence feedback; cognitive runtime/memory/association/adaptation; evolution isolation and adoption; prediction identity/feedback; affective decision and orphaned Brain API; attention/self-model/recovery; goal outcomes; cognitive-cycle integration; representation provenance/canary preview; affective/developmental subsystem gap; and causal feedback/typed persistence. The 41 no-symbol path supplement and seven other-ref-only dispositions remain separate and are not re-counted as new work here.

## 4. DF-02 disposition

**Builder evidence reconciliation advanced; DF-02 is not falsely marked closed.** The 111 candidate-branch paths now have an exact path-level consumer matrix, joined to the 159-path donor/candidate inventory and full-content scan. The previous blanket statement that all 118 paths were still an undifferentiated lexical set is superseded.

Remaining closure work is narrower and explicit: finish semantic successor/duplicate-owner decisions for the divergent paths not already covered by focused reports; confirm which generic-token matches are incidental; reconcile cross-branch source ownership for remaining true consumers; and preserve the distinction between technical disposition and Director-only source-baseline, retirement, non-adoption or adoption authority. No source baseline is selected and no donor/runtime code is adopted by this report.


## 5. Superseding scan and exact ownership update — 2026-11-21

The earlier artifact/run cited above is superseded for all-ref branch ownership by workflow 44931803411, artifact 14717933378, candidate PR #192 source snapshot 19c1c168fdbdab58ed9732cd250d2ae4624936eb, donor PR #97 HEAD c1da222e6c94aeb3f2ad000392c21fe4fc81ab25, scanner commit b8a594ea514ff44cadb5342986c68b1eac6e22ed. Artifact SHA-256: 189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f.

The new scan covers 254 branch refs / 213 unique tips, 1,415 text blobs, 40,041 lexical candidate rows, 1,226 consumer-blob/path/category occurrences, 798 path/blob ownership rows and 1,938 exact path-reference rows. The candidate path set remains 111: 76 divergent same-path artifacts and 35 absent same-path artifacts. The no-symbol set is 48 (28 absent, 19 divergent, one identical).

The new artifact supplies the branch-name/tip-to-exact-blob join missing from the previous artifact. The 76-path dispersion report now has a direct ownership map; it is no longer accurate to say that branch ownership cannot be established from the scan.

The C++ source tree in the PR #192 documentation branch remained unchanged through the documentation-only successor commit 5c402cf8110bf38f2db114e1fadf463e245e9dae; the source/build/test consumer findings remain applicable. The new scan is the controlling evidence for exact branch/blob ownership. Lexical and compile reachability still do not substitute for per-path semantic successor decisions.

**DF02 remains OPEN:** the 76 divergent paths still require semantic disposition and duplicate-owner reconciliation. No source baseline or adoption decision is made.

## 6. Corrected exact all-ref artifact digest and candidate-path coverage — 2026-11-24

The exact all-ref artifact downloaded from run `44931803411`, artifact `14717933378`, has SHA-256 `189f65acfc5561c71da652ac32b71d308aa47ea8737793381af3a17cae45676a`. This locally computed digest matches the artifact bytes; the earlier §5 digest `189f65b26b78e3811fb5b2c9fef6cfc97a8f6a24c8f62f80b0f6c1e7c9d70e7f` is incorrect and is superseded.

The 76 divergent candidate-branch paths are now exact-path cross-referenced to the existing focused reports (70 core and six engineering). The 35 absent-path and 48 no-symbol cohorts are also covered by their per-path adjudication reports. Thus all 159 donor paths have candidate-path-level semantic coverage; this does not claim exhaustive semantic review of every alternate-branch blob variant or every lexical consumer candidate.

The full artifact contains 413 distinct consumer paths, 1,226 exact consumer-blob contents, 798 path/blob ownership rows, 1,938 exact path-reference rows, 40,041 symbol-match rows, 254 refs and 213 unique tips. These are discovery/ownership evidence, not 1,226 proven dependencies. The candidate C++/engineering source tree is unchanged between the artifact's candidate snapshot `19c1c168fdbdab58ed9732cd250d2ae4624936eb` and PR #192 HEAD `437c26939db515f8fbabdab238a8e6042848eec1`.

The prior statement in §5 that all 76 divergent paths still require candidate-path semantic disposition is superseded. **The remaining DF-02 work is material alternate-branch consumer/implementation cluster adjudication and historical authority/retention disposition.** DF-02 remains OPEN; no source baseline or donor adoption is selected.
