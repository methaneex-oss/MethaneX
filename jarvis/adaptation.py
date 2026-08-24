from __future__ import annotations

from dataclasses import dataclass, field


@dataclass(frozen=True)
class AdaptationProposal:
    target: str
    change: str
    evidence: tuple[str, ...]
    expected_benefit: float
    reversible: bool = True


@dataclass
class AdaptationLedger:
    proposals: list[AdaptationProposal] = field(default_factory=list)

    def propose(self, target: str, change: str, evidence: list[str], expected_benefit: float, reversible: bool = True) -> AdaptationProposal:
        if not target.strip() or not change.strip() or not evidence:
            raise ValueError("target, change and evidence are required")
        proposal = AdaptationProposal(target, change, tuple(evidence), max(0.0, min(1.0, expected_benefit)), reversible)
        self.proposals.append(proposal)
        return proposal

    def actionable(self, minimum_benefit: float = 0.7) -> tuple[AdaptationProposal, ...]:
        return tuple(p for p in self.proposals if p.expected_benefit >= minimum_benefit and p.reversible)
