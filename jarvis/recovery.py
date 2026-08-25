from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import Iterable


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
    """Classifies failure evidence before selecting a bounded recovery direction."""

    def classify(self, evidence: Iterable[str]) -> FailureClass:
        text = " ".join(evidence).casefold()
        if any(token in text for token in ("timeout", "temporarily", "unavailable")):
            return FailureClass.TRANSIENT
        if any(token in text for token in ("unknown", "missing", "insufficient information")):
            return FailureClass.INFORMATION
        if any(token in text for token in ("wrong plan", "strategy failed", "invalid approach")):
            return FailureClass.STRATEGY
        if any(token in text for token in ("unsupported", "not capable", "permission denied")):
            return FailureClass.CAPABILITY
        return FailureClass.UNKNOWN

    def decide(self, evidence: Iterable[str]) -> RecoveryDecision:
        failure = self.classify(evidence)
        actions = {
            FailureClass.TRANSIENT: "retry or wait for the environment to stabilize",
            FailureClass.INFORMATION: "gather missing evidence",
            FailureClass.STRATEGY: "generate and evaluate an alternative strategy",
            FailureClass.CAPABILITY: "identify another authorized capability",
            FailureClass.UNKNOWN: "pause and investigate before acting again",
        }
        confidence = 0.8 if failure != FailureClass.UNKNOWN else 0.4
        return RecoveryDecision(failure, actions[failure], confidence)
