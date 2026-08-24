from __future__ import annotations

from dataclasses import dataclass, field
from typing import Callable, Iterable

from .cognitive_engine import CognitiveDecision, CognitiveEngine
from .reflection import Reflection, Reflector


@dataclass
class CycleState:
    cycle_id: int = 0
    phase: str = "idle"
    history: list[str] = field(default_factory=list)


@dataclass(frozen=True)
class CycleResult:
    decision: CognitiveDecision
    action_output: str | None
    reflection: Reflection


class CognitiveCycle:
    """A bounded cognitive loop that can observe, decide, act, and reflect."""

    def __init__(self, engine: CognitiveEngine | None = None, reflector: Reflector | None = None) -> None:
        self.engine = engine or CognitiveEngine()
        self.reflector = reflector or Reflector()
        self.state = CycleState()

    def run(
        self,
        goal: str,
        *,
        facts: Iterable[str] = (),
        options: Iterable[tuple[str, Iterable[str]]] = (),
        execute: Callable[[str], str] | None = None,
    ) -> CycleResult:
        self.state.cycle_id += 1
        self.state.phase = "thinking"
        decision = self.engine.decide(goal, facts=facts, options=options)
        candidate = decision.strategy.steps[0] if decision.strategy else "gather more information"
        self.state.history.append(f"decision:{candidate}")
        self.state.phase = "acting"
        output = execute(candidate) if execute else None
        observed = output if output is not None else candidate
        self.state.phase = "reflecting"
        reflection = self.reflector.reflect(
            outcome=observed,
            expected=candidate,
            evidence=list(decision.context),
            confidence=decision.evaluation.confidence if decision.evaluation else 0.0,
        )
        self.state.history.append(f"reflection:{reflection.confidence:.2f}")
        self.state.phase = "idle"
        return CycleResult(decision, output, reflection)
