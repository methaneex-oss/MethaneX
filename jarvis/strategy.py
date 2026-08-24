from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable


@dataclass(frozen=True)
class Strategy:
    name: str
    steps: tuple[str, ...]
    expected_value: float
    risk: float
    reversibility: float


class StrategyEngine:
    """Scores strategies explicitly so decisions are inspectable rather than hard-coded commands."""

    def propose(self, goal: str, options: Iterable[tuple[str, Iterable[str]]]) -> tuple[Strategy, ...]:
        strategies: list[Strategy] = []
        for name, steps in options:
            normalized = tuple(step.strip() for step in steps if step.strip())
            if not normalized:
                continue
            risk = min(1.0, 0.1 * len(normalized))
            reversibility = 1.0 / max(1, len(normalized))
            expected = max(0.0, min(1.0, 0.65 + 0.15 * reversibility - 0.25 * risk))
            strategies.append(Strategy(name.strip() or goal, normalized, expected, risk, reversibility))
        return tuple(strategies)

    def choose(self, strategies: Iterable[Strategy]) -> Strategy | None:
        return max(
            strategies,
            key=lambda s: s.expected_value + (0.2 * s.reversibility) - (0.3 * s.risk),
            default=None,
        )
