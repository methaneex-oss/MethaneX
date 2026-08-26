from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
from typing import Callable, Iterable

from .adaptation import AdaptationLedger
from .attention import AttentionController, Focus
from .cognitive_cycle import CognitiveCycle, CycleResult
from .conflict import ConflictResolver
from .continuity import Continuity, Experience
from .evolution import EvolutionEngine, ShadowResult
from .goals import Goal, GoalArbiter
from .intelligence import IntelligenceFederator
from .memory_consolidation import ExperienceRecord, MemoryConsolidator
from .persistence import StateJournal
from .recovery import RecoveryEngine
from .simulation import Simulator
from .world_model import EntityState, SelfModel, WorldModel


@dataclass(frozen=True)
class BrainSnapshot:
    identity: str
    cycles: int
    experiences: int
    world_entities: int
    world_relations: int
    pending_adaptations: int
    active_goals: int
    capabilities: int
    limitations: int
    evaluated_evolutions: int


class Brain:
    """Persistent cognitive substrate: one identity, many replaceable cognitive capabilities."""

    def __init__(self, identity: str = "JARVIS", state_path: str | Path | None = None) -> None:
        self.world = WorldModel()
        self.self_model = SelfModel(identity=identity)
        self.continuity = Continuity(identity=identity)
        self.attention = AttentionController()
        self.conflicts = ConflictResolver()
        self.adaptations = AdaptationLedger()
        self.evolution = EvolutionEngine()
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

    def observe(self, name: str, attributes: dict[str, object], confidence: float = 0.5) -> EntityState:
        entity = self.world.observe(name, attributes, confidence)
        self._persist()
        return entity

    def relate(self, subject: str, relation: str, object_: str) -> None:
        self.world.relate(subject, relation, object_)
        self._persist()

    def record_capability(self, capability: str) -> None:
        self.self_model.register_capability(capability)
        self._persist()

    def record_limitation(self, limitation: str) -> None:
        self.self_model.register_limitation(limitation)
        self._persist()

    def record_metric(self, name: str, value: float) -> None:
        self.self_model.record_metric(name, value)
        self._persist()

    def propose_adaptation(self, target: str, change: str, evidence: list[str], expected_benefit: float, reversible: bool = True):
        proposal = self.adaptations.propose(target, change, evidence, expected_benefit, reversible)
        self._persist()
        return proposal

    def evaluate_evolution(
        self,
        scorer: Callable[[str, str], tuple[float, float]],
        *,
        minimum_improvement: float = 0.0,
    ) -> tuple[ShadowResult, ...]:
        """Evaluate reversible adaptations in shadow mode; nothing is applied automatically."""
        results = self.evolution.evaluate(
            self.adaptations.proposals,
            scorer,
            minimum_improvement=minimum_improvement,
        )
        self._persist()
        return results

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
            world_relations=len(self.world.relations),
            pending_adaptations=len(self.adaptations.proposals),
            active_goals=sum(goal.active for goal in self.goals.goals.values()),
            capabilities=len(self.self_model.capabilities),
            limitations=len(self.self_model.limitations),
            evaluated_evolutions=len(self.evolution.history),
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
            "performance": self.self_model.performance,
            "experiences": [
                {
                    "cycle_id": experience.cycle_id,
                    "goal": experience.goal,
                    "decision": experience.decision,
                    "outcome": experience.outcome,
                    "success": experience.success,
                    "confidence": experience.confidence,
                    "timestamp": experience.timestamp,
                }
                for experience in self.continuity.experiences[-200:]
            ],
            "world": {
                "entities": {
                    name: {
                        "attributes": entity.attributes,
                        "confidence": entity.confidence,
                        "observed_at": entity.observed_at,
                    }
                    for name, entity in self.world.entities.items()
                },
                "relations": [list(relation) for relation in sorted(self.world.relations)],
            },
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
            "evolution": [
                {
                    "target": result.target,
                    "change": result.change,
                    "baseline_score": result.baseline_score,
                    "candidate_score": result.candidate_score,
                    "improvement": result.improvement,
                    "accepted": result.accepted,
                    "reason": result.reason,
                }
                for result in self.evolution.history[-200:]
            ],
        })

    def _restore(self) -> None:
        if not self.journal:
            return
        state = self.journal.load()
        if not state:
            return
        if state.get("identity"):
            self.identity = str(state["identity"])
            self.self_model.identity = self.identity
            self.continuity.identity = self.identity
        try:
            self.cycle.state.cycle_id = max(0, int(state.get("cycles", 0)))
        except (TypeError, ValueError):
            self.cycle.state.cycle_id = 0
        history = state.get("history", [])
        if isinstance(history, list):
            self.cycle.state.history.extend(str(x) for x in history[-50:])
        capabilities = state.get("capabilities", [])
        if isinstance(capabilities, (list, tuple, set)):
            self.self_model.capabilities.update(str(x) for x in capabilities)
        limitations = state.get("limitations", [])
        if isinstance(limitations, (list, tuple, set)):
            self.self_model.limitations.update(str(x) for x in limitations)
        performance = state.get("performance", {})
        if isinstance(performance, dict):
            for key, value in performance.items():
                try:
                    self.self_model.performance[str(key)] = float(value)
                except (TypeError, ValueError):
                    continue
        world = state.get("world", {})
        if isinstance(world, dict):
            entities = world.get("entities", {})
            if isinstance(entities, dict):
                for name, saved in entities.items():
                    if not isinstance(saved, dict):
                        continue
                    attributes = saved.get("attributes", {})
                    if not isinstance(attributes, dict):
                        attributes = {}
                    try:
                        confidence = max(0.0, min(1.0, float(saved.get("confidence", 0.5))))
                    except (TypeError, ValueError):
                        confidence = 0.5
                    entity = EntityState(str(name), dict(attributes), confidence)
                    observed_at = str(saved.get("observed_at", ""))
                    if observed_at:
                        entity.observed_at = observed_at
                    self.world.entities[str(name)] = entity
            relations = world.get("relations", [])
            if isinstance(relations, list):
                for relation in relations:
                    if isinstance(relation, (list, tuple)) and len(relation) == 3:
                        self.world.relations.add(tuple(str(x) for x in relation))
        experiences = state.get("experiences", [])
        if isinstance(experiences, list):
            for saved in experiences:
                if not isinstance(saved, dict):
                    continue
                try:
                    timestamp = str(saved.get("timestamp", ""))
                    if timestamp:
                        datetime.fromisoformat(timestamp.replace("Z", "+00:00"))
                    self.continuity.record(Experience(
                        cycle_id=int(saved.get("cycle_id", 0)),
                        goal=str(saved.get("goal", "")),
                        decision=str(saved.get("decision", "")),
                        outcome=str(saved.get("outcome", "")),
                        success=bool(saved.get("success", False)),
                        confidence=max(0.0, min(1.0, float(saved.get("confidence", 0.0)))),
                        timestamp=timestamp or datetime.now(timezone.utc).isoformat(),
                    ))
                except (TypeError, ValueError):
                    continue
        goals = state.get("goals", [])
        if isinstance(goals, list):
            for saved in goals:
                if not isinstance(saved, dict):
                    continue
                objective = str(saved.get("objective", "")).strip()
                if not objective:
                    continue
                try:
                    priority = float(saved.get("priority", 0.5))
                    urgency = float(saved.get("urgency", 0.5))
                    confidence = float(saved.get("confidence", 0.5))
                except (TypeError, ValueError):
                    priority = urgency = confidence = 0.5
                goal = self.goals.add(objective, priority=priority, urgency=urgency, confidence=confidence)
                generated_id = goal.id
                saved_id = str(saved.get("id", generated_id))
                goal.id = saved_id
                goal.active = bool(saved.get("active", True))
                self.goals.goals.pop(generated_id, None)
                self.goals.goals[saved_id] = goal
        evolution = state.get("evolution", [])
        if isinstance(evolution, list):
            for saved in evolution:
                if not isinstance(saved, dict):
                    continue
                try:
                    self.evolution.history.append(ShadowResult(
                        target=str(saved.get("target", "")),
                        change=str(saved.get("change", "")),
                        baseline_score=max(0.0, min(1.0, float(saved.get("baseline_score", 0.0)))),
                        candidate_score=max(0.0, min(1.0, float(saved.get("candidate_score", 0.0)))),
                        improvement=float(saved.get("improvement", 0.0)),
                        accepted=bool(saved.get("accepted", False)),
                        reason=str(saved.get("reason", "")),
                    ))
                except (TypeError, ValueError):
                    continue
