from __future__ import annotations

from dataclasses import dataclass
from typing import Callable


@dataclass(frozen=True)
class Tool:
    name: str
    description: str
    capability: str
    handler: Callable[[str], str]


class ToolRegistry:
    def __init__(self) -> None:
        self._tools: dict[str, Tool] = {}

    def register(self, tool: Tool) -> None:
        self._tools[tool.name] = tool

    def find(self, query: str) -> tuple[Tool, ...]:
        terms = set(query.casefold().split())
        ranked = []
        for tool in self._tools.values():
            score = len(terms & set((tool.name + " " + tool.description).casefold().split()))
            if score:
                ranked.append((score, tool))
        return tuple(tool for _, tool in sorted(ranked, key=lambda item: item[0], reverse=True))

    def all(self) -> tuple[Tool, ...]:
        return tuple(self._tools.values())
