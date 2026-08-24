from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol, Sequence


@dataclass(frozen=True)
class IntelligenceRequest:
    prompt: str
    context: tuple[str, ...] = ()


@dataclass(frozen=True)
class IntelligenceResponse:
    text: str
    provider: str
    confidence: float = 0.5


class IntelligenceProvider(Protocol):
    name: str

    def generate(self, request: IntelligenceRequest) -> IntelligenceResponse: ...


@dataclass
class LocalReasoner:
    name: str = "fallback"

    def generate(self, request: IntelligenceRequest) -> IntelligenceResponse:
        context_text = " | ".join(request.context)
        text = f"I understand the request. Relevant memory: {context_text}" if context_text else "I understand the request, but no external intelligence provider is connected yet."
        return IntelligenceResponse(text=text, provider=self.name, confidence=0.1)


class IntelligenceRouter:
    """Provider-neutral orchestration; no external model is permanently embedded."""

    def __init__(self, providers: Sequence[IntelligenceProvider] = ()) -> None:
        self._providers = list(providers)

    def register(self, provider: IntelligenceProvider) -> None:
        self._providers.append(provider)

    @property
    def providers(self) -> tuple[IntelligenceProvider, ...]:
        return tuple(self._providers)

    def generate(self, request: IntelligenceRequest) -> IntelligenceResponse:
        if not self._providers:
            raise RuntimeError("No intelligence provider is configured")
        responses = [provider.generate(request) for provider in self._providers]
        return max(responses, key=lambda item: item.confidence)


@dataclass(frozen=True)
class Lesson:
    lesson: str
    confidence: float
    source: str


class LearningEngine:
    """Creates bounded candidate lessons from observed outcomes for later validation/storage."""

    def propose(self, observation: str, outcome: str, source: str = "experience") -> Lesson | None:
        observation, outcome = observation.strip(), outcome.strip()
        if not observation or not outcome:
            return None
        return Lesson(f"When {observation}, the observed outcome was: {outcome}", 0.5, source)
