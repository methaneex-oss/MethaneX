# DF-02 Capability Registry, Evaluator and Execution Boundary Adjudication — 2026-11-27

**Scope:** capability registry/evaluator/execution APIs, Brain adapter and donor test suites.  
**Candidate:** PR #192 frozen SHA `caf87986dfea7aca75728818651c8687e9f5faf0`. **Donor:** PR #97 `c1da222e6c94aeb3f2ad000392c21fe4fc81ab25`.  
**Disposition:** capability metadata registry, risk/cost/reliability evaluator and permission-gated provider callback are present and registered. The execution boundary is in-process and does not enforce registry/evaluator decisions or provider-output schema. Source/test inspection only.

## 1. Exact refs

- Registry source `e8565f666a0d34906e21409dc72c4b50935196c2`.
- Evaluator source `c26199c03c544a700d3b5154930afba10d3253cd`.
- Execution source `5fef6077caf96c77eef6bda2eedd57540759d4e7`.
- Execution header `d2835c4e77b4b672422eaf4ef024d23a7d2eafc9`.
- Brain adapter `brain_restored_api.cpp` blob `7155d4d9c8eef527836fb79bf901aa32ddbae38`.
- Donor tests: registry `3333ac6049da4422073263e13a053fcc85980a5b`; evaluator `16fa37cc0209d7e7e91de78f92f84491f0850705`; execution `e7ac00dc0b51e9b3135c6072a65f980c6a796375`.

## 2. Capability contract

- Registry accepts unique nonempty IDs/names, bounded reliability and nonnegative cost; supports discovery by availability.
- Evaluator ranks only observable operational properties: availability, risk, estimated cost, reliability and reversibility; deterministic tie by capability ID. It does not infer semantic intent from names/descriptions.
- Execution boundary checks ID, availability, numeric risk against caller-supplied maximum and exact permission strings, selects provider by ID, invokes synchronous callback and catches exceptions.
- Brain adapter records execution event/output/provider/status/reliability in memory journal if append succeeds.

This is a metadata/evaluation/callback mechanism, not a process isolation, tool sandbox, external permission authority or capability proof.

## 3. Source-derived execution gaps

- **Evaluator not enforced:** execution accepts a caller-supplied descriptor and does not require it be registered or carry an evaluator-eligible result. Callers can bypass registry/evaluator and invoke a provider by ID with their own descriptor/risk.
- **Descriptor validation:** registry `valid` checks nonempty ID/name, reliability comparisons and nonnegative cost but no explicit finite cost guard (positive infinity passes), enum validity, duplicate/empty permission/schema entries or output schema constraints.
- **Execution result identity/status:** boundary fills empty result capability/provider IDs, but does not reject a nonempty mismatched capability ID/provider, invalid status enum, empty provider identity, or unvalidated output. A provider can report success with a mismatched result.
- **Availability/reliability:** degraded capability is not rejected by boundary (only unavailable); reliability is not enforced there.
- **No schema/size check:** request input and provider output are opaque strings; input_schema/output_schema are descriptive fields only. Output can be arbitrarily large.
- **In-process synchronous execution:** callback runs inside process with no timeout, cancellation, resource budget, isolation or independent verification. A hung provider can block caller.
- **Persistence status:** Brain returns provider execution result even if capability-execution event append fails; caller has no separate audit-persistence status.

These are source-level gaps; no reproduction/test execution claimed.

## 4. Test evidence and limits

Donor tests assert:
- duplicate/missing registration behavior, lookup and availability discovery;
- evaluator ranks reliable/reversible low-risk capability above risky/degraded and rejects strict constraints;
- successful provider callback/result and Brain journal event;
- missing permission is rejected before provider call.

No tests inject mismatched provider result identity/status, invalid enums, infinite cost, degraded execution policy, schema mismatch/oversized output, timeout/hang, callback reentrancy, execution without registration/evaluation, or journal append failure. The tests use assert; core CMake keeps assertions enabled for Release.

## 5. Five review lenses

1. **Semantics:** metadata/evaluator/permission callback path mapped.
2. **Build/test:** donor suite source and CMake registration inspected; no native execution.
3. **Security/trust:** provider is in-process and result identity/schema are not independently validated; evaluator can be bypassed.
4. **Capability:** execution callback exists but no concrete external adapter or safe sandbox is established.
5. **Hostile review:** “boundary” is not described as sandbox; success/persistence distinction explicit.

## 6. Open obligations / disposition

| Item | State |
|---|---|
| Registry/evaluator/execution source | Inspected |
| Three test contracts | Inspected |
| Registry/evaluator enforcement at execution | Gap |
| Provider/result identity/schema validation | Gap |
| Timeout/cancellation/isolation | Open |
| Audit persistence status | Gap |
| Native tests | Not performed |
| Full consumer/authority/retention | Open |
| DF-02 | OPEN |

Capability system remains **OPEN / NO AUTHORITY DECISION**. No source selected/adopted/retired/deleted; no DF-02 closure, Foundation clearance or Stage A authorization.
