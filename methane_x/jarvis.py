from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
from typing import Callable

from .intelligence import IntelligenceRequest, IntelligenceProvider, LocalReasoner
from .learning import Experience, LearningEngine
from .persistent_memory import PersistentMemory
from .speech import ConsoleSpeech


@dataclass
class Tool:
    name: str
    handler: Callable[[str], object]


class Jarvis:
    """Integrated perception -> memory -> reasoning -> action -> learning loop."""

    def __init__(
        self,
        memory: PersistentMemory | None = None,
        intelligence: IntelligenceProvider | None = None,
        memory_path: str | Path | None = None,
    ) -> None:
        self.memory = memory or PersistentMemory(memory_path or "data/jarvis_memory.db")
        self.intelligence = intelligence or LocalReasoner()
        self.learning = LearningEngine(self.memory)
        self.speech = ConsoleSpeech()
        self.tools: dict[str, Tool] = {}
        self.running = True

    def register_tool(self, name: str, handler: Callable[[str], object]) -> None:
        normalized = name.strip().lower()
        if not normalized:
            raise ValueError("tool name is required")
        self.tools[normalized] = Tool(normalized, handler)

    def perceive(self, text: str) -> str:
        return text.strip()

    def decide(self, text: str) -> tuple[str, str]:
        low = text.casefold()
        if low in {"exit", "quit", "shutdown"}:
            return "shutdown", ""
        if low in {"status", "health", "system status"}:
            return "status", ""
        if low.startswith("remember "):
            return "remember", text[9:].strip()
        if low.startswith("recall "):
            return "recall", text[7:].strip()
        for name in self.tools:
            if low.startswith(name + " ") or low == name:
                return "tool", name
        return "reason", text

    def process(self, raw: str) -> str:
        text = self.perceive(raw)
        if not text:
            return "I didn't receive a command."
        kind, payload = self.decide(text)
        if kind == "shutdown":
            self.running = False
            return "Shutdown requested."
        if kind == "status":
            return f"Online. Memory: {self.memory.count()} entries. Intelligence: {self.intelligence.name}. Tools: {len(self.tools)}."
        if kind == "remember":
            item = self.memory.remember(payload, tier=3, confidence=1.0, source="user")
            return f"Remembered: {item.content}"
        if kind == "recall":
            items = self.memory.search(payload or text)
            return "\n".join(
                f"[{m.tier}] {m.content} (confidence {m.confidence:.2f})" for m in items
            ) or "I don't have a matching memory."
        if kind == "tool":
            name = payload
            result = str(self.tools[name].handler(text))
            self.learning.learn(Experience(text, name, result, True))
            return result

        memories = self.memory.search(text)
        request = IntelligenceRequest(text, tuple(m.content for m in memories))
        response = self.intelligence.generate(request)
        self.learning.learn(Experience(text, "reason", response.text, True))
        return response.text

    def run(self) -> None:
        self.speech.speak("JARVIS core online. Say 'Jarvis' or type a command.")
        try:
            while self.running:
                raw = self.speech.listen()
                if not raw:
                    continue
                cleaned = raw.strip()
                if cleaned.casefold().startswith("jarvis"):
                    cleaned = cleaned[6:].strip(" ,:—-") or "status"
                self.speech.speak(self.process(cleaned))
        finally:
            self.memory.close()


if __name__ == "__main__":
    Jarvis().run()
