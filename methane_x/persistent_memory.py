from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path
import sqlite3

@dataclass(frozen=True)
class Memory:
    content: str
    tier: int
    confidence: float
    source: str
    created_at: str
    memory_id: int

class PersistentMemory:
    """SQLite-backed Tier 1/2/3 memory for durable JARVIS state."""
    def __init__(self, path: str | Path = "data/methanex_memory.db"):
        self.path = Path(path)
        self.path.parent.mkdir(parents=True, exist_ok=True)
        self.db = sqlite3.connect(self.path)
        self.db.execute("CREATE TABLE IF NOT EXISTS memories (id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT NOT NULL, tier INTEGER NOT NULL, confidence REAL NOT NULL, source TEXT NOT NULL, created_at TEXT NOT NULL)")
        self.db.commit()

    def remember(self, content: str, tier: int = 3, confidence: float = 1.0, source: str = "user") -> Memory:
        if tier not in (1, 2, 3): raise ValueError("tier must be 1, 2 or 3")
        if tier == 1 and source != "system": raise PermissionError("Tier 1 is immutable system identity")
        content = content.strip()
        if not content: raise ValueError("memory cannot be empty")
        confidence = min(1.0, max(0.0, confidence))
        now = datetime.now(timezone.utc).isoformat()
        cur = self.db.execute("INSERT INTO memories(content,tier,confidence,source,created_at) VALUES(?,?,?,?,?)", (content,tier,confidence,source,now))
        self.db.commit()
        return Memory(content,tier,confidence,source,now,cur.lastrowid)

    def search(self, query: str, limit: int = 5) -> list[Memory]:
        terms = {x.lower().strip(".,!?;:") for x in query.split() if len(x) > 1}
        rows = self.db.execute("SELECT id,content,tier,confidence,source,created_at FROM memories").fetchall()
        scored = []
        for row in rows:
            words = {x.lower().strip(".,!?;:") for x in row[1].split()}
            overlap = len(terms & words)
            if overlap:
                score = overlap * row[3] * {1:1.5,2:1.25,3:1.0}.get(row[2],1.0)
                scored.append((score, row))
        scored.sort(key=lambda x:x[0], reverse=True)
        return [Memory(r[1],r[2],r[3],r[4],r[5],r[0]) for _,r in scored[:limit]]

    def count(self) -> int:
        return int(self.db.execute("SELECT COUNT(*) FROM memories").fetchone()[0])

    def close(self) -> None:
        self.db.close()
