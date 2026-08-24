from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Settings:
    memory_path: Path = Path.home() / ".jarvis" / "memory.db"
    wake_words: tuple[str, ...] = ("jarvis", "hey jarvis")
    require_wake_word: bool = True
    log_level: str = "INFO"

    @classmethod
    def from_env(cls) -> "Settings":
        memory = os.getenv("JARVIS_MEMORY_PATH") or os.getenv("METHANEX_MEMORY_PATH")
        words = os.getenv("JARVIS_WAKE_WORDS") or os.getenv("METHANEX_WAKE_WORDS")
        require = os.getenv("JARVIS_REQUIRE_WAKE_WORD") or os.getenv("METHANEX_REQUIRE_WAKE_WORD")
        return cls(
            memory_path=Path(memory).expanduser() if memory else cls.memory_path,
            wake_words=tuple(w.strip().casefold() for w in words.split(",") if w.strip()) if words else cls.wake_words,
            require_wake_word=False if require == "0" else True,
            log_level=os.getenv("JARVIS_LOG_LEVEL", os.getenv("METHANEX_LOG_LEVEL", cls.log_level)).upper(),
        )
