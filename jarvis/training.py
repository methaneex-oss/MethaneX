from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path
from typing import Callable, Iterable

from .persistence import StateJournal


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

    def __init__(self, state_path: str | Path | None = None) -> None:
        self._lessons: dict[str, list[TeachingExample]] = {}
        self._journal = StateJournal(state_path) if state_path else None
        self._restore()

    def store(self, examples: Iterable[TeachingExample]) -> None:
        changed = False
        for example in examples:
            subject = example.subject.strip()
            lesson = example.lesson.strip()
            if subject and lesson:
                self._lessons.setdefault(subject.lower(), []).append(
                    TeachingExample(
                        subject=subject,
                        lesson=lesson,
                        source=example.source,
                        difficulty=max(0.0, min(1.0, example.difficulty)),
                        timestamp=example.timestamp,
                    )
                )
                changed = True
        if changed:
            self._persist()

    def recall(self, subject: str) -> tuple[TeachingExample, ...]:
        return tuple(self._lessons.get(subject.strip().lower(), ()))

    def _persist(self) -> None:
        if not self._journal:
            return
        self._journal.save({
            "lessons": {
                subject: [
                    {
                        "subject": example.subject,
                        "lesson": example.lesson,
                        "source": example.source,
                        "difficulty": example.difficulty,
                        "timestamp": example.timestamp,
                    }
                    for example in examples
                ]
                for subject, examples in self._lessons.items()
            }
        })

    def _restore(self) -> None:
        if not self._journal:
            return
        state = self._journal.load()
        lessons = state.get("lessons")
        if not isinstance(lessons, dict):
            return
        for subject, entries in lessons.items():
            if not isinstance(subject, str) or not isinstance(entries, list):
                continue
            restored: list[TeachingExample] = []
            for entry in entries:
                if not isinstance(entry, dict):
                    continue
                lesson = entry.get("lesson")
                source = entry.get("source")
                if not isinstance(lesson, str) or not lesson.strip() or not isinstance(source, str) or not source.strip():
                    continue
                difficulty = entry.get("difficulty", 0.5)
                if not isinstance(difficulty, (int, float)):
                    difficulty = 0.5
                timestamp = entry.get("timestamp")
                if not isinstance(timestamp, str) or not timestamp:
                    timestamp = datetime.now(timezone.utc).isoformat()
                restored.append(TeachingExample(
                    subject=subject.strip(),
                    lesson=lesson.strip(),
                    source=source.strip(),
                    difficulty=max(0.0, min(1.0, float(difficulty))),
                    timestamp=timestamp,
                ))
            if restored:
                self._lessons[subject.strip().lower()] = restored


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
