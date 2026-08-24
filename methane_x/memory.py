from __future__ import annotations

import json
import sqlite3
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path


@dataclass(frozen=True)
class Memory:
    content: str
    confidence: float = 1.0
    source: str = "user"
    tier: int = 3
    created_at: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


class MemoryStore:
    """Persistent memory with identity, approved knowledge and experience tiers."""

    def __init__(self, path: str | Path | None = None) -> None:
        self.path = Path(path) if path else None
        self._items: list[Memory] = []
        self._db: sqlite3.Connection | None = None
        if self.path:
            self.path.parent.mkdir(parents=True, exist_ok=True)
            self._db = sqlite3.connect(self.path)
            self._db.execute(
                "CREATE TABLE IF NOT EXISTS memories (content TEXT NOT NULL, confidence REAL NOT NULL, source TEXT NOT NULL, tier INTEGER NOT NULL, created_at TEXT NOT NULL)"
            )
            self._db.commit()

    def remember(self, content: str, *, confidence: float = 1.0, source: str = "user", tier: int = 3) -> Memory:
        if tier not in (1, 2, 3):
            raise ValueError("tier must be 1, 2, or 3")
        content = content.strip()
        if not content:
            raise ValueError("memory cannot be empty")
        confidence = max(0.0, min(1.0, confidence))
        item = Memory(content=content, confidence=confidence, source=source, tier=tier)
        if self._db:
            self._db.execute("INSERT INTO memories VALUES (?, ?, ?, ?, ?)", (item.content, item.confidence, item.source, item.tier, item.created_at))
            self._db.commit()
        else:
            self._items.append(item)
        return item

    def all(self) -> tuple[Memory, ...]:
        if not self._db:
            return tuple(self._items)
        rows = self._db.execute("SELECT content, confidence, source, tier, created_at FROM memories ORDER BY rowid").fetchall()
        return tuple(Memory(*row) for row in rows)

    def relevant(self, query: str, *, limit: int = 10) -> list[Memory]:
        terms = {word.lower() for word in query.split() if word.strip()}
        if not terms or limit < 1:
            return []
        scored: list[tuple[float, Memory]] = []
        for item in self.all():
            overlap = len(terms & set(item.content.lower().split()))
            if overlap:
                scored.append((overlap * item.confidence, item))
        return [item for _, item in sorted(scored, key=lambda pair: pair[0], reverse=True)[:limit]]

    def export_json(self) -> str:
        return json.dumps([memory.__dict__ for memory in self.all()], indent=2)

    def close(self) -> None:
        if self._db is not None:
            self._db.close()
            self._db = None
