from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
from typing import Callable


@dataclass(frozen=True)
class HealthCheck:
    name: str
    ok: bool
    detail: str


class HealthMonitor:
    def __init__(self) -> None:
        self._checks: dict[str, Callable[[], str]] = {}

    def register(self, name: str, check: Callable[[], str]) -> None:
        self._checks[name] = check

    def run(self) -> tuple[HealthCheck, ...]:
        results: list[HealthCheck] = []
        for name, check in self._checks.items():
            try:
                results.append(HealthCheck(name, True, check()))
            except Exception as exc:
                results.append(HealthCheck(name, False, str(exc)))
        return tuple(results)

    def snapshot(self) -> dict[str, object]:
        checks = self.run()
        return {
            "timestamp": datetime.now(timezone.utc).isoformat(),
            "healthy": all(check.ok for check in checks),
            "checks": [check.__dict__ for check in checks],
        }
