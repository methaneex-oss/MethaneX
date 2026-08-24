from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable

from .cognition import CognitiveWorkspace, Evaluation, Metacognition, build_workspace
from .strategy import Strategy, StrategyEngine


@dataclass(frozen=True)
class CognitiveDecision:
    goal: str
    strategy: Strategy | None
    evaluation: Evaluation | None
    context: tuple[str, ...]


class CognitiveEngine:
    """Core decision layer: model the situation, compare strategies, evaluate, then decide."""

    def __init__(self, strategy_engine: StrategyEngine | None = None, metacognition: Metacognition | None = None) -> None:
        self.strategy_engine = strategy_engine or StrategyEngine()
        self.metacognition = metacognition or Metacognition()

    def decide(
        self,
        goal: str,
        *,
        facts: Iterable[str] = (),
        options: Iterable[tuple[str, Iterable[str]]] = (),
    ) -> CognitiveDecision:
        workspace = build_workspace(goal, facts)
        strategies = self.strategy_engine.propose(goal, options)
        strategy = self.strategy_engine.choose(strategies)
        evaluation = self.metacognition.evaluate(workspace, strategy.steps[0] if strategy else "gather more information")
        workspace.think("decision", strategy.name if strategy else "information gathering", evaluation.confidence)
        return CognitiveDecision(goal, strategy, evaluation, workspace.context())
