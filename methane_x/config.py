from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Settings:
    memory_path: Path = Path.home() / ".methane_x" / "memory.db"
    wake_words: tuple[str, ...] = ("jarvis", "hey jarvis")
    log_level: str = "INFO"

    @classmethod
    def from_env(cls) -> "Settings":
        memory = os.getenv("METHANEX_MEMORY_PATH")
        words = os.getenv("METHANEX_WAKE_WORDS")
        return cls(
            memory_path=Path(memory).expanduser() if memory else cls.memory_path,
            wake_words=tuple(w.strip().casefold() for w in words.split(",") if w.strip()) if words else cls.wake_words,
            log_level=os.getenv("METHANEX_LOG_LEVEL", cls.log_level).upper(),
        )
