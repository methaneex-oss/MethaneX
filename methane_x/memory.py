from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone
from typing import Iterable


@dataclass(frozen=True)
class Memory:
    content: str
    confidence: float = 1.0
    source: str = "user"
    created_at: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


class MemoryStore:
    """Small in-process memory layer; persistence is intentionally pluggable later."""

    def __init__(self) -> None:
        self._items: list[Memory] = []

    def remember(self, content: str, *, confidence: float = 1.0, source: str = "user") -> Memory:
        confidence = max(0.0, min(1.0, confidence))
        item = Memory(content=content.strip(), confidence=confidence, source=source)
        self._items.append(item)
        return item

    def all(self) -> Iterable[Memory]:
        return tuple(self._items)

    def relevant(self, query: str) -> list[Memory]:
        terms = {word.lower() for word in query.split() if word.strip()}
        scored = []
        for item in self._items:
            overlap = len(terms & set(item.content.lower().split()))
            if overlap:
                scored.append((overlap * item.confidence, item))
        return [item for _, item in sorted(scored, key=lambda pair: pair[0], reverse=True)]
