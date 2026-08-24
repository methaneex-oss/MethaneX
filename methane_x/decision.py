from __future__ import annotations

from dataclasses import dataclass
from typing import Sequence


@dataclass(frozen=True)
class Candidate:
    strategy: str
    expected_value: float
    confidence: float
    risk: float = 0.0

    @property
    def score(self) -> float:
        return self.expected_value * self.confidence - self.risk


class DecisionEngine:
    """Scores candidate strategies from supplied evidence; it does not encode command-specific behavior."""

    def choose(self, candidates: Sequence[Candidate], *, risk_tolerance: float = 1.0) -> Candidate | None:
        eligible = [item for item in candidates if 0.0 <= item.risk <= risk_tolerance]
        if not eligible:
            return None
        return max(eligible, key=lambda item: item.score)

    def rank(self, candidates: Sequence[Candidate], *, risk_tolerance: float = 1.0) -> tuple[Candidate, ...]:
        eligible = [item for item in candidates if item.risk <= risk_tolerance]
        return tuple(sorted(eligible, key=lambda item: item.score, reverse=True))
