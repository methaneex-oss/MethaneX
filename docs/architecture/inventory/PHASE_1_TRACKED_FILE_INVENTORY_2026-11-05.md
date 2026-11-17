# Phase 1 Tracked-File Inventory — Exact Baseline

**Repository:** `methaneex-oss/MethaneX`  
**Tree commit:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Tree object:** `1273ddbcd0087d189e01388ded2d362fb1e058d2`  
**Generated:** 2026-11-05  
**Method:** GitHub Git Trees API, recursive tree for the exact commit; count only entries with `type=blob`.  
**Result:** 200 tracked file blobs. The API response was not truncated.

## Reproduction procedure

The same inventory can be independently reproduced from a local clone without relying on the current branch tip:

```bash
git fetch origin 1273ddbcd0087d189e01388ded2d362fb1e058d2
git ls-tree -r --full-tree 1273ddbcd0087d189e01388ded2d362fb1e058d2
git ls-tree -r --full-tree --name-only 1273ddbcd0087d189e01388ded2d362fb1e058d2 | wc -l
```

For a machine-readable path/type/size/object listing using Git:

```bash
git ls-tree -r -l --full-tree 1273ddbcd0087d189e01388ded2d362fb1e058d2
```

The Git Trees API equivalent used for this record is:

```text
GET /repos/methaneex-oss/MethaneX/git/trees/1273ddbcd0087d189e01388ded2d362fb1e058d2?recursive=1
```

Filter the returned `tree` array to `type == "blob"`. The API returned `truncated=false`; all 200 blob entries are included below. File size and blob SHA are taken directly from each tree entry.

## Classification method

Classification is deterministic by repository path prefix and file extension:
- `core/cpp/include/**/*.hpp`: Core C++ public header.
- `core/cpp/src/**/*.cpp`: Core C++ implementation.
- `core/cpp/tests/**/*.cpp`: Core C++ test source.
- `engineering/cpp/include/**/*.hpp`: Engineering-agent C++ header.
- `engineering/cpp/src/**/*.cpp`: Engineering-agent C++ implementation.
- `engineering/cpp/tests/**/*.cpp`: Engineering-agent C++ test source.
- `runtime/rust/Cargo.toml` and `runtime/rust/src/**/*.rs`: Rust crate manifest/source.
- `interfaces/typescript/**/*.ts`: TypeScript interface/source.
- `.github/workflows/*`: GitHub Actions workflow.
- `*.md`: Markdown documentation/note.
- Remaining tracked blobs: Other configuration/text.

This is a file inventory classification, not a semantic quality assessment. Test registration is separately determined from the CMake test-registration declarations and must not be inferred from a `tests/` path.

## Reconciled category counts

| Category | Count |
|---|---:|
| Core C++ implementation | 58 |
| Core C++ public header | 58 |
| Core C++ test source | 48 |
| Engineering-agent C++ header | 5 |
| Engineering-agent C++ implementation | 5 |
| Engineering-agent C++ test source | 1 |
| GitHub Actions workflow | 10 |
| Markdown documentation/note | 5 |
| Other configuration/text | 3 |
| Rust crate manifest/source | 4 |
| TypeScript interface/source | 3 |
| **Total** | **200** |

## Complete tracked-file list

| Path | Category | Bytes | Git blob SHA |
|---|---|---:|---|
| `.github/workflows/brain-ci.yml` | GitHub Actions workflow | 1334 | `0d5d0c9b9528a418e3c1358420ee2ea708c4dd8c` |
| `.github/workflows/brain-tests.yml` | GitHub Actions workflow | 1296 | `3ccd812db82fdbc073573fac09b32f883a392f54` |
| `.github/workflows/brain-tsan.yml` | GitHub Actions workflow | 885 | `fdb61786cfe62c99feb8a5a7e0d50d7f4e55ed75` |
| `.github/workflows/build.yml` | GitHub Actions workflow | 316 | `6dce9c84f507d67789e00fbc138ceb03233b24e6` |
| `.github/workflows/dlt-002-four-hour.yml` | GitHub Actions workflow | 6141 | `52d08751d29c1b7c7b60e07834ac1bfdc4eba626` |
| `.github/workflows/engineering.yml` | GitHub Actions workflow | 1303 | `46738b2a3b1c6ab66a7f2eeb3d0a9e892be829e7` |
| `.github/workflows/jarvis-learning-mechanisms.yml` | GitHub Actions workflow | 9348 | `0eac13b1e6a43ea7fa06aaf9e0134f5b6ae27710` |
| `.github/workflows/jbp-brain-int-001.yml` | GitHub Actions workflow | 4614 | `31523dfa6bb5160397ebefd1f25325484461e271` |
| `.github/workflows/jbp-learning-002.yml` | GitHub Actions workflow | 4095 | `4e88b4150eed6e5df3e81dd28a35216a299039e9` |
| `.github/workflows/jbp-mem-001.yml` | GitHub Actions workflow | 6965 | `9e1efd73a9a91a70c1d9ceda0d6b458f9bdd7f7f` |
| `core/cpp/CMakeLists.txt` | Other configuration/text | 2140 | `c51816888e1bddb7bc00c59e72529524e27a0717` |
| `core/cpp/include/jarvis/core/action_authorization.hpp` | Core C++ public header | 704 | `047f3f8d74c8558255750fbe14d29f7ae9153360` |
| `core/cpp/include/jarvis/core/action_execution.hpp` | Core C++ public header | 990 | `38ff7033e7621db8f05cc1edc4bf59cb899ccdd3` |
| `core/cpp/include/jarvis/core/action_model.hpp` | Core C++ public header | 713 | `6a3b1720d5b58630faf320ba1e3c082cb417b7a9` |
| `core/cpp/include/jarvis/core/adaptation.hpp` | Core C++ public header | 576 | `9a2bb897a120f7585286481a6138dc9cb767ac30` |
| `core/cpp/include/jarvis/core/association_model.hpp` | Core C++ public header | 1133 | `faa835175cfd6c2fdc1d4561269edb8ab406c689` |
| `core/cpp/include/jarvis/core/attention_state.hpp` | Core C++ public header | 823 | `8f16c4f454db0e1bbb4cdffc711ebcee5e34c637` |
| `core/cpp/include/jarvis/core/attention.hpp` | Core C++ public header | 1210 | `c7e8ab0c5430d5c942fe314d928400f769c0a77c` |
| `core/cpp/include/jarvis/core/brain.hpp` | Core C++ public header | 15268 | `8268ef84e0b361ead536724ba7761904b30ee58f` |
| `core/cpp/include/jarvis/core/capability_evaluator.hpp` | Core C++ public header | 800 | `a8a5c03ce3feee03e0e4ad68fb65376248e5939c` |
| `core/cpp/include/jarvis/core/capability_execution.hpp` | Core C++ public header | 1580 | `d2835c4e77b4b672422eaf4ef024d23a7d2eafc9` |
| `core/cpp/include/jarvis/core/capability_registry.hpp` | Core C++ public header | 1541 | `3f762bf8a57c75fbfb9f976f9a82cdea8d9cca9a` |
| `core/cpp/include/jarvis/core/causal_model.hpp` | Core C++ public header | 847 | `f740bdf222b3309b13f0c2f541c97448fc05da3e` |
| `core/cpp/include/jarvis/core/cognition.hpp` | Core C++ public header | 1550 | `e9aec6461351db42c77ff8414a175ce4c5eea33e` |
| `core/cpp/include/jarvis/core/cognitive_cycle.hpp` | Core C++ public header | 2211 | `28e7af98327956268a769adf7813125be842c1a2` |
| `core/cpp/include/jarvis/core/cognitive_runtime.hpp` | Core C++ public header | 2419 | `d02b2607cebcb7c31963e2fe336970707a481e00` |
| `core/cpp/include/jarvis/core/cognitive_trigger.hpp` | Core C++ public header | 926 | `be1e33d11ebbea1e4dff685fd04b29fbb5324141` |
| `core/cpp/include/jarvis/core/cognitive_workspace.hpp` | Core C++ public header | 1175 | `b015d44e332ea2511d29e607495714d0b982d44e` |
| `core/cpp/include/jarvis/core/decision.hpp` | Core C++ public header | 1454 | `7dd9d6b7337311868d236dc0ced81f558200ab1a` |
| `core/cpp/include/jarvis/core/event.hpp` | Core C++ public header | 529 | `a31db633e8181378fcec0a20c5958c0065d430ee` |
| `core/cpp/include/jarvis/core/evolution_adoption_journal.hpp` | Core C++ public header | 1303 | `f902abfc65d705e15b6b9c8690f8e023f55afacc` |
| `core/cpp/include/jarvis/core/evolution_adoption.hpp` | Core C++ public header | 411 | `46e50e77190dd939db85dfe673da462061acdfe4` |
| `core/cpp/include/jarvis/core/evolution_canary.hpp` | Core C++ public header | 842 | `46ca0938caf1b27b1ea804f1b5ea795683ab0ef0` |
| `core/cpp/include/jarvis/core/evolution_candidate_generator.hpp` | Core C++ public header | 480 | `a68ce0cec079854e07fe09a14844ac54354f501f` |
| `core/cpp/include/jarvis/core/evolution_controller.hpp` | Core C++ public header | 1239 | `e06441d23685093a3c533498a09adf3a8baf5914` |
| `core/cpp/include/jarvis/core/evolution_experiment_coordinator.hpp` | Core C++ public header | 1030 | `2fde3fdf0b3e6772f11358385e069f9b94af34d0` |
| `core/cpp/include/jarvis/core/evolution_experiment_runner.hpp` | Core C++ public header | 418 | `38668879bec3e1cd5d8bcdf884edad819b1573d6` |
| `core/cpp/include/jarvis/core/evolution_experiment.hpp` | Core C++ public header | 647 | `53bcd379fb788a3b0c369309c328f70d56f051ba` |
| `core/cpp/include/jarvis/core/evolution_history.hpp` | Core C++ public header | 1155 | `02efd6b4956393470902880c8a6ab73b3875c825` |
| `core/cpp/include/jarvis/core/evolution_learning.hpp` | Core C++ public header | 551 | `e11ad3276110b9876c881a184f753cac67baed05` |
| `core/cpp/include/jarvis/core/evolution_monitor.hpp` | Core C++ public header | 794 | `d8bd6d10534e6c65e922d36dd5b4ad8b47219b31` |
| `core/cpp/include/jarvis/core/evolution_opportunity.hpp` | Core C++ public header | 1183 | `c03e36726228909c579d517afb8e11910027ba3f` |
| `core/cpp/include/jarvis/core/evolution_orchestrator.hpp` | Core C++ public header | 1570 | `75105e51509156f1fad361ec47e0ae365a1a0291` |
| `core/cpp/include/jarvis/core/evolution_rollback.hpp` | Core C++ public header | 518 | `22e1f10dd5b986f588a8106b8f433e2e6945072b` |
| `core/cpp/include/jarvis/core/evolution_safety.hpp` | Core C++ public header | 472 | `60c69311a1f05d43eef2b8931be261fce3db60cf` |
| `core/cpp/include/jarvis/core/evolution_sandbox.hpp` | Core C++ public header | 920 | `887e07970132f3f049f6e7bef0569b1c3e086932` |
| `core/cpp/include/jarvis/core/evolution_scheduler.hpp` | Core C++ public header | 877 | `240a9254ccf6263d36c55cc92f8921250f398234` |
| `core/cpp/include/jarvis/core/evolution_strategy.hpp` | Core C++ public header | 578 | `236557072d309ef99f76553cec90852d5441137c` |
| `core/cpp/include/jarvis/core/evolution_trials.hpp` | Core C++ public header | 651 | `12555232deb8612abef0afee27cfc5ff5cb1fab6` |
| `core/cpp/include/jarvis/core/evolution.hpp` | Core C++ public header | 1652 | `736876b339846e0ad4da62854a206712e79a201b` |
| `core/cpp/include/jarvis/core/goals.hpp` | Core C++ public header | 1031 | `803fdd34130c71f54912b23fcba2f9eed23dd4f2` |
| `core/cpp/include/jarvis/core/intent.hpp` | Core C++ public header | 548 | `1749ae0d795da496dd6a9a4dcdbd203ae7ddaf6f` |
| `core/cpp/include/jarvis/core/knowledge.hpp` | Core C++ public header | 665 | `50eb1113a4569c3de05489c421d1cabb1437733d` |
| `core/cpp/include/jarvis/core/learning_loop.hpp` | Core C++ public header | 673 | `287f2fe34cebd60b7a562d68c666572f71431cd6` |
| `core/cpp/include/jarvis/core/memory.hpp` | Core C++ public header | 2765 | `f3662038237246efa51155f940d77564f144d6d9` |
| `core/cpp/include/jarvis/core/perception_pipeline.hpp` | Core C++ public header | 1267 | `1e5fed009a2453211dac1a4187ff47c5cc65da39` |
| `core/cpp/include/jarvis/core/planning.hpp` | Core C++ public header | 1325 | `303731d3ac52362ec86afdb482a5567c3b38a8ff` |
| `core/cpp/include/jarvis/core/process_isolation.hpp` | Core C++ public header | 1440 | `a85f71694c446a430291025ac4fe033e18a59549` |
| `core/cpp/include/jarvis/core/reasoning.hpp` | Core C++ public header | 984 | `5c6f82797d4f5052ad5d71a25624de192a2c87d9` |
| `core/cpp/include/jarvis/core/reflection.hpp` | Core C++ public header | 482 | `435e03f8f03f74cb910338ab4ab1264e4eaf085c` |
| `core/cpp/include/jarvis/core/representation.hpp` | Core C++ public header | 1315 | `4a9a12e8e66ce9c393081a4ffff0b7519f3a92ae` |
| `core/cpp/include/jarvis/core/resilience.hpp` | Core C++ public header | 1011 | `4cb687b6fe75f0a03a5017f1d58ce8ba66a51b66` |
| `core/cpp/include/jarvis/core/self_model.hpp` | Core C++ public header | 898 | `afd8a340f3e172b09c3859eb2602e383316ec4f8` |
| `core/cpp/include/jarvis/core/self_state.hpp` | Core C++ public header | 1343 | `333917cc3dc4118a6776240141a5b16ee741bae8` |
| `core/cpp/include/jarvis/core/self_testing.hpp` | Core C++ public header | 1167 | `3dee193f773b068cf2c67fce7afeba04981f4fd4` |
| `core/cpp/include/jarvis/core/strategy.hpp` | Core C++ public header | 497 | `a5b153e9e4044cda97f261a053786b38fc70e76e` |
| `core/cpp/include/jarvis/core/threat.hpp` | Core C++ public header | 566 | `4e84b378a92e8ea3e6d5fb4a371cba76561daca1` |
| `core/cpp/include/jarvis/core/world_model.hpp` | Core C++ public header | 1259 | `1c14f692374b0ab272f05634b7bdd26e358b4f1f` |
| `core/cpp/include/jarvis/core/world_state.hpp` | Core C++ public header | 989 | `5e91ec301d8254380731e0fdf14d16b6a3d5face` |
| `core/cpp/src/action_authorization.cpp` | Core C++ implementation | 1573 | `669bc86c8111ae9755bcd40715352b4fc71350d0` |
| `core/cpp/src/action_execution.cpp` | Core C++ implementation | 2367 | `c2f8653eb755fa2790a88e49bc8b0b9c3077e439` |
| `core/cpp/src/action_model.cpp` | Core C++ implementation | 1829 | `1da9e70b4d0716ae6ee7ff2110b28424f094d6df` |
| `core/cpp/src/adaptation.cpp` | Core C++ implementation | 1386 | `7e07a491a5b13379a5719882a834ecc2452a54ef` |
| `core/cpp/src/association_model.cpp` | Core C++ implementation | 3602 | `b378d4237527dfbb4c65f43545f7f0fc7c42669b` |
| `core/cpp/src/attention_state.cpp` | Core C++ implementation | 2570 | `b2d743e30548ba3803671693cca22412ae291199` |
| `core/cpp/src/attention.cpp` | Core C++ implementation | 2906 | `58f734dbe9772675d687752026231297f289e770` |
| `core/cpp/src/brain_novelty.cpp` | Core C++ implementation | 970 | `92f93b6e21eed69444011804c047a19f95693722` |
| `core/cpp/src/brain_restored_api.cpp` | Core C++ implementation | 26806 | `618deb6976eed951eae02b7f0da741e6d730bb0c` |
| `core/cpp/src/brain.cpp` | Core C++ implementation | 31860 | `e9f3758fcc9c0e89b7280ce376db9033d547682d` |
| `core/cpp/src/capability_evaluator.cpp` | Core C++ implementation | 2185 | `c26199c03c544a700d3b5154930afba10d3253cd` |
| `core/cpp/src/capability_execution.cpp` | Core C++ implementation | 3821 | `5fef6077caf96c77eef6bda2eedd57540759d4e7` |
| `core/cpp/src/capability_registry.cpp` | Core C++ implementation | 2674 | `e8565f666a0d34906e21409dc72c4b50935196c2` |
| `core/cpp/src/causal_model.cpp` | Core C++ implementation | 5269 | `f873d0a6e7fa0676bb88bf7a1f66436bc88a3c0d` |
| `core/cpp/src/cognitive_cycle.cpp` | Core C++ implementation | 6202 | `3df14c552f2048b0394dc362f7ee7a654a93fb32` |
| `core/cpp/src/cognitive_runtime.cpp` | Core C++ implementation | 6247 | `1a1383cedc42e357dc9efce117328b8d55e30bca` |
| `core/cpp/src/cognitive_trigger.cpp` | Core C++ implementation | 1823 | `3eee892e6c5da55614f1202b7841eaec4cf7e625` |
| `core/cpp/src/cognitive_workspace.cpp` | Core C++ implementation | 469 | `fbd2321d9cd1c98217389beced292654e33a906e` |
| `core/cpp/src/decision.cpp` | Core C++ implementation | 5154 | `6a49e0f1f80c3c6b0955ddf98182fc6611c0e84c` |
| `core/cpp/src/evolution_adoption_journal.cpp` | Core C++ implementation | 2680 | `a9e141ac0b784466e86575eefdb3260b2e15dfc0` |
| `core/cpp/src/evolution_adoption.cpp` | Core C++ implementation | 476 | `b62153de36395b3ef46e25a1af0520e15af85e3f` |
| `core/cpp/src/evolution_canary.cpp` | Core C++ implementation | 1820 | `b40c2eec58db1a3f7d3007781f0a5e6abe8c70a9` |
| `core/cpp/src/evolution_candidate_generator.cpp` | Core C++ implementation | 895 | `c953448fde4f5b61a117cdbf08317a71f11d1692` |
| `core/cpp/src/evolution_controller.cpp` | Core C++ implementation | 3750 | `01484ebf12fc3902bce749030a1f54610b26236a` |
| `core/cpp/src/evolution_experiment_coordinator.cpp` | Core C++ implementation | 3027 | `c689d16b31c039a7be9ab5c9bde0de49e677b32d` |
| `core/cpp/src/evolution_experiment_runner.cpp` | Core C++ implementation | 910 | `83d3c26e589cd16151818774a81ccb62f9d514fc` |
| `core/cpp/src/evolution_experiment.cpp` | Core C++ implementation | 1709 | `6c4c8272b72f7685230870147dd362ad3c6dd363` |
| `core/cpp/src/evolution_history.cpp` | Core C++ implementation | 1486 | `4c023ab4a726efb07f563c2b5425b824e19aeee9` |
| `core/cpp/src/evolution_learning.cpp` | Core C++ implementation | 1569 | `55030a497cdb96cd748f88612617dacb326f6617` |
| `core/cpp/src/evolution_monitor.cpp` | Core C++ implementation | 916 | `568798a562a4c14877adaf2a08d303405ff77f7e` |
| `core/cpp/src/evolution_opportunity.cpp` | Core C++ implementation | 3758 | `db48c582f12565261318333337341bef2ad7653f` |
| `core/cpp/src/evolution_orchestrator.cpp` | Core C++ implementation | 5934 | `efd55281ba7d2edf95c6a9f6537ed2944022617e` |
| `core/cpp/src/evolution_rollback.cpp` | Core C++ implementation | 795 | `b6d941d7388a95bf9fa0831cbf71ea39adafade1` |
| `core/cpp/src/evolution_safety.cpp` | Core C++ implementation | 665 | `6c930ebbe69ad92fe155e3c169e3e996442f22cf` |
| `core/cpp/src/evolution_sandbox.cpp` | Core C++ implementation | 1274 | `837ab2adb087284fb370b623371693660b47624a` |
| `core/cpp/src/evolution_scheduler.cpp` | Core C++ implementation | 761 | `142cfcab2d973e94c827d8d8b014df78fda70efb` |
| `core/cpp/src/evolution_strategy.cpp` | Core C++ implementation | 1917 | `09119ffd3991f57106b1e9dbd783357ac9c5edef` |
| `core/cpp/src/evolution_trials.cpp` | Core C++ implementation | 1872 | `4e6192c3d06560c826f8beaf507a546d4c56952a` |
| `core/cpp/src/evolution.cpp` | Core C++ implementation | 4334 | `3860a5a59495460c44e49b8539adff637d7ae65d` |
| `core/cpp/src/goals.cpp` | Core C++ implementation | 3338 | `778a829de8314e83b095af2f2c2a6b83baa769f4` |
| `core/cpp/src/intent.cpp` | Core C++ implementation | 1654 | `4283a4255284c51257df6bad12734782f2a6cde9` |
| `core/cpp/src/knowledge.cpp` | Core C++ implementation | 1241 | `25ecf822e6132f576266c1f86a964a227c7fb75f` |
| `core/cpp/src/learning_loop.cpp` | Core C++ implementation | 1282 | `bc9a6aaca38d060667bcdf82f2b1a1f72c5936ba` |
| `core/cpp/src/memory.cpp` | Core C++ implementation | 18029 | `ba72a897306d4761246d0deab2fbab37c49d372f` |
| `core/cpp/src/perception_pipeline.cpp` | Core C++ implementation | 1903 | `ab9a745bb68e416d4e32c9d0c26a2d0b2016ab17` |
| `core/cpp/src/planning.cpp` | Core C++ implementation | 2932 | `aab022b7cbc06f380413395757d590b56a1f3a20` |
| `core/cpp/src/process_isolation.cpp` | Core C++ implementation | 9615 | `eac7a12fafe36b6c5f463ad0a41caa3bb835a61c` |
| `core/cpp/src/reasoning.cpp` | Core C++ implementation | 4753 | `feec78b2e8a1f2b0b58733fd509e4e5a750258fc` |
| `core/cpp/src/reflection.cpp` | Core C++ implementation | 1289 | `06f34e20f35aad535a2c606b3669b2127ef7a480` |
| `core/cpp/src/representation.cpp` | Core C++ implementation | 2756 | `0e53bfaa0c1114cb7390d9f7ce577c87d6bc6169` |
| `core/cpp/src/resilience.cpp` | Core C++ implementation | 2145 | `ec02b31ed08dc7ac5d9337f92091bb202988cc03` |
| `core/cpp/src/self_model.cpp` | Core C++ implementation | 2000 | `3c6a375eadd6894a635d2e18023a7079cba97c86` |
| `core/cpp/src/self_state.cpp` | Core C++ implementation | 2040 | `01684a46b29fc827beadbd4c05178521085df476` |
| `core/cpp/src/self_testing.cpp` | Core C++ implementation | 1687 | `30b5af95ba1785120a10097767e28a9f3b67a8ce` |
| `core/cpp/src/strategy.cpp` | Core C++ implementation | 934 | `5406a341cd4b3f42e16166f6122a0cb580aee298` |
| `core/cpp/src/threat.cpp` | Core C++ implementation | 2310 | `b9b7258b9540b30588aa4e7c0002d24a28a3e7b4` |
| `core/cpp/src/world_model.cpp` | Core C++ implementation | 3784 | `5b68e8fe37d99732557237e347ae02234a3de172` |
| `core/cpp/src/world_state.cpp` | Core C++ implementation | 2436 | `84658ee6e1a4485e1fe0f24ebb40eb3e281670f0` |
| `core/cpp/tests/action_authorization_suite.cpp` | Core C++ test source | 1524 | `cf0cd95ec6fd83da756c305c54439a018cad796b` |
| `core/cpp/tests/action_execution_phase7_suite.cpp` | Core C++ test source | 3063 | `b4a0060596c91c67080ac0a2db324f720d760fbe` |
| `core/cpp/tests/action_model_architecture_suite.cpp` | Core C++ test source | 1399 | `24f419a4ff469995bbc5961974c7ee3b869c9911` |
| `core/cpp/tests/association_causality_phase5_suite.cpp` | Core C++ test source | 2042 | `d520025258805b02c1b3fbb2dbebe32e01562fbf` |
| `core/cpp/tests/attention_architecture_suite.cpp` | Core C++ test source | 1983 | `3a5609ed29e117c2241ce3f23543c8042f5815b2` |
| `core/cpp/tests/brain_10_suite.cpp` | Core C++ test source | 3795 | `be220d6bdaf1af2a584f6c628fd03b9aea12811c` |
| `core/cpp/tests/brain_contract.cpp` | Core C++ test source | 2101 | `54340d74eca3d8613db1763f8e01e3bc6fc221ba` |
| `core/cpp/tests/brain_deep_suite.cpp` | Core C++ test source | 7861 | `ca8e7012c92822608c3be0539784d281b0578bfd` |
| `core/cpp/tests/brain_failure_suite.cpp` | Core C++ test source | 1973 | `b0e5cb3dd436b5507be10f554c5b850b3fb73df2` |
| `core/cpp/tests/brain_smoke.cpp` | Core C++ test source | 1065 | `0c61c6f9e1bb35e40d0d8c4d7eb17744998c3e68` |
| `core/cpp/tests/capability_evaluator_suite.cpp` | Core C++ test source | 1293 | `16fa37cc0209d7e7e91de78f92f84491f0850705` |
| `core/cpp/tests/capability_execution_suite.cpp` | Core C++ test source | 3163 | `e7ac00dc0b51e9b3135c6072a65f980c6a796375` |
| `core/cpp/tests/capability_registry_suite.cpp` | Core C++ test source | 1756 | `3333ac6049da4422073263e13a053fcc85980a5b` |
| `core/cpp/tests/CMakeLists.txt` | Other configuration/text | 15273 | `dab0c52ab4dfe15e1e2cbccfa9e6c904abdf54e3` |
| `core/cpp/tests/cognitive_cycle_stress_suite.cpp` | Core C++ test source | 1662 | `b1f73ca14ac7a82eb4054b88c6f75f997eb6d9f3` |
| `core/cpp/tests/cognitive_cycle_suite.cpp` | Core C++ test source | 4387 | `38ff2c7d6e851b4745e9dc7c01f968b7245400a2` |
| `core/cpp/tests/cognitive_runtime_suite.cpp` | Core C++ test source | 2596 | `48cac9cb0e27e2dc8a15323429d1f7158ee427a0` |
| `core/cpp/tests/cognitive_trigger_suite.cpp` | Core C++ test source | 2234 | `a817221e2dda72b9a6e45b4b00039f506ff9dc61` |
| `core/cpp/tests/cognitive_workspace_runtime_suite.cpp` | Core C++ test source | 1209 | `ae938f5df02d8f907a548c446c01e17fbd2f1470` |
| `core/cpp/tests/decision_planning_architecture_suite.cpp` | Core C++ test source | 4821 | `16934f99898c3ffffcf5ac04a7a031e0845da050` |
| `core/cpp/tests/evolution_adoption_journal_suite.cpp` | Core C++ test source | 682 | `24a1be9541cc038518065724aef1968efc4dc595` |
| `core/cpp/tests/evolution_brain_integration_suite.cpp` | Core C++ test source | 1600 | `3164cbc19bfb056cdccfdd58f0be047226d41a86` |
| `core/cpp/tests/evolution_canary_controller_suite.cpp` | Core C++ test source | 1481 | `6acd8aedb7520aebe745b15a2a10c527262f28e0` |
| `core/cpp/tests/evolution_experiment_coordinator_suite.cpp` | Core C++ test source | 1141 | `83d884dd97cbcf2d002249a70e44bb29e6ac0560` |
| `core/cpp/tests/evolution_experiment_runner_suite.cpp` | Core C++ test source | 2797 | `08888276d875ce5e55f421e828f1bb4f061d1ea5` |
| `core/cpp/tests/evolution_experiment_suite.cpp` | Core C++ test source | 1755 | `f5aa9ee8fc68e8a2f9f0dd0466ff5e26a77423d2` |
| `core/cpp/tests/evolution_experiment_test.cpp` | Core C++ test source | 907 | `fdc3cacd71690b96939f201b3ac804d7868fa76c` |
| `core/cpp/tests/evolution_learning_suite.cpp` | Core C++ test source | 768 | `41e2fa3532efa4de3521ca889bb6558711340299` |
| `core/cpp/tests/evolution_monitor_suite.cpp` | Core C++ test source | 500 | `fd54357414ee680c73f97e731989b6f2b7578754` |
| `core/cpp/tests/evolution_opportunity_orchestration_suite.cpp` | Core C++ test source | 3355 | `4ef1dc80a85a8e9247c5816bdb73c6876d3a1b22` |
| `core/cpp/tests/evolution_scheduler_suite.cpp` | Core C++ test source | 543 | `f590c4e068789acd06dbb3c75af606bf01d08902` |
| `core/cpp/tests/evolution_trials_suite.cpp` | Core C++ test source | 989 | `643273ae753b289a7ea578724f6c554682567e8c` |
| `core/cpp/tests/goals_architecture_suite.cpp` | Core C++ test source | 2870 | `14a52aa606b53f8529aa5c54861c11902deb7c97` |
| `core/cpp/tests/judgment_intent_strategy_phase6_suite.cpp` | Core C++ test source | 1956 | `05b6c3f4c331e035dc9276025ae1d03bfe931a71` |
| `core/cpp/tests/knowledge_memory_phase3_suite.cpp` | Core C++ test source | 1308 | `f796977fd116418b3cf0a5f9c8d33ed7a48f811e` |
| `core/cpp/tests/learning_adaptation_phase8_suite.cpp` | Core C++ test source | 2594 | `79cb7b8146686b35273628de213d33edd4328cff` |
| `core/cpp/tests/learning_loop_architecture_suite.cpp` | Core C++ test source | 2138 | `1b01fc772f525619fb635579ccf7831187fee08a` |
| `core/cpp/tests/memory_architecture_suite.cpp` | Core C++ test source | 2636 | `2a9eb061427c622260304d09f45089e1debef294` |
| `core/cpp/tests/perception_pipeline_suite.cpp` | Core C++ test source | 3390 | `2312d9f86763a05d7eef9e341d7b1d60bfe845e9` |
| `core/cpp/tests/phase4_notes.md` | Markdown documentation/note | 554 | `bf77a7805cc292bdbbd80b5d31566877f67ddf4b` |
| `core/cpp/tests/prediction_feedback_phase10_suite.cpp` | Core C++ test source | 2446 | `e72da8e7653aee775cfade9060064231c7a01630` |
| `core/cpp/tests/process_isolation_suite.cpp` | Core C++ test source | 2066 | `78b764368de4d427c3196b26b57255edc422bf50` |
| `core/cpp/tests/process_isolation_syscall_suite.cpp` | Core C++ test source | 564 | `cd347d277c84376c3a90ce4d95b31b4dbafde583` |
| `core/cpp/tests/reasoning_architecture_suite.cpp` | Core C++ test source | 1925 | `a7119afd091e045d6294aa1b15c20de349ed6a1c` |
| `core/cpp/tests/representation_suite.cpp` | Core C++ test source | 953 | `1ee7663934f067de4fdd31832719b06274ae6171` |
| `core/cpp/tests/self_model_health_phase4_suite.cpp` | Core C++ test source | 783 | `46fdbb1325159999e7e3ac7e223e9a2a2703b5f5` |
| `core/cpp/tests/self_state_suite.cpp` | Core C++ test source | 1745 | `2d6a9e51393a5e144d4920a06d5fee5606c5ad71` |
| `core/cpp/tests/self_testing_healing_phase9_suite.cpp` | Core C++ test source | 1676 | `1e0c13c6de2843771d63389ddc338617a04af632` |
| `core/cpp/tests/world_self_model_phase4_suite.cpp` | Core C++ test source | 2526 | `f375f6e36c16fbb038d2ce3ba5c4cd18adf1860c` |
| `core/cpp/tests/world_state_suite.cpp` | Core C++ test source | 968 | `bc6539059a8cc856572f3b01358085f27b1673a9` |
| `docs/ARCHITECTURE.md` | Markdown documentation/note | 2320 | `819544194e080f1210a32efc05867c6220f9e6fd` |
| `docs/JARVIS_BRAIN_MASTER_BLUEPRINT.md` | Markdown documentation/note | 10580 | `9958b8a596e172488b21fce1cdc256ccde419cfe` |
| `docs/JARVIS_PHASE_2_COMPLETION.md` | Markdown documentation/note | 1447 | `7e001e63703bf07efe95c321c1f6c4272ae626f7` |
| `engineering/cpp/CMakeLists.txt` | Other configuration/text | 946 | `7e2621c8678ad784d6e8c9e777b22b7c5310b855` |
| `engineering/cpp/include/jarvis/engineering/agent.hpp` | Engineering-agent C++ header | 1809 | `b71c525a97790f460535713d85a705db086c55ac` |
| `engineering/cpp/include/jarvis/engineering/coordinator.hpp` | Engineering-agent C++ header | 854 | `d395db8ce7ae24e40d56aa923758a2251f9188e4` |
| `engineering/cpp/include/jarvis/engineering/execution.hpp` | Engineering-agent C++ header | 776 | `2bf187c48bee71bda48ecac6f7135cba3cc7495b` |
| `engineering/cpp/include/jarvis/engineering/message_bus.hpp` | Engineering-agent C++ header | 2482 | `2658f6c12d60f3df611f5cc0a01569b51b59bcb7` |
| `engineering/cpp/include/jarvis/engineering/operator_console.hpp` | Engineering-agent C++ header | 1362 | `196d3a6755aa7f6cf29a8f5d46a65764c27c9964` |
| `engineering/cpp/src/agent.cpp` | Engineering-agent C++ implementation | 702 | `d922dab52bd2f8d774f3734686da21391cabbf19` |
| `engineering/cpp/src/coordinator.cpp` | Engineering-agent C++ implementation | 2463 | `44f42429e9730683bd8b529b37ea4e53c4b09c74` |
| `engineering/cpp/src/execution.cpp` | Engineering-agent C++ implementation | 205 | `324f202ebe0bc93dd1dd34d726be2b1dc9625fba` |
| `engineering/cpp/src/message_bus.cpp` | Engineering-agent C++ implementation | 3940 | `9811d41fc237e33c80086e33049f9ae482c58c77` |
| `engineering/cpp/src/operator_console.cpp` | Engineering-agent C++ implementation | 1986 | `bf94b8779f79fb52fc3bc39ebd8ff59b5fa13b41` |
| `engineering/cpp/tests/agent_and_console_suite.cpp` | Engineering-agent C++ test source | 1818 | `b1f7a48df7adad95750e6970fa76f75acb2ac6ea` |
| `interfaces/typescript/src/agent_bridge.ts` | TypeScript interface/source | 1018 | `cd86f7d5f44e2d30c0401bb4bf02e05328d1c038` |
| `interfaces/typescript/src/brain.ts` | TypeScript interface/source | 692 | `291916d45af0c67180542f8d775dba8b8ec1976f` |
| `interfaces/typescript/src/operator_session.ts` | TypeScript interface/source | 1569 | `2a699a78bc5beb31ed07cd913e0a527bb64d6bcf` |
| `README.md` | Markdown documentation/note | 3651 | `4cbc127a04199f9244015028bd016df52dece9ff` |
| `runtime/rust/Cargo.toml` | Rust crate manifest/source | 234 | `c8e5a4d1cd1faef5c79a816fbef04d5022575f0a` |
| `runtime/rust/src/cognition.rs` | Rust crate manifest/source | 1577 | `e46bb5b19528b58bf518f75f5edf704221cf5c9f` |
| `runtime/rust/src/error.rs` | Rust crate manifest/source | 170 | `5019356b7382960766de039e3e16a1f1c4e43150` |
| `runtime/rust/src/lib.rs` | Rust crate manifest/source | 939 | `ba949e43b7e06ce081b078035dfe7e48625d521c` |

## Test registration caveat

The Phase 1 report separately records 45 CMake-registered executable/test targets and three C++ test source files not registered by the audited core CMake test configuration: `brain_smoke.cpp`, `evolution_experiment_test.cpp`, and `representation_suite.cpp`. This inventory does not independently validate that count. The registration claim must be reproduced by inspecting the exact baseline's `core/cpp/tests/CMakeLists.txt` and following its target/test declarations; file existence is not execution evidence.

## Scope and limits

This inventory proves the tracked file paths and Git blob identities at the pinned tree. It does not prove file correctness, build inclusion, runtime reachability, test execution, or the absence of untracked/local files. Any comparison with a later branch must name that branch's exact commit and compute a path/object delta; do not silently substitute a newer tree.
