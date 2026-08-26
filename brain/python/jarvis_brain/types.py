from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum
from time import time_ns
from typing import Any

class EventKind(str, Enum):
    OBSERVATION="observation"; PREDICTION="prediction"; ACTION="action"; OUTCOME="outcome"
    REFLECTION="reflection"; LEARNING="learning"; EVOLUTION="evolution"; RECOVERY="recovery"
    SIMULATION="simulation"; DECISION="decision"

@dataclass(slots=True)
class Event:
    kind: EventKind
    payload: dict[str, Any]
    timestamp_ns: int = field(default_factory=time_ns)
    sequence: int = 0

@dataclass(slots=True)
class Belief:
    subject: str
    predicate: str
    value: Any
    strength: float = 0.5
    evidence_count: int = 1
    updated_ns: int = field(default_factory=time_ns)

@dataclass(slots=True)
class Prediction:
    key: str
    predicted_value: Any
    basis: tuple[str, ...]
    created_ns: int = field(default_factory=time_ns)
    resolved: bool = False
    error: float | None = None

@dataclass(slots=True)
class CognitiveState:
    identity: str = "JARVIS"
    cycle: int = 0
    active_context: dict[str, Any] = field(default_factory=dict)
    beliefs: dict[str, Belief] = field(default_factory=dict)
    predictions: dict[str, Prediction] = field(default_factory=dict)
    working_memory: list[dict[str, Any]] = field(default_factory=list)
    capabilities: dict[str, float] = field(default_factory=dict)
    performance: dict[str, float] = field(default_factory=dict)
    events_seen: int = 0
    def bounded_working_memory(self, limit: int = 64) -> None:
        if len(self.working_memory) > limit: del self.working_memory[:-limit]
