from __future__ import annotations

from .brain import Brain
from .config import Settings
from .intelligence import IntelligenceRouter, LocalReasoner
from .memory import MemoryStore
from .voice import WakeWordDetector


class JarvisRuntime:
    """Application runtime wiring the core subsystems together."""

    def __init__(self, settings: Settings | None = None) -> None:
        self.settings = settings or Settings.from_env()
        self.memory = MemoryStore(self.settings.memory_path)
        self.intelligence = IntelligenceRouter([LocalReasoner()])
        self.wake_word = WakeWordDetector(self.settings.wake_words)
        self.brain = Brain(memory=self.memory, intelligence=self.intelligence)

    def process(self, text: str) -> str:
        return self.brain.process(text)

    def close(self) -> None:
        self.memory.close()
