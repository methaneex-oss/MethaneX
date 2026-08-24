from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol

class IntelligenceProvider(Protocol):
    name: str
    def generate(self, prompt: str, context: list[str] | None = None) -> str: ...

@dataclass
class LocalReasoner:
    """Deterministic fallback; external models can implement the same protocol."""
    name: str = "fallback"
    def generate(self, prompt: str, context: list[str] | None = None) -> str:
        context_text = " | ".join(context or [])
        if context_text:
            return f"I understand the request. Relevant memory: {context_text}"
        return "I understand the request, but no external intelligence provider is connected yet."

@dataclass(frozen=True)
class Lesson:
    lesson: str
    confidence: float
    source: str

class LearningEngine:
    """Turns verified observations into candidate lessons; storage approval remains explicit."""
    def propose(self, observation: str, outcome: str, source: str = "experience") -> Lesson | None:
        observation, outcome = observation.strip(), outcome.strip()
        if not observation or not outcome:
            return None
        return Lesson(f"When {observation}, the observed outcome was: {outcome}", 0.5, source)
