from __future__ import annotations

from dataclasses import dataclass
from typing import Callable

from .intelligence import IntelligenceRequest, IntelligenceRouter
from .planning import Plan, Planner, TaskState


@dataclass(frozen=True)
class CycleResult:
    task_id: str
    output: str
    provider: str


class CognitiveLoop:
    """Coordinates planning, intelligence, execution and observation without hardcoding a model."""

    def __init__(
        self,
        planner: Planner,
        intelligence: IntelligenceRouter,
        executor: Callable[[str], str] | None = None,
    ) -> None:
        self.planner = planner
        self.intelligence = intelligence
        self.executor = executor or (lambda task: task)

    def start(self, goal: str) -> Plan:
        return self.planner.create(goal)

    def step(self, plan: Plan) -> CycleResult | None:
        task = self.planner.next(plan)
        if task is None:
            return None
        task.state = TaskState.RUNNING
        try:
            response = self.intelligence.generate(IntelligenceRequest(prompt=task.description))
            output = self.executor(response.text)
            task.result = output
            task.state = TaskState.SUCCEEDED
            return CycleResult(task.id, output, response.provider)
        except Exception as exc:
            task.error = str(exc)
            task.state = TaskState.FAILED
            raise

    def run(self, goal: str) -> list[CycleResult]:
        plan = self.start(goal)
        results: list[CycleResult] = []
        while (result := self.step(plan)) is not None:
            results.append(result)
        return results
