from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable


@dataclass(frozen=True)
class GoalSignal:
    goal: str
    priority: float
    urgency: float = 0.5
    confidence: float = 0.5

    @property
    def score(self) -> float:
        return max(0.0, min(1.0, 0.55 * self.priority + 0.3 * self.urgency + 0.15 * self.confidence))


class GoalArbiter:
    """Arbitrates competing goals using explicit signals rather than fixed command rules."""

    def choose(self, goals: Iterable[GoalSignal]) -> GoalSignal | None:
        return max(goals, key=lambda goal: goal.score, default=None)
