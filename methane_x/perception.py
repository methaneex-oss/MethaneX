from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


@dataclass(frozen=True)
class Observation:
    modality: str
    content: object
    confidence: float = 0.5
    source: str = "unknown"


class VisionProvider(Protocol):
    name: str

    def analyze(self, image: bytes) -> Observation: ...


class PerceptionHub:
    """Collects normalized observations without coupling cognition to sensors."""

    def __init__(self) -> None:
        self._observations: list[Observation] = []

    def ingest(self, observation: Observation) -> Observation:
        self._observations.append(observation)
        return observation

    def recent(self, limit: int = 20) -> tuple[Observation, ...]:
        return tuple(self._observations[-max(0, limit):])
