from __future__ import annotations

from .brain import Brain
from .config import Settings
from .health import HealthMonitor
from .intelligence import IntelligenceRouter, LocalReasoner
from .learning import Experience, LearningEngine
from .memory import MemoryStore
from .observability import EventLog
from .safety import ActionGuard, ActionRequest, CapabilityPolicy
from .verification import VerifiedExecutor
from .voice import WakeWordDetector


class JarvisRuntime:
    """Application runtime wiring the core cognitive subsystems together."""

    def __init__(self, settings: Settings | None = None) -> None:
        self.settings = settings or Settings.from_env()
        self.memory = MemoryStore(self.settings.memory_path)
        self.intelligence = IntelligenceRouter([LocalReasoner()])
        self.wake_word = WakeWordDetector(self.settings.wake_words)
        self.brain = Brain(memory=self.memory, intelligence=self.intelligence)
        self.learning = LearningEngine(self.memory)
        self.events = EventLog()
        self.policy = CapabilityPolicy()
        self.guard = ActionGuard(self.policy)
        self.health = HealthMonitor()
        self.health.register("memory", lambda: f"{len(self.memory.all())} memories")
        self.health.register("intelligence", lambda: f"{len(self.intelligence.providers)} provider(s)")

    def process(self, text: str) -> str:
        self.events.emit("input.received", text=text)
        output = self.brain.process(text)
        self.learning.learn(Experience(text, text, output, True))
        self.events.emit("response.completed", output=output)
        return output

    def execute_verified(self, capability: str, action: str, execute, verify):
        self.guard.authorize(ActionRequest(capability, action))
        self.events.emit("action.authorized", capability=capability, action=action)
        result = VerifiedExecutor(execute, verify).run(action)
        self.events.emit("action.verified", capability=capability, ok=result.ok, attempts=result.attempts)
        return result

    def close(self) -> None:
        self.memory.close()
