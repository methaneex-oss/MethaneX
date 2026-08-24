from __future__ import annotations

from dataclasses import dataclass
from typing import Callable, Iterable


@dataclass(frozen=True)
class SimulatedOutcome:
    strategy: str
    success: bool
    score: float
    consequence: str


class Simulator:
    """Provides a deterministic substrate for comparing candidate strategies before execution."""

    def evaluate(self, strategies: Iterable[tuple[str, Iterable[str]]], evaluator: Callable[[tuple[str, ...]], float]) -> tuple[SimulatedOutcome, ...]:
        outcomes: list[SimulatedOutcome] = []
        for name, steps in strategies:
            normalized = tuple(step.strip() for step in steps if step.strip())
            if not normalized:
                continue
            score = max(0.0, min(1.0, float(evaluator(normalized))))
            outcomes.append(SimulatedOutcome(name, score >= 0.5, score, "estimated from available model"))
        return tuple(sorted(outcomes, key=lambda outcome: outcome.score, reverse=True))
