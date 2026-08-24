from __future__ import annotations

from dataclasses import dataclass
from .intelligence import IntelligenceProvider, LocalReasoner, LearningEngine
from .persistent_memory import PersistentMemory
from .speech import ConsoleSpeech

@dataclass
class Tool:
    name: str
    handler: object

class Jarvis:
    """Integrated perception -> memory -> reasoning -> action -> learning loop."""
    def __init__(self, memory: PersistentMemory | None = None, intelligence: IntelligenceProvider | None = None):
        self.memory = memory or PersistentMemory()
        self.intelligence = intelligence or LocalReasoner()
        self.learning = LearningEngine()
        self.speech = ConsoleSpeech()
        self.tools: dict[str, Tool] = {}
        self.running = True

    def register_tool(self, name: str, handler) -> None:
        self.tools[name.lower()] = Tool(name.lower(), handler)

    def perceive(self, text: str) -> str:
        return text.strip()

    def decide(self, text: str) -> tuple[str, str]:
        low = text.lower()
        if low in {"exit", "quit", "shutdown"}: return "shutdown", ""
        if low in {"status", "health", "system status"}: return "status", ""
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
            return "\n".join(f"[{m.tier}] {m.content} (confidence {m.confidence:.2f})" for m in items) or "I don't have a matching memory."
        if kind == "tool":
            name = payload
            result = str(self.tools[name].handler(text))
            lesson = self.learning.propose(text, result)
            if lesson and lesson.confidence >= 0.8:
                self.memory.remember(lesson.lesson, tier=3, confidence=lesson.confidence, source=lesson.source)
            return result
        memories = self.memory.search(text)
        return self.intelligence.generate(text, [m.content for m in memories])

    def run(self) -> None:
        self.speech.speak("JARVIS core online. Say 'Jarvis' or type a command.")
        while self.running:
            raw = self.speech.listen()
            if not raw: continue
            cleaned = raw.strip()
            if cleaned.lower().startswith("jarvis"):
                cleaned = cleaned[6:].strip(" ,:—-") or "status"
            self.speech.speak(self.process(cleaned))

if __name__ == "__main__":
    Jarvis().run()
