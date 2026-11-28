# DF-02 Brain.hpp Exact Variant and API Authority Adjudication — 2026-11-28

**Scope:** exact 21-blob historical cohort for `core/cpp/include/jarvis/core/brain.hpp`; public API and authority surface comparison.  
**Candidate:** frozen PR #192 SHA `caf87986dfea7aca75728818651c8687e9f5faf0`.  
**Donor:** PR #97 HEAD `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Evidence:** discovery artifact #14956148301; ZIP SHA-256 reverified `9902957475c76f4840d1d280c7d4f50537941e9445810afb805132374a328f38`.  
**Disposition:** exact header versions inventoried and key API/authority differences source-verified; full API compatibility/authority closure remains OPEN.

## 1. Exact 21-blob inventory

| Blob SHA | Tip count | Candidate/donor | Lines (extracted) |
|---|---:|---|---:|
| `12b90d4b9270b0b7e0055587bdceda2712db12ad` | 3 | Alternate | 309 |
| `196fed5a91bc5e57ae7d3af3b0576210cd17a8be` | 2 | Alternate | 83 |
| `1c8f2f4cb402447a9dcf043b0bb976de9ad2886f` | 4 | Alternate | 133 |
| `3e72b0595eec37c68d3395b838312d029478454a` | 15 | Alternate | 308 |
| `44f350fd88c439aed0f3542c5dccfed6d0f65eee` | 7 | Alternate | 299 |
| `5f01602af673291ecddd7e80b69d766369c443e3` | 1 | Alternate | 70 |
| `671186f4c39879a182f9e511394fc564d86f2988` | 51 | Donor | 83 |
| `7679c207be9bb5e6a70b36d770d5dfb846137fb5` | 13 | Alternate | 114 |
| `7888a0fc1f28058640c223d65e804fd26bc171a8` | 1 | Alternate | 174 |
| `78c0484cca036970fab03a2747e238d8b272f477` | 1 | Alternate | 112 |
| `8268ef84e0b361ead536724ba7761904b30ee58f` | 100 | Candidate | 325 |
| `92e8864735c8e1eb3df8614e0eeeea8804151c66` | 1 | Alternate | 138 |
| `937c7cded1b1f8c7482307de13e0bc72cbe6f7ca` | 1 | Alternate | 242 |
| `94368254672f17045030a9effa86b0a71c2c4704` | 1 | Alternate | 112 |
| `a195bdd00fe5fe376095c55bb2acf0671abea85c` | 1 | Alternate | 83 |
| `a73a3d87b1b97f1cab797ea357225d3e35db2456` | 1 | Alternate | 86 |
| `c7df90f0444f0a92eec72ac5ac44e419edd5eda1` | 2 | Alternate | 158 |
| `ca718aa4603bbdd0abc7de26ed296bcf8c6562fe` | 3 | Alternate | 113 |
| `cd8d780b95165ded9c4ea90372cd37d1bcef1bea` | 1 | Alternate | 320 |
| `d9556376afee39f5591102dd04ae777e5301538b` | 2 | Alternate | 112 |
| `dacf427d71e9f47382f6d3b734055e6ea1e7adcc` | 1 | Alternate | 86 |

Total: 21 blobs, 212 tip-presence rows. Tip counts are content-presence metadata, not independent authors, reviews or authority.

## 2. Exact candidate/donor API and authority differences

Frozen candidate header SHA `8268ef84e0b361ead536724ba7761904b30ee58f`; donor header SHA `671186f4c39879a182f9e511394fc564d86f2988`.

Donor declarations include additional API families for contextual prediction/feedback, goal-outcome evidence, contextual association/concept inference, affective/developmental planning, attention policy, self-test/healing, evolution evaluation/canary and sequence-addressed prediction resolution. These are public-contract changes; implementation and consumer integration are separate evidence.

### Memory authority correction (important)

- Candidate header exposes only `const Memory& memory() const noexcept`.
- Donor header exposes **both** `Memory& memory() noexcept` and the const accessor.
- Donor therefore **adds mutable direct Memory access**. A caller can potentially append/alter journal/store records outside Brain's normal event validation, learning, sequence accounting, replay and authority pathways. Exact use sites and consequences require a reverse consumer audit; this is a material API/security concern, not a compatibility improvement.
- A prior report wording that implied donor removed mutable access was incorrect and has been corrected in the restored Brain API adjudication and header-lineage report.

Other material surface changes:
- Candidate prediction state is keyed by string in an unordered map; donor's prediction representation and sequence-addressed resolution API differ, with helper lookups by sequence.
- Donor snapshot includes affective state.
- Donor exposes richer prediction feedback status and sequence identity; candidate has simpler key-based resolution.
- Donor adds goal outcome evidence assimilation, contextual prediction, contextual associations/concepts, generalized concepts, developmental strategy APIs, affective learning/appraisal/calibration, and evolution evaluation recording.
- Evolution parameter registration changes from void to bool in the donor declaration.
- Donor's API includes mutable memory accessor, which must be explicitly considered in ownership and journal integrity design.

Exact declarations were source-inspected at frozen refs. This is not a full ABI/source compatibility analysis.

## 3. Historical variant feature groups

Content markers extracted across exact blobs indicate several non-monotonic API families:
- richer affective/developmental/contextual/prediction-feedback/goal-outcome surface appears in a subset of versions;
- earlier versions include contextual/developmental/goal-outcome APIs without the full affective/feedback set;
- other versions contain only a simpler Brain API and omit prediction-feedback/developmental/goal-outcome markers;
- public class layout, storage type, inline methods, overloads and direct Memory access vary across versions.

These marker groupings are discovery aids. Exact method signatures, overloads, implementation ownership and semantic successors for all 21 blobs remain open. The previous similarity-based family counts are not re-derived from these marker sets and are not treated as authoritative.

## 4. Build/consumer implications

- Candidate CMake compiles candidate brain.cpp, not the donor split API files. Candidate header declarations and implementation must be reconciled against exact registered source definitions.
- Donor CMake registers brain.cpp plus the restored API, action-execution, prediction-context and affective-planning translation units, and affective/developmental models.
- Mutable Memory exposure creates potential direct write bypasses. Consumer matches must be exact-context classified; lexical symbol hits do not prove use.
- Header surface changes may alter ABI, source compatibility, class layout, inline behavior and concurrency/locking guarantees. Native compilation and caller/test link closure are required.

## 5. Review lenses

1. **Semantic/API:** material additions and state-representation changes established; all 21 variants not fully semantically diffed.
2. **Build:** candidate/donor translation-unit ownership differs; no build/link/CTest execution.
3. **Trust/authority:** donor mutable Memory accessor expands direct mutation authority and must be reconciled with journal validation, sequence/cycle accounting, replay and persistence.
4. **Capability:** declared API does not prove functional capability or autonomous operation.
5. **Hostile:** header declarations alone do not prove all method implementations are registered, all callers are valid, or persistence/concurrency contracts are sound.

## 6. Disposition

| Obligation | State |
|---|---|
| 21 exact blobs/tip counts | Complete for this slice |
| Candidate/donor public declaration comparison | Bounded comparison complete |
| Mutable Memory accessor authority delta | Confirmed; high-priority open impact audit |
| Storage representation and sequence API | Identified |
| Exact implementation/link/consumer graph | Partial/open |
| Historical semantic variants | Partial |
| ABI/source compatibility and tests | Open; not run |
| Provenance/authority/retention | Open |
| DF-02 | OPEN |

**Disposition:** Brain.hpp cohort is source-adjudicated at bounded candidate/donor surface, not semantically/authority closed. No header selected/adopted, alternate retired/deleted, baseline, Stage A or gate authorization.
