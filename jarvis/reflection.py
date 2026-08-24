from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Reflection:
    outcome: str
    what_worked: tuple[str, ...]
    what_failed: tuple[str, ...]
    uncertainty: tuple[str, ...]
    lesson_candidate: str | None
    confidence: float


class Reflector:
    """Converts observed outcomes into structured self-review without mutating memory itself."""

    def reflect(self, *, outcome: str, expected: str, evidence: list[str], confidence: float) -> Reflection:
        normalized_outcome = outcome.strip()
        normalized_expected = expected.strip()
        worked = (normalized_expected,) if normalized_outcome == normalized_expected and normalized_expected else ()
        failed = (normalized_expected,) if normalized_expected and normalized_outcome != normalized_expected else ()
        lesson = None
        if failed:
            lesson = f"Review strategy because observed outcome differed from expected: {normalized_outcome}"
        adjusted = max(0.0, min(1.0, confidence + (0.1 if worked else -0.1 if failed else 0.0)))
        return Reflection(normalized_outcome, worked, failed, tuple(evidence), lesson, adjusted)
