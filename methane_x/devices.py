from __future__ import annotations

from dataclasses import dataclass, field


@dataclass
class Device:
    id: str
    kind: str
    capabilities: set[str] = field(default_factory=set)
    online: bool = True


class DeviceRegistry:
    def __init__(self) -> None:
        self._devices: dict[str, Device] = {}

    def register(self, device: Device) -> None:
        self._devices[device.id] = device

    def set_online(self, device_id: str, online: bool) -> None:
        self._devices[device_id].online = online

    def available(self, capability: str) -> tuple[Device, ...]:
        return tuple(d for d in self._devices.values() if d.online and capability in d.capabilities)

    def all(self) -> tuple[Device, ...]:
        return tuple(self._devices.values())
