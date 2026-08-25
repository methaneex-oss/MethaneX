from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum


class ProcessPhase(str, Enum):
    IDLE = "idle"
    OBSERVING = "observing"
    REASONING = "reasoning"
    SIMULATING = "simulating"
    ACTING = "acting"
    REFLECTING = "reflecting"
    RECOVERING = "recovering"


@dataclass
class CognitiveProcess:
    name: str
    phase: ProcessPhase = ProcessPhase.IDLE
    load: float = 0.0
    metadata: dict[str, object] = field(default_factory=dict)


class ProcessRegistry:
    """Makes distributed cognitive processes inspectable and independently stateful."""

    def __init__(self) -> None:
        self.processes: dict[str, CognitiveProcess] = {}

    def register(self, name: str) -> CognitiveProcess:
        process = self.processes.setdefault(name, CognitiveProcess(name))
        return process

    def set_phase(self, name: str, phase: ProcessPhase, load: float | None = None) -> CognitiveProcess:
        process = self.register(name)
        process.phase = phase
        if load is not None:
            process.load = max(0.0, min(1.0, load))
        return process

    def active(self) -> tuple[CognitiveProcess, ...]:
        return tuple(p for p in self.processes.values() if p.phase != ProcessPhase.IDLE)
