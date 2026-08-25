from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone


@dataclass(frozen=True)
class Experience:
    cycle_id: int
    goal: str
    decision: str
    outcome: str
    success: bool
    confidence: float
    timestamp: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


@dataclass
class Continuity:
    """Durable in-process continuity: experiences and identity survive individual cycles."""
    identity: str = "JARVIS"
    experiences: list[Experience] = field(default_factory=list)
    generation: int = 0

    def record(self, experience: Experience) -> None:
        self.experiences.append(experience)
        self.generation += 1

    def recent(self, limit: int = 20) -> tuple[Experience, ...]:
        return tuple(self.experiences[-max(0, limit):])

    def success_rate(self, goal: str | None = None) -> float:
        items = [e for e in self.experiences if goal is None or e.goal == goal]
        if not items:
            return 0.0
        return sum(e.success for e in items) / len(items)
