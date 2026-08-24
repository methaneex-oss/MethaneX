from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone
from enum import Enum
from uuid import uuid4


class ProcessState(str, Enum):
    OBSERVING = "observing"
    THINKING = "thinking"
    ACTING = "acting"
    REFLECTING = "reflecting"
    RECOVERING = "recovering"
    IDLE = "idle"


@dataclass
class SelfModel:
    identity: str = "JARVIS"
    version: str = "0.1-cognitive"
    capabilities: set[str] = field(default_factory=set)
    limitations: set[str] = field(default_factory=set)
    active_processes: dict[str, ProcessState] = field(default_factory=dict)
    performance: dict[str, float] = field(default_factory=dict)

    def register_capability(self, name: str) -> None:
        self.capabilities.add(name)

    def register_limitation(self, name: str) -> None:
        self.limitations.add(name)

    def set_process(self, name: str, state: ProcessState) -> None:
        self.active_processes[name] = state

    def record_performance(self, metric: str, value: float) -> None:
        self.performance[metric] = max(0.0, min(1.0, value))


@dataclass(frozen=True)
class ExperienceObservation:
    event: str
    outcome: str
    success: bool
    cost: float = 0.0
    timestamp: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


@dataclass(frozen=True)
class EvolutionProposal:
    id: str
    target: str
    reason: str
    expected_benefit: float
    evidence: tuple[str, ...]
    reversible: bool = True


class OrganismState:
    """Continuity layer: self-model, observations and evidence-backed adaptation proposals."""

    def __init__(self, identity: str = "JARVIS") -> None:
        self.self_model = SelfModel(identity=identity)
        self.experiences: list[ExperienceObservation] = []
        self.proposals: list[EvolutionProposal] = []

    def observe(self, event: str, outcome: str, success: bool, cost: float = 0.0) -> ExperienceObservation:
        observation = ExperienceObservation(event, outcome, success, max(0.0, cost))
        self.experiences.append(observation)
        return observation

    def propose_adaptation(self, target: str, reason: str, evidence: list[str], expected_benefit: float) -> EvolutionProposal:
        proposal = EvolutionProposal(
            id=uuid4().hex,
            target=target,
            reason=reason,
            expected_benefit=max(0.0, min(1.0, expected_benefit)),
            evidence=tuple(evidence),
        )
        self.proposals.append(proposal)
        return proposal

    def success_rate(self, event: str | None = None) -> float:
        observations = [x for x in self.experiences if event is None or x.event == event]
        if not observations:
            return 0.0
        return sum(x.success for x in observations) / len(observations)
