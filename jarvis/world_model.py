from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime, timezone


@dataclass
class EntityState:
    name: str
    attributes: dict[str, object] = field(default_factory=dict)
    confidence: float = 0.5
    observed_at: str = field(default_factory=lambda: datetime.now(timezone.utc).isoformat())

    def observe(self, attributes: dict[str, object], confidence: float) -> None:
        self.attributes.update(attributes)
        self.confidence = max(0.0, min(1.0, confidence))
        self.observed_at = datetime.now(timezone.utc).isoformat()


@dataclass
class WorldModel:
    entities: dict[str, EntityState] = field(default_factory=dict)
    relations: set[tuple[str, str, str]] = field(default_factory=set)

    def observe(self, name: str, attributes: dict[str, object], confidence: float = 0.5) -> EntityState:
        entity = self.entities.setdefault(name, EntityState(name))
        entity.observe(attributes, confidence)
        return entity

    def relate(self, subject: str, relation: str, object_: str) -> None:
        self.relations.add((subject, relation, object_))


@dataclass
class SelfModel:
    identity: str = "JARVIS"
    capabilities: set[str] = field(default_factory=set)
    limitations: set[str] = field(default_factory=set)
    active_processes: set[str] = field(default_factory=set)
    performance: dict[str, float] = field(default_factory=dict)

    def register_capability(self, capability: str) -> None:
        self.capabilities.add(capability)

    def register_limitation(self, limitation: str) -> None:
        self.limitations.add(limitation)

    def record_metric(self, name: str, value: float) -> None:
        self.performance[name] = value
