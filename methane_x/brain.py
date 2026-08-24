from __future__ import annotations

from dataclasses import dataclass
from typing import Callable

from .memory import MemoryStore


@dataclass(frozen=True)
class Event:
    kind: str
    payload: str


class Brain:
    """Minimal orchestration brain with replaceable reasoning and action adapters."""

    WAKE_WORD = "jarvis"

    def __init__(self, memory: MemoryStore | None = None) -> None:
        self.memory = memory or MemoryStore()
        self._actions: dict[str, Callable[[str], str]] = {}

    def register_action(self, name: str, handler: Callable[[str], str]) -> None:
        self._actions[name.lower()] = handler

    def perceive(self, text: str) -> Event:
        cleaned = text.strip()
        lowered = cleaned.lower()
        if lowered in {"exit", "quit", "shutdown"}:
            return Event("shutdown", cleaned)
        if "remember" in lowered:
            return Event("memory.store", cleaned)
        if lowered in {"status", "system status", "health"}:
            return Event("status", cleaned)
        for action in self._actions:
            if lowered.startswith(action):
                return Event(f"action.{action}", cleaned)
        return Event("conversation", cleaned)

    def handle(self, event: Event) -> str:
        if event.kind == "memory.store":
            content = event.payload.split("remember", 1)[-1].strip(" :")
            if not content:
                return "I need something to remember."
            self.memory.remember(content)
            return f"Stored: {content}"

        if event.kind == "status":
            return f"Online. Memory entries: {len(tuple(self.memory.all()))}. Core: ready."

        if event.kind == "shutdown":
            return "Shutdown requested."

        if event.kind.startswith("action."):
            name = event.kind.split(".", 1)[1]
            return self._actions[name](event.payload)

        memories = self.memory.relevant(event.payload)
        if memories:
            return f"I have a related memory: {memories[0].content}"
        return "Prototype core online. Reasoning and external intelligence adapters are not connected yet."

    def process(self, text: str) -> str:
        return self.handle(self.perceive(text))
