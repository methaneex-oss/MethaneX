# JARVIS Review Records

**Status:** Proposed review-record navigation structure  
**Repository:** `methaneex-oss/MethaneX`  
**Introduced:** 2026-11-08  
**Purpose:** Provide one discoverable home for review reports, review evidence, correction records, and review-process guidance without moving or rewriting historical artifacts.

This directory is the canonical entry point for reviewer-authored records. It is not an approval register and does not itself establish that any review is independent, formally submitted, accepted, or authorized by the Project Director.

## Review record categories

| Category | Location | Scope |
|---|---|---|
| Documentation foundation | [documentation-foundation/](documentation-foundation/) | Reviews of documentation structure, navigation, authority/provenance, reader continuity, and documentation-gate evidence |
| Brain foundation | [brain-foundation/](brain-foundation/) | Existing Brain-foundation review correction/evidence records; historical paths are preserved |
| Architecture and system design | Reserved category | Create only when a substantive review record is needed |
| Implementation and code | Reserved category | Create only when a substantive review record is needed |
| Testing and verification | Reserved category | Create only when a substantive review record is needed |
| Security and assurance | Reserved category | Create only when a substantive review record is needed |
| Release and operations | Reserved category | Create only when a substantive review record is needed |

Do not create empty placeholder directories merely to make the taxonomy look complete. Add a category when its first record is created, then update this index.

## Current records

### Documentation foundation

- [2026-11-08 — Documentation Foundation Review Report](documentation-foundation/2026-11-08_DOCUMENTATION_FOUNDATION_REVIEW_REPORT.md) — technical assessment of PRs #192 and #193 against DF-01–DF-13. Clearance is not recommended. The report discloses that its authoring model identity is the same GPT-6 identity recorded as Builder in the self-review; it is therefore **not a qualifying independent review** and does not satisfy DF-11.

### Brain foundation

- Existing historical review material remains under [brain-foundation/](brain-foundation/). It is not moved or reclassified by this directory introduction.

## Record-keeping rules

1. **One canonical home:** put each new reviewer-authored report in the category matching its primary review subject. Link to it from this index.
2. **Exact target:** identify repository, PR/branch, base SHA, head SHA, reviewed files, and review date. A branch name alone is insufficient.
3. **Independence disclosure:** state whether the reviewer is independent of the Builder/author and disclose shared model identity, authorship, conflicts, or other limitations. Never label a self-review as independent.
4. **Evidence discipline:** separate observed facts, analysis, recommendations, and authority decisions. Cite exact paths, revisions, comments, checks, or other evidence.
5. **Finding lifecycle:** give each finding an identifier, severity, evidence, impact, required disposition, and closure evidence. Do not mark a finding closed merely because a later document says it was fixed.
6. **Formal review distinction:** a report stored here, a PR comment, a Builder self-review, and a formal GitHub review submission are different artifacts. Record each accurately.
7. **No authority substitution:** reviewers assess and recommend. They do not accept architecture, clear gates, approve a baseline, or authorize implementation unless a separate explicit delegation grants that authority.
8. **Historical preservation:** do not move, delete, rename, or rewrite older review artifacts as a tidiness exercise. Add links and provenance notes first; any relocation must preserve history and be explicitly authorized.
9. **Synchronize navigation:** update this index and the relevant project documentation index/inventory when adding a material review record.
10. **Re-review exact changes:** a finding is closed only after the corrected artifact is fetched at its new exact revision and the relevant evidence is rechecked.

## Report template

Use [the independent review report template](../templates/INDEPENDENT_REVIEW_REPORT_TEMPLATE.md) as a starting point. Adapt it to the review type, but retain exact-revision identification, independence disclosure, evidence, findings, limitations, and disposition.

## Important boundary

The presence of a report in this directory does not mean the report has been independently validated or accepted. Review status and authority status must always be read from the report itself and the linked formal review/decision record.
