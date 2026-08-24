from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Callable

from .cognitive_loop import CognitiveLoop
from .intelligence import IntelligenceRouter, LocalReasoner
from .learning import Experience, LearningEngine
from .memory import MemoryStore
from .planning import Planner
from .safety import ActionGuard, ActionRequest, CapabilityPolicy


@dataclass(frozen=True)
class Event:
    kind: str
    payload: str


class Brain:
    """JARVIS orchestration layer: perception, memory, planning, intelligence and guarded actions."""

    def __init__(self, memory: MemoryStore | None = None, *, memory_path: str | Path | None = None) -> None:
        self.memory = memory or MemoryStore(memory_path)
        self.intelligence = IntelligenceRouter([LocalReasoner()])
        self.planner = Planner()
        self.cognition = CognitiveLoop(self.planner, self.intelligence)
        self.learning = LearningEngine(self.memory)
        self.policy = CapabilityPolicy()
        self.guard = ActionGuard(self.policy)
        self._actions: dict[str, tuple[str, Callable[[str], str]]] = {}

    def register_action(self, name: str, handler: Callable[[str], str], *, capability: str | None = None) -> None:
        action_name = name.lower()
        self._actions[action_name] = (capability or f"action.{action_name}", handler)

    def allow_capability(self, capability: str) -> None:
        self.policy.allow(capability)

    def perceive(self, text: str) -> Event:
        cleaned = text.strip()
        lowered = cleaned.lower()
        if lowered in {"exit", "quit", "shutdown"}:
            return Event("shutdown", cleaned)
        if lowered.startswith("remember "):
            return Event("memory.store", cleaned)
        if lowered in {"status", "system status", "health"}:
            return Event("status", cleaned)
        for action in self._actions:
            if lowered.startswith(action):
                return Event(f"action.{action}", cleaned)
        return Event("goal", cleaned)

    def handle(self, event: Event) -> str:
        if event.kind == "memory.store":
            content = event.payload[len("remember"):].strip(" :")
            if not content:
                return "I need something to remember."
            self.memory.remember(content, tier=3, source="user")
            return f"Stored: {content}"

        if event.kind == "status":
            return f"Online. Memory entries: {len(self.memory.all())}. Brain: ready. Intelligence providers: {len(self.intelligence.providers)}."

        if event.kind == "shutdown":
            return "Shutdown requested."

        if event.kind.startswith("action."):
            name = event.kind.split(".", 1)[1]
            capability, handler = self._actions[name]
            self.guard.authorize(ActionRequest(capability, event.payload))
            result = handler(event.payload)
            self.learning.learn(Experience(event.payload, name, result, True))
            return result

        memories = tuple(self.memory.relevant(event.payload, limit=5))
        context = tuple(item.content for item in memories)
        plan = self.planner.create(event.payload)
        task = self.planner.next(plan)
        if task is None:
            return "I could not create an executable plan."
        response = self.intelligence.generate(__import__("methane_x.intelligence", fromlist=["IntelligenceRequest"]).IntelligenceRequest(event.payload, context))
        self.learning.learn(Experience(event.payload, "reason", response.text, True))
        return response.text

    def process(self, text: str) -> str:
        return self.handle(self.perceive(text))
