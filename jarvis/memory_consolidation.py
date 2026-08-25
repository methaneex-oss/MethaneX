from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class ExperienceRecord:
    situation: str
    action: str
    outcome: str
    success: bool
    confidence: float = 0.5


@dataclass(frozen=True)
class Lesson:
    pattern: str
    guidance: str
    confidence: float
    observations: int


class MemoryConsolidator:
    """Turns repeated experience into candidate lessons; never treats one event as truth."""

    def consolidate(self, experiences: list[ExperienceRecord]) -> tuple[Lesson, ...]:
        groups: dict[tuple[str, str], list[ExperienceRecord]] = {}
        for item in experiences:
            groups.setdefault((item.situation.strip(), item.action.strip()), []).append(item)
        lessons: list[Lesson] = []
        for (situation, action), items in groups.items():
            if len(items) < 2:
                continue
            successes = sum(item.success for item in items)
            rate = successes / len(items)
            mean_confidence = sum(max(0.0, min(1.0, item.confidence)) for item in items) / len(items)
            confidence = max(0.0, min(1.0, 0.5 * rate + 0.5 * mean_confidence))
            guidance = "prefer" if rate > 0.5 else "avoid" if rate < 0.5 else "insufficient evidence"
            lessons.append(Lesson(situation, f"{guidance} action '{action}'", confidence, len(items)))
        return tuple(sorted(lessons, key=lambda lesson: lesson.confidence, reverse=True))
