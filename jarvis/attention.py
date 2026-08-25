from __future__ import annotations

from dataclasses import dataclass
from typing import Iterable


@dataclass(frozen=True)
class Focus:
    item: str
    relevance: float
    urgency: float
    uncertainty: float

    @property
    def score(self) -> float:
        return max(0.0, min(1.0, 0.5 * self.relevance + 0.3 * self.urgency + 0.2 * self.uncertainty))


class AttentionController:
    """Ranks competing cognitive inputs instead of processing everything equally."""

    def select(self, items: Iterable[Focus], budget: int = 5) -> tuple[Focus, ...]:
        if budget < 1:
            return ()
        return tuple(sorted(items, key=lambda item: item.score, reverse=True)[:budget])
