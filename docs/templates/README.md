# Documentation Templates

These templates provide consistent structure for future documentation contributions. They are starting points, not mandatory governance rules unless an accepted project decision adopts them.

## Available templates

- [Planning / technical document template](PLANNING_DOCUMENT_TEMPLATE.md) — architecture, specifications, research and plans.
- [Independent review report template](INDEPENDENT_REVIEW_REPORT_TEMPLATE.md) — evidence-based review of an exact revision.
- [Test evidence report template](TEST_EVIDENCE_REPORT_TEMPLATE.md) — reproducible verification results tied to an exact commit and environment.

## Usage rules

1. Copy the relevant template into the correct canonical directory; do not edit the template in place for a project-specific report.
2. Remove instructions and fields that do not apply, but do not omit material authority, scope, revision, evidence or limitation information.
3. Use exact commit SHAs and file paths when claims depend on repository state.
4. Distinguish facts, analysis, hypotheses, recommendations and decisions.
5. Record checks not performed and evidence that could not be retrieved.
6. Add the resulting artifact to the Planning Documentation Index and detailed inventory when it is a substantive planning artifact.
7. Preserve one canonical artifact path; do not create parallel copies in separate PR stacks without an explicit reason and dependency record.

A completed template does not itself constitute approval, independent review, test execution, gate clearance or implementation authorization.
