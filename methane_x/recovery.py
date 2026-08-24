from __future__ import annotations

from dataclasses import dataclass
from typing import Callable


@dataclass(frozen=True)
class RecoveryResult:
    recovered: bool
    attempts: int
    detail: str


class RecoveryController:
    """Runs explicit recovery procedures with a bounded attempt budget."""

    def __init__(self, max_attempts: int = 2) -> None:
        if max_attempts < 1:
            raise ValueError("max_attempts must be >= 1")
        self.max_attempts = max_attempts

    def recover(self, probe: Callable[[], bool], repair: Callable[[], str]) -> RecoveryResult:
        for attempt in range(1, self.max_attempts + 1):
            if probe():
                return RecoveryResult(True, attempt, "subsystem healthy")
            detail = repair()
            if probe():
                return RecoveryResult(True, attempt, detail)
        return RecoveryResult(False, self.max_attempts, "recovery budget exhausted")
