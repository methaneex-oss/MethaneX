from __future__ import annotations

from concurrent.futures import Future, ThreadPoolExecutor
from dataclasses import dataclass
from typing import Callable, Iterable


@dataclass(frozen=True)
class TaskResult:
    index: int
    value: object | None
    error: str | None


class TaskScheduler:
    """Small concurrency boundary for independent JARVIS background tasks."""

    def __init__(self, workers: int = 4) -> None:
        if workers < 1:
            raise ValueError("workers must be >= 1")
        self.executor = ThreadPoolExecutor(max_workers=workers, thread_name_prefix="methane-x")

    def submit_many(self, fn: Callable[[object], object], items: Iterable[object]) -> list[TaskResult]:
        futures: list[tuple[int, Future[object]]] = [
            (index, self.executor.submit(fn, item)) for index, item in enumerate(items)
        ]
        results: list[TaskResult] = []
        for index, future in futures:
            try:
                results.append(TaskResult(index, future.result(), None))
            except Exception as exc:
                results.append(TaskResult(index, None, str(exc)))
        return results

    def shutdown(self) -> None:
        self.executor.shutdown(wait=True)
