from __future__ import annotations

from dataclasses import dataclass, field
from typing import Callable, Iterable

from .adaptation import AdaptationProposal


@dataclass(frozen=True)
class ShadowResult:
    target: str
    change: str
    baseline_score: float
    candidate_score: float
    improvement: float
    accepted: bool
    reason: str


@dataclass
class EvolutionEngine:
    """Evaluates reversible changes in shadow mode before they affect live cognition."""

    history: list[ShadowResult] = field(default_factory=list)

    def evaluate(
        self,
        proposals: Iterable[AdaptationProposal],
        scorer: Callable[[str, str], tuple[float, float]],
        *,
        minimum_improvement: float = 0.0,
    ) -> tuple[ShadowResult, ...]:
        if not 0.0 <= minimum_improvement <= 1.0:
            raise ValueError("minimum_improvement must be between 0 and 1")

        results: list[ShadowResult] = []
        for proposal in proposals:
            if not proposal.reversible:
                results.append(ShadowResult(
                    proposal.target,
                    proposal.change,
                    0.0,
                    0.0,
                    0.0,
                    False,
                    "non-reversible proposal rejected from shadow evolution",
                ))
                continue

            baseline, candidate = scorer(proposal.target, proposal.change)
            baseline = max(0.0, min(1.0, float(baseline)))
            candidate = max(0.0, min(1.0, float(candidate)))
            improvement = candidate - baseline
            accepted = improvement >= minimum_improvement and candidate >= baseline
            reason = "candidate improves or matches baseline" if accepted else "candidate did not improve baseline"
            results.append(ShadowResult(
                proposal.target,
                proposal.change,
                baseline,
                candidate,
                improvement,
                accepted,
                reason,
            ))

        self.history.extend(results)
        return tuple(results)

    def accepted(self) -> tuple[ShadowResult, ...]:
        return tuple(result for result in self.history if result.accepted)
