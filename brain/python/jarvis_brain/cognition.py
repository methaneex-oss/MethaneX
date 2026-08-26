from __future__ import annotations
from dataclasses import dataclass
from typing import Any, Iterable

@dataclass(frozen=True, slots=True)
class CandidateAction:
    name: str
    arguments: dict[str, Any]
    expected_value: float
    risk: float
    reversibility: float
    evidence: tuple[str, ...] = ()
    @property
    def utility(self) -> float:
        return self.expected_value - self.risk + 0.2 * self.reversibility

@dataclass(frozen=True, slots=True)
class Reflection:
    expected: Any
    actual: Any
    error: float
    lesson: str

def build_context(observation: dict[str, Any], working_memory: Iterable[dict[str, Any]]) -> dict[str, Any]:
    recent = list(working_memory)[-8:]
    return {"current": observation, "recent": recent, "keys": tuple(observation.keys())}

def compare_values(expected: Any, actual: Any) -> float:
    if expected == actual: return 0.0
    if isinstance(expected, (int, float)) and isinstance(actual, (int, float)):
        denominator = max(1.0, abs(float(expected)), abs(float(actual)))
        return min(1.0, abs(float(expected) - float(actual)) / denominator)
    return 1.0

def reflect(expected: Any, actual: Any) -> Reflection:
    error = compare_values(expected, actual)
    lesson = "prediction matched observation" if error == 0.0 else "prediction and observation differed; retain the discrepancy for future revision"
    return Reflection(expected, actual, error, lesson)

def rank_actions(actions: Iterable[CandidateAction]) -> list[CandidateAction]:
    return sorted(actions, key=lambda action: action.utility, reverse=True)
