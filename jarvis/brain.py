from __future__ import annotations

from dataclasses import dataclass
from typing import Callable, Iterable

from .adaptation import AdaptationLedger
from .attention import AttentionController, Focus
from .cognitive_cycle import CognitiveCycle, CycleResult
from .conflict import ConflictResolver
from .continuity import Continuity
from .memory_consolidation import ExperienceRecord, MemoryConsolidator
from .world_model import SelfModel, WorldModel


@dataclass(frozen=True)
class BrainSnapshot:
    identity: str
    cycles: int
    experiences: int
    world_entities: int
    pending_adaptations: int


class Brain:
    """Unified cognitive substrate. Sensors, speech, tools and models plug into this facade."""

    def __init__(self, identity: str = "JARVIS") -> None:
        self.world = WorldModel()
        self.self_model = SelfModel(identity=identity)
        self.continuity = Continuity(identity=identity)
        self.attention = AttentionController()
        self.conflicts = ConflictResolver()
        self.adaptations = AdaptationLedger()
        self.consolidator = MemoryConsolidator()
        self.cycle = CognitiveCycle()
        self.identity = identity

    def think(
        self,
        goal: str,
        *,
        observations: Iterable[Focus] = (),
        facts: Iterable[str] = (),
        options: Iterable[tuple[str, Iterable[str]]] = (),
        execute: Callable[[str], str] | None = None,
    ) -> CycleResult:
        focused = self.attention.select(observations)
        context = tuple(facts) + tuple(f"attention: {item.item}" for item in focused)
        return self.cycle.run(goal, facts=context, options=options, execute=execute)

    def consolidate(self, experiences: list[ExperienceRecord]):
        return self.consolidator.consolidate(experiences)

    def snapshot(self) -> BrainSnapshot:
        return BrainSnapshot(
            identity=self.identity,
            cycles=self.cycle.state.cycle_id,
            experiences=len(self.continuity.experiences),
            world_entities=len(self.world.entities),
            pending_adaptations=len(self.adaptations.proposals),
        )
