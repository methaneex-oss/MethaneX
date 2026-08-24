from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from uuid import uuid4


class TaskState(str, Enum):
    PENDING = "pending"
    RUNNING = "running"
    SUCCEEDED = "succeeded"
    FAILED = "failed"
    CANCELLED = "cancelled"


@dataclass
class Task:
    description: str
    id: str = field(default_factory=lambda: uuid4().hex)
    dependencies: list[str] = field(default_factory=list)
    state: TaskState = TaskState.PENDING
    result: str | None = None
    error: str | None = None


@dataclass
class Plan:
    goal: str
    tasks: list[Task]

    def ready_tasks(self) -> list[Task]:
        completed = {t.id for t in self.tasks if t.state == TaskState.SUCCEEDED}
        return [t for t in self.tasks if t.state == TaskState.PENDING and all(d in completed for d in t.dependencies)]


class Planner:
    """Deterministic baseline planner; intelligence providers can replace/extend it."""

    def create(self, goal: str) -> Plan:
        goal = goal.strip()
        if not goal:
            raise ValueError("A goal is required")
        return Plan(goal=goal, tasks=[Task(description=goal)])

    def next(self, plan: Plan) -> Task | None:
        ready = plan.ready_tasks()
        return ready[0] if ready else None
