from __future__ import annotations

from dataclasses import dataclass, field
from typing import Iterable

from .training import ExternalTeacher, TeachingExample, TrainingEngine


@dataclass(frozen=True)
class TrainingQuestion:
    prompt: str
    expected_concepts: tuple[str, ...] = ()


@dataclass(frozen=True)
class TrainingAssessment:
    subject: str
    score: float
    strengths: tuple[str, ...]
    weaknesses: tuple[str, ...]
    questions_answered: int


@dataclass
class Curriculum:
    subject: str
    levels: list[float] = field(default_factory=lambda: [0.25, 0.5, 0.75, 1.0])


class LearningLoop:
    """Runs progressive study and assessment without making a teacher part of JARVIS."""

    def __init__(self, training: TrainingEngine | None = None) -> None:
        self.training = training or TrainingEngine()

    def study(self, curriculum: Curriculum, teacher: ExternalTeacher) -> tuple[TeachingExample, ...]:
        for level in curriculum.levels:
            self.training.train(curriculum.subject, teacher, level=level)
        return self.training.memory.recall(curriculum.subject)

    def assess(self, subject: str, questions: Iterable[TrainingQuestion]) -> TrainingAssessment:
        lessons = self.training.memory.recall(subject)
        corpus = " ".join(item.lesson.lower() for item in lessons)
        answered = 0
        strengths: list[str] = []
        weaknesses: list[str] = []
        for question in questions:
            concepts = tuple(c.strip().lower() for c in question.expected_concepts if c.strip())
            if concepts and all(concept in corpus for concept in concepts):
                answered += 1
                strengths.extend(concepts)
            else:
                weaknesses.extend(concepts or (question.prompt,))
        total = answered + len(list(questions))
        score = answered / total if total else 0.0
        return TrainingAssessment(subject, score, tuple(dict.fromkeys(strengths)), tuple(dict.fromkeys(weaknesses)), total)
