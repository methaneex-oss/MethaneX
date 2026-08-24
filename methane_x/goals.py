from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from uuid import uuid4


class GoalState(str, Enum):
    PROPOSED = "proposed"
    ACTIVE = "active"
    COMPLETED = "completed"
    FAILED = "failed"
    PAUSED = "paused"


@dataclass
class Goal:
    objective: str
    priority: float = 0.5
    id: str = field(default_factory=lambda: uuid4().hex)
    state: GoalState = GoalState.PROPOSED
    rationale: str = ""


class GoalManager:
    """Maintains explicit, inspectable goals; it does not invent arbitrary actions."""

    def __init__(self) -> None:
        self._goals: dict[str, Goal] = {}

    def propose(self, objective: str, *, priority: float = 0.5, rationale: str = "") -> Goal:
        objective = objective.strip()
        if not objective:
            raise ValueError("objective is required")
        goal = Goal(objective, max(0.0, min(1.0, priority)), rationale=rationale)
        self._goals[goal.id] = goal
        return goal

    def activate(self, goal_id: str) -> Goal:
        goal = self._goals[goal_id]
        goal.state = GoalState.ACTIVE
        return goal

    def choose_next(self) -> Goal | None:
        active = [g for g in self._goals.values() if g.state == GoalState.ACTIVE]
        return max(active, key=lambda g: g.priority, default=None)

    def complete(self, goal_id: str) -> Goal:
        goal = self._goals[goal_id]
        goal.state = GoalState.COMPLETED
        return goal

    def pause(self, goal_id: str) -> Goal:
        goal = self._goals[goal_id]
        goal.state = GoalState.PAUSED
        return goal

    def all(self) -> tuple[Goal, ...]:
        return tuple(self._goals.values())
