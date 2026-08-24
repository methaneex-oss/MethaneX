"""MethaneX JARVIS prototype package."""

from .cognitive_loop import CognitiveLoop, CycleResult
from .decision import Candidate, DecisionEngine
from .devices import Device, DeviceRegistry
from .goals import Goal, GoalManager, GoalState
from .health import HealthMonitor
from .intelligence import IntelligenceRequest, IntelligenceResponse, IntelligenceRouter
from .learning import Experience, LearningEngine
from .memory import Memory, MemoryStore
from .memory_consolidation import MemoryConsolidator
from .perception import Observation, PerceptionHub
from .planning import Plan, Planner, Task, TaskState
from .recovery import RecoveryController
from .safety import ActionGuard, ActionRequest, CapabilityPolicy
from .tools import Tool, ToolRegistry
from .verification import VerifiedExecutor
from .voice import ConsoleSpeech, WakeWordDetector

__version__ = "0.3.0"

__all__ = [
    "ActionGuard", "ActionRequest", "Candidate", "CapabilityPolicy", "CognitiveLoop", "ConsoleSpeech",
    "CycleResult", "DecisionEngine", "Device", "DeviceRegistry", "Experience", "Goal", "GoalManager",
    "GoalState", "HealthMonitor", "IntelligenceRequest", "IntelligenceResponse", "IntelligenceRouter",
    "LearningEngine", "Memory", "MemoryConsolidator", "MemoryStore", "Observation", "PerceptionHub",
    "Plan", "Planner", "RecoveryController", "Task", "TaskState", "Tool", "ToolRegistry",
    "VerifiedExecutor", "WakeWordDetector",
]
