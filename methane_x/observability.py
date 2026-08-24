from __future__ import annotations

import json
from dataclasses import asdict, dataclass, field
from datetime import datetime, timezone


@dataclass(frozen=True)
class Event:
    name: str
    data: dict[str, object] = field(default_factory=dict)
    timestamp: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())


class EventLog:
    def __init__(self) -> None:
        self._events: list[Event] = []

    def emit(self, name: str, **data: object) -> Event:
        event = Event(name, data)
        self._events.append(event)
        return event

    def all(self) -> tuple[Event, ...]:
        return tuple(self._events)

    def export_json(self) -> str:
        return json.dumps([asdict(event) for event in self._events], indent=2)
