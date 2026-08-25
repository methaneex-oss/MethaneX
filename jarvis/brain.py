from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Iterable

from .adaptation import AdaptationLedger
from .attention import AttentionController, Focus
from .cognitive_cycle import CognitiveCycle, CycleResult
from .conflict import ConflictResolver
from .continuity import Continuity, Experience
from .goals import Goal, GoalArbiter
from .intelligence import IntelligenceFederator
from .memory_consolidation import ExperienceRecord, MemoryConsolidator
from .persistence import StateJournal
from .recovery import RecoveryEngine
from .simulation import Simulator
from .world_model import SelfModel, WorldModel


@dataclass(frozen=True)
class BrainSnapshot:
    identity: str
    cycles: int
    experiences: int
    world_entities: int
    pending_adaptations: int
    active_goals: int
    capabilities: int
    limitations: int


class Brain:
    """Persistent cognitive substrate: one identity, many replaceable cognitive capabilities."""

    def __init__(self, identity: str = "JARVIS", state_path: str | Path | None = None) -> None:
        self.world = WorldModel()
        self.self_model = SelfModel(identity=identity)
        self.continuity = Continuity(identity=identity)
        self.attention = AttentionController()
        self.conflicts = ConflictResolver()
        self.adaptations = AdaptationLedger()
        self.goals = GoalArbiter()
        self.intelligence = IntelligenceFederator()
        self.recovery = RecoveryEngine()
        self.simulator = Simulator()
        self.consolidator = MemoryConsolidator()
        self.cycle = CognitiveCycle()
        self.identity = identity
        self.journal = StateJournal(state_path) if state_path else None
        self._restore()

    def add_goal(self, objective: str, *, priority: float = 0.5, urgency: float = 0.5, confidence: float = 0.5) -> Goal:
        goal = self.goals.add(objective, priority=priority, urgency=urgency, confidence=confidence)
        self._persist()
        return goal

    def choose_goal(self) -> Goal | None:
        return self.goals.choose()

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
        try:
            result = self.cycle.run(goal, facts=context, options=options, execute=execute)
            evaluation = result.decision.evaluation
            self.continuity.record(Experience(
                cycle_id=self.cycle.state.cycle_id,
                goal=goal,
                decision=result.decision.strategy.name if result.decision.strategy else "gather information",
                outcome=result.reflection.outcome,
                success=bool(result.reflection.what_worked),
                confidence=evaluation.confidence if evaluation else 0.0,
            ))
            return result
        finally:
            self.self_model.active_processes.discard("thinking")
            self._persist()

    def consolidate(self, experiences: list[ExperienceRecord]):
        return self.consolidator.consolidate(experiences)

    def snapshot(self) -> BrainSnapshot:
        return BrainSnapshot(
            identity=self.identity,
            cycles=self.cycle.state.cycle_id,
            experiences=len(self.continuity.experiences),
            world_entities=len(self.world.entities),
            pending_adaptations=len(self.adaptations.proposals),
            active_goals=sum(goal.active for goal in self.goals.goals.values()),
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
            "goals": [
                {
                    "objective": goal.objective,
                    "priority": goal.priority,
                    "urgency": goal.urgency,
                    "confidence": goal.confidence,
                    "id": goal.id,
                    "active": goal.active,
                }
                for goal in self.goals.goals.values()
            ],
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
        for saved in state.get("goals", []):
            goal = self.goals.add(
                str(saved.get("objective", "")),
                priority=float(saved.get("priority", 0.5)),
                urgency=float(saved.get("urgency", 0.5)),
                confidence=float(saved.get("confidence", 0.5)),
            )
            goal.active = bool(saved.get("active", True))
