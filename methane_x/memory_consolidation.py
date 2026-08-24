from __future__ import annotations

from dataclasses import dataclass

from .memory import Memory, MemoryStore


@dataclass(frozen=True)
class ConsolidationReport:
    considered: int
    promoted: int
    rejected: int


class MemoryConsolidator:
    """Promotes only sufficiently confident experience into approved knowledge."""

    def __init__(self, memory: MemoryStore, threshold: float = 0.8) -> None:
        self.memory = memory
        self.threshold = threshold

    def consolidate(self) -> ConsolidationReport:
        items = self.memory.all()
        promoted = 0
        rejected = 0
        for item in items:
            if item.tier == 3 and item.confidence >= self.threshold:
                self.memory.remember(item.content, confidence=item.confidence, source=item.source, tier=2)
                promoted += 1
            elif item.tier == 3:
                rejected += 1
        return ConsolidationReport(len(items), promoted, rejected)
