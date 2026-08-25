from __future__ import annotations

from dataclasses import dataclass
from .cognition import Belief


@dataclass(frozen=True)
class Conflict:
    statements: tuple[str, ...]
    reason: str


class ConflictResolver:
    """Keeps contradictory observations explicit instead of silently overwriting knowledge."""

    def detect(self, beliefs: list[Belief]) -> tuple[Conflict, ...]:
        conflicts: list[Conflict] = []
        for index, left in enumerate(beliefs):
            for right in beliefs[index + 1:]:
                if self._contradict(left.statement, right.statement):
                    conflicts.append(Conflict((left.statement, right.statement), "statements appear mutually exclusive"))
        return tuple(conflicts)

    @staticmethod
    def _contradict(left: str, right: str) -> bool:
        a, b = left.casefold().strip(), right.casefold().strip()
        if a.startswith("not ") and a[4:] == b:
            return True
        if b.startswith("not ") and b[4:] == a:
            return True
        return False

    def choose(self, beliefs: list[Belief]) -> Belief | None:
        return max(beliefs, key=lambda belief: belief.confidence, default=None)
