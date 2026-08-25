from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import Callable, Iterable


class FailureClass(str, Enum):
    TRANSIENT = "transient"
    INFORMATION = "information"
    STRATEGY = "strategy"
    CAPABILITY = "capability"
    UNKNOWN = "unknown"


@dataclass(frozen=True)
class RecoveryDecision:
    failure: FailureClass
    action: str
    confidence: float


class RecoveryEngine:
    """Recovery substrate. Domain intelligence supplies classification and the recovery strategy."""

    def __init__(self, classifier: Callable[[tuple[str, ...]], FailureClass] | None = None) -> None:
        self.classifier = classifier or (lambda evidence: FailureClass.UNKNOWN)

    def classify(self, evidence: Iterable[str]) -> FailureClass:
        return self.classifier(tuple(evidence))

    def decide(
        self,
        evidence: Iterable[str],
        *,
        strategy: str = "investigate before acting",
        confidence: float = 0.4,
    ) -> RecoveryDecision:
        failure = self.classify(evidence)
        return RecoveryDecision(failure, strategy, max(0.0, min(1.0, confidence)))
