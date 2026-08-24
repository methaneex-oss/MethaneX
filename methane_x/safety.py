from __future__ import annotations

from dataclasses import dataclass, field


@dataclass
class CapabilityPolicy:
    """Explicit allow-list boundary for actions; denied by default."""

    allowed: set[str] = field(default_factory=set)

    def allow(self, capability: str) -> None:
        self.allowed.add(capability)

    def deny(self, capability: str) -> None:
        self.allowed.discard(capability)

    def check(self, capability: str) -> None:
        if capability not in self.allowed:
            raise PermissionError(f"Capability not authorized: {capability}")


@dataclass(frozen=True)
class ActionRequest:
    capability: str
    description: str


class ActionGuard:
    def __init__(self, policy: CapabilityPolicy) -> None:
        self.policy = policy

    def authorize(self, request: ActionRequest) -> None:
        self.policy.check(request.capability)
