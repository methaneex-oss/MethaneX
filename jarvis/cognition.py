from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from typing import Iterable


class BeliefStatus(str, Enum):
    HYPOTHESIS = "hypothesis"
    SUPPORTED = "supported"
    CONTRADICTED = "contradicted"


@dataclass
class Belief:
    statement: str
    confidence: float = 0.5
    status: BeliefStatus = BeliefStatus.HYPOTHESIS
    sources: list[str] = field(default_factory=list)

    def update(self, confidence: float, status: BeliefStatus | None = None, source: str | None = None) -> None:
        self.confidence = max(0.0, min(1.0, confidence))
        if status is not None:
            self.status = status
        if source and source not in self.sources:
            self.sources.append(source)


@dataclass(frozen=True)
class Thought:
    kind: str
    content: str
    confidence: float


@dataclass
class CognitiveWorkspace:
    goal: str
    beliefs: dict[str, Belief] = field(default_factory=dict)
    thoughts: list[Thought] = field(default_factory=list)
    uncertainties: list[str] = field(default_factory=list)
    constraints: list[str] = field(default_factory=list)

    def add_belief(self, statement: str, confidence: float = 0.5, source: str | None = None) -> Belief:
        belief = self.beliefs.get(statement)
        if belief is None:
            belief = Belief(
                statement=statement,
                confidence=max(0.0, min(1.0, confidence)),
                sources=[source] if source else [],
            )
            self.beliefs[statement] = belief
        else:
            belief.update(confidence, source=source)
        return belief

    def add_uncertainty(self, item: str) -> None:
        if item and item not in self.uncertainties:
            self.uncertainties.append(item)

    def think(self, kind: str, content: str, confidence: float = 0.5) -> Thought:
        thought = Thought(kind, content, max(0.0, min(1.0, confidence)))
        self.thoughts.append(thought)
        return thought

    def context(self, limit: int = 12) -> tuple[str, ...]:
        items = [f"goal: {self.goal}"]
        items.extend(f"belief: {b.statement} ({b.confidence:.2f})" for b in self.beliefs.values())
        items.extend(f"uncertainty: {u}" for u in self.uncertainties)
        items.extend(f"constraint: {c}" for c in self.constraints)
        return tuple(items[-limit:])


@dataclass(frozen=True)
class Evaluation:
    success_probability: float
    confidence: float
    risks: tuple[str, ...]
    next_step: str
    rationale: str


class Metacognition:
    """Evaluates the quality and uncertainty of a proposed cognitive step."""

    def evaluate(self, workspace: CognitiveWorkspace, candidate: str) -> Evaluation:
        uncertainty_penalty = min(0.6, 0.1 * len(workspace.uncertainties))
        base = max(0.0, min(1.0, 0.7 - uncertainty_penalty))
        risks = tuple(workspace.uncertainties[:5])
        return Evaluation(
            success_probability=base,
            confidence=base,
            risks=risks,
            next_step=candidate,
            rationale="Candidate evaluated against current beliefs, uncertainty, and constraints.",
        )


def build_workspace(goal: str, facts: Iterable[str] = ()) -> CognitiveWorkspace:
    workspace = CognitiveWorkspace(goal=goal.strip())
    for fact in facts:
        if fact.strip():
            workspace.add_belief(fact, confidence=0.6, source="context")
    return workspace
