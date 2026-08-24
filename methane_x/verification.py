from __future__ import annotations

from dataclasses import dataclass
from typing import Callable


@dataclass(frozen=True)
class VerificationResult:
    ok: bool
    detail: str
    attempts: int


class VerifiedExecutor:
    """Executes an action and verifies its outcome without unbounded retries."""

    def __init__(self, execute: Callable[[str], str], verify: Callable[[str], bool], max_attempts: int = 2) -> None:
        if max_attempts < 1:
            raise ValueError("max_attempts must be >= 1")
        self.execute = execute
        self.verify = verify
        self.max_attempts = max_attempts

    def run(self, action: str) -> VerificationResult:
        last_output = ""
        for attempt in range(1, self.max_attempts + 1):
            last_output = self.execute(action)
            if self.verify(last_output):
                return VerificationResult(True, last_output, attempt)
        return VerificationResult(False, last_output, self.max_attempts)
