from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Iterable

from .adaptation import AdaptationLedger
from .attention import AttentionController, Focus
from .cognitive_cycle import CognitiveCycle, CycleResult
from .conflict import ConflictResolver
from .continuity import Continuity
from .memory_consolidation import ExperienceRecord, MemoryConsolidator
from .persistence import StateJournal
from .world_model import SelfModel, WorldModel


@dataclass(frozen=True)
class BrainSnapshot:
    identity: str
    cycles: int
    experiences: int
    world_entities: int
    pending_adaptations: int
    capabilities: int
    limitations: int


class Brain:
    """Unified persistent cognitive substrate. Sensors, models and tools plug into this facade."""

    def __init__(self, identity: str = "JARVIS", state_path: str | Path | None = None) -> None:
        self.world = WorldModel()
        self.self_model = SelfModel(identity=identity)
        self.continuity = Continuity(identity=identity)
        self.attention = AttentionController()
        self.conflicts = ConflictResolver()
        self.adaptations = AdaptationLedger()
        self.consolidator = MemoryConsolidator()
        self.cycle = CognitiveCycle()
        self.identity = identity
        self.journal = StateJournal(state_path) if state_path else None
        self._restore()

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
        self.self_model.active_processes.add("thinking")
        result = self.cycle.run(goal, facts=context, options=options, execute=execute)
        self.self_model.active_processes.discard("thinking")
        self.continuity.observe(goal, result.reflection.outcome, bool(result.reflection.what_worked))
        self._persist()
        return result

    def consolidate(self, experiences: list[ExperienceRecord]):
        return self.consolidator.consolidate(experiences)

    def snapshot(self) -> BrainSnapshot:
        return BrainSnapshot(
            identity=self.identity,
            cycles=self.cycle.state.cycle_id,
            experiences=len(self.continuity.experiences),
            world_entities=len(self.world.entities),
            pending_adaptations=len(self.adaptations.proposals),
            capabilities=len(self.self_model.capabilities),
            limitations=len(self.self_model.limitations),
        )

    def _persist(self) -> None:
        if not self.journal:
            return
        self.journal.save({
            "identity": self.identity,
            "cycles": self.cycle.state.cycle_id,
            "history": self.cycle.state.history[-50:],
            "capabilities": sorted(self.self_model.capabilities),
            "limitations": sorted(self.self_model.limitations),
        })

    def _restore(self) -> None:
        if not self.journal:
            return
        state = self.journal.load()
        if state.get("identity"):
            self.identity = str(state["identity"])
            self.self_model.identity = self.identity
        self.cycle.state.cycle_id = int(state.get("cycles", 0))
        self.cycle.state.history.extend(str(x) for x in state.get("history", [])[-50:])
        self.self_model.capabilities.update(str(x) for x in state.get("capabilities", []))
        self.self_model.limitations.update(str(x) for x in state.get("limitations", []))
