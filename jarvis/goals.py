from __future__ import annotations

from dataclasses import dataclass, field
from uuid import uuid4


@dataclass
class Goal:
    objective: str
    priority: float = 0.5
    urgency: float = 0.5
    confidence: float = 0.5
    id: str = field(default_factory=lambda: uuid4().hex)
    active: bool = True

    @property
    def score(self) -> float:
        return (0.45 * self.priority) + (0.35 * self.urgency) + (0.20 * self.confidence)


class GoalArbiter:
    """Chooses among competing goals using explicit state rather than command-specific rules."""

    def __init__(self) -> None:
        self.goals: dict[str, Goal] = {}

    def add(self, objective: str, *, priority: float = 0.5, urgency: float = 0.5, confidence: float = 0.5) -> Goal:
        if not objective.strip():
            raise ValueError("objective is required")
        goal = Goal(objective.strip(), *[max(0.0, min(1.0, x)) for x in (priority, urgency, confidence)])
        self.goals[goal.id] = goal
        return goal

    def choose(self) -> Goal | None:
        return max((g for g in self.goals.values() if g.active), key=lambda g: g.score, default=None)

    def suspend(self, goal_id: str) -> None:
        self.goals[goal_id].active = False
