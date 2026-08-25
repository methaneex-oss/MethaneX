from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable, Protocol


@dataclass(frozen=True)
class IntelligenceResult:
    provider: str
    content: str
    confidence: float
    latency_ms: float = 0.0


class IntelligenceProvider(Protocol):
    name: str

    def reason(self, prompt: str, context: tuple[str, ...]) -> IntelligenceResult: ...


class IntelligenceFederator:
    """Keeps cognition independent of any single model; providers are replaceable capabilities."""

    def __init__(self, providers: Iterable[IntelligenceProvider] = ()) -> None:
        self.providers = list(providers)

    def register(self, provider: IntelligenceProvider) -> None:
        if provider not in self.providers:
            self.providers.append(provider)

    def query(self, prompt: str, context: Iterable[str] = ()) -> tuple[IntelligenceResult, ...]:
        normalized = tuple(context)
        results: list[IntelligenceResult] = []
        for provider in tuple(self.providers):
            try:
                result = provider.reason(prompt, normalized)
                results.append(result)
            except Exception:
                continue
        return tuple(results)

    def best(self, results: Iterable[IntelligenceResult]) -> IntelligenceResult | None:
        return max(results, key=lambda result: result.confidence, default=None)
