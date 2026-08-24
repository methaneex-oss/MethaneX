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

    def choose(self, candidates: Sequence[Candidate]) -> Candidate | None:
        if not candidates:
            return None
        return max(candidates, key=lambda item: item.score)

    def rank(self, candidates: Sequence[Candidate]) -> tuple[Candidate, ...]:
        return tuple(sorted(candidates, key=lambda item: item.score, reverse=True))
