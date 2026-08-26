from __future__ import annotations

from dataclasses import dataclass, field
from typing import Callable, Iterable

from .cognitive_cycle import CognitiveCycle, CycleResult


@dataclass
class AutonomyState:
    active: bool = False
    steps: int = 0
    last_goal: str | None = None
    stop_reason: str | None = None
    history: list[str] = field(default_factory=list)


@dataclass(frozen=True)
class AutonomyResult:
    goal: str
    cycles: tuple[CycleResult, ...]
    stop_reason: str


class AutonomousController:
    """Orchestrates bounded cognitive work while keeping decision logic in the brain."""

    def __init__(self, cycle: CognitiveCycle | None = None) -> None:
        self.cycle = cycle or CognitiveCycle()
        self.state = AutonomyState()

    def run(
        self,
        goal: str,
        *,
        facts: Iterable[str] = (),
        options: Iterable[tuple[str, Iterable[str]]] = (),
        execute: Callable[[str], str] | None = None,
        continue_if: Callable[[CycleResult], bool] | None = None,
        max_cycles: int = 1,
    ) -> AutonomyResult:
        if not goal.strip():
            raise ValueError("goal must not be empty")
        if max_cycles < 1:
            raise ValueError("max_cycles must be at least 1")

        self.state = AutonomyState(active=True, last_goal=goal.strip())
        results: list[CycleResult] = []
        stop_reason = "cycle_limit"

        try:
            for _ in range(max_cycles):
                result = self.cycle.run(goal, facts=facts, options=options, execute=execute)
                results.append(result)
                self.state.steps += 1
                self.state.history.append(result.reflection.what_worked)

                if continue_if is None or not continue_if(result):
                    stop_reason = "decision_complete"
                    break
            else:
                stop_reason = "cycle_limit"
        finally:
            self.state.active = False
            self.state.stop_reason = stop_reason

        return AutonomyResult(goal=goal.strip(), cycles=tuple(results), stop_reason=stop_reason)
