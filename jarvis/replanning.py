from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable


@dataclass(frozen=True)
class ReplanDecision:
    replan: bool
    reason: str
    alternatives: tuple[str, ...]


class Replanner:
    """Decides whether a failed or degraded plan needs a new strategy."""

    def decide(self, *, goal: str, plan_steps: Iterable[str], failed_step: str | None, observed_result: str, confidence: float) -> ReplanDecision:
        steps = tuple(plan_steps)
        if not failed_step and confidence >= 0.65:
            return ReplanDecision(False, "Current plan remains sufficiently supported.", ())
        if failed_step:
            alternatives = tuple(step for step in steps if step != failed_step)
            return ReplanDecision(True, f"Plan evidence changed after failure of '{failed_step}'.", alternatives)
        return ReplanDecision(True, f"Confidence dropped below threshold for goal '{goal}'.", steps)
