from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Evaluation:
    success: bool
    quality: float
    lesson_signal: float
    reason: str


class OutcomeEvaluator:
    """Converts observed outcomes into bounded signals for learning and replanning."""

    def evaluate(self, expected: str, observed: str, success: bool) -> Evaluation:
        quality = 1.0 if success else 0.0
        if expected.strip() and observed.strip() and expected.strip().casefold() == observed.strip().casefold():
            quality = 1.0
        elif success:
            quality = 0.75
        return Evaluation(success, quality, quality, "verified outcome" if success else "outcome failed; reconsider strategy")
