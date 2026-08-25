from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone
from typing import Callable, Iterable


@dataclass(frozen=True)
class TeachingExample:
    subject: str
    lesson: str
    source: str
    difficulty: float = 0.5
    timestamp: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


@dataclass(frozen=True)
class TrainingResult:
    subject: str
    learned: tuple[str, ...]
    rejected: tuple[str, ...]
    score: float
    source: str


class ExternalTeacher:
    """Adapter contract for an external teacher. The teacher is not part of JARVIS."""

    def teach(self, subject: str, level: float) -> Iterable[TeachingExample]:
        raise NotImplementedError


class TrainingMemory:
    """Stores validated learning independently from external teacher implementations."""

    def __init__(self) -> None:
        self._lessons: dict[str, list[TeachingExample]] = {}

    def store(self, examples: Iterable[TeachingExample]) -> None:
        for example in examples:
            if example.subject.strip() and example.lesson.strip():
                self._lessons.setdefault(example.subject.strip().lower(), []).append(example)

    def recall(self, subject: str) -> tuple[TeachingExample, ...]:
        return tuple(self._lessons.get(subject.strip().lower(), ()))


class TrainingEngine:
    """Learns general knowledge from teachers through study, validation and consolidation."""

    def __init__(self, memory: TrainingMemory | None = None) -> None:
        self.memory = memory or TrainingMemory()

    def train(
        self,
        subject: str,
        teacher: ExternalTeacher,
        *,
        level: float = 0.5,
        validator: Callable[[TeachingExample], bool] | None = None,
    ) -> TrainingResult:
        examples = tuple(teacher.teach(subject, max(0.0, min(1.0, level))))
        accepted: list[TeachingExample] = []
        rejected: list[str] = []
        for example in examples:
            valid = validator(example) if validator else bool(example.lesson.strip())
            if valid:
                accepted.append(example)
            else:
                rejected.append(example.lesson)
        self.memory.store(accepted)
        score = len(accepted) / len(examples) if examples else 0.0
        source = accepted[0].source if accepted else teacher.__class__.__name__
        return TrainingResult(subject, tuple(e.lesson for e in accepted), tuple(rejected), score, source)
