from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


class MemorySink(Protocol):
    def remember(self, content: str, *, confidence: float = 1.0, source: str = "user", tier: int = 3) -> object: ...


@dataclass(frozen=True)
class Experience:
    goal: str
    action: str
    outcome: str
    success: bool


@dataclass(frozen=True)
class Lesson:
    content: str
    confidence: float
    source: str = "experience"


class LessonValidator(Protocol):
    def validate(self, lesson: Lesson) -> bool: ...


class LearningEngine:
    """Turns observed outcomes into bounded, reviewable memory candidates."""

    def __init__(self, memory: MemorySink, validator: LessonValidator | None = None) -> None:
        self.memory = memory
        self.validator = validator

    def propose(self, experience: Experience) -> Lesson:
        if experience.success:
            confidence = 0.8
            content = f"Successful approach for '{experience.goal}': {experience.action}."
        else:
            confidence = 0.4
            content = f"Failed approach for '{experience.goal}': {experience.action}; outcome: {experience.outcome}."
        return Lesson(content=content, confidence=confidence)

    def learn(self, experience: Experience) -> Lesson | None:
        lesson = self.propose(experience)
        if self.validator is not None and not self.validator.validate(lesson):
            return None
        self.memory.remember(lesson.content, confidence=lesson.confidence, source=lesson.source)
        return lesson
