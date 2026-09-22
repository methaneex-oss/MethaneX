# Evolution Sandbox Policy

This policy is mandatory for agents operating on JARVIS evolution.

## Allowed

- create isolated branches/workspaces;
- inspect existing JARVIS source and tests;
- modify evolution implementation inside the isolated workspace;
- add tests and benchmarks;
- run builds and test suites;
- compare baseline and candidate behavior;
- produce evidence and review artifacts;
- communicate findings to other engineering agents and the operator.

## Forbidden

- modifying `main` directly;
- modifying unrelated repositories;
- modifying any relationship/personal project;
- writing credentials or secrets into the repository;
- deploying an unverified candidate to production;
- bypassing authorization or execution boundaries;
- claiming a statistical result that was not actually measured;
- treating an LLM response as proof that a candidate is better;
- automatic irreversible adoption;
- unrestricted source mutation.

## Adoption boundary

An evolution candidate remains a candidate until the normal JARVIS evolution controller accepts measured evidence and passes its safety gate. Agent code changes must therefore remain isolated until the engineering review and CI process approves them.

## Failure behavior

If the requested isolation, authorization, validation, or verification boundary cannot be enforced, the agent must fail closed and report the reason through the engineering message bus.
