from __future__ import annotations

import json
import os
from dataclasses import dataclass
from typing import Any
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

from .training import ExternalTeacher, TeachingExample


@dataclass(frozen=True)
class ProviderConfig:
    name: str
    base_url: str
    api_key_env: str
    model: str


class HTTPTeacher(ExternalTeacher):
    """Minimal provider adapter. Credentials stay in environment variables."""

    def __init__(self, config: ProviderConfig, timeout: float = 30.0) -> None:
        self.config = config
        self.timeout = timeout

    def teach(self, subject: str, level: float = 0.5) -> tuple[TeachingExample, ...]:
        api_key = os.getenv(self.config.api_key_env)
        if not api_key:
            raise RuntimeError(f"Missing credential: {self.config.api_key_env}")
        prompt = (
            f"Teach JARVIS general world knowledge about {subject}. "
            f"Target learning level: {max(0.0, min(1.0, level)):.2f}. "
            "Return concise factual lessons as a JSON array of strings. "
            "Do not include markdown."
        )
        payload = {"model": self.config.model, "messages": [{"role": "user", "content": prompt}]}
        body = json.dumps(payload).encode("utf-8")
        request = Request(
            self.config.base_url,
            data=body,
            headers={"Authorization": f"Bearer {api_key}", "Content-Type": "application/json"},
            method="POST",
        )
        try:
            with urlopen(request, timeout=self.timeout) as response:
                data: dict[str, Any] = json.loads(response.read().decode("utf-8"))
        except (HTTPError, URLError, TimeoutError) as exc:
            raise RuntimeError(f"{self.config.name} teacher request failed") from exc
        text = self._extract_text(data)
        try:
            lessons = json.loads(text)
        except json.JSONDecodeError as exc:
            raise RuntimeError(f"{self.config.name} returned invalid training data") from exc
        if not isinstance(lessons, list):
            raise RuntimeError(f"{self.config.name} returned a non-list lesson payload")
        return tuple(
            TeachingExample(subject=subject, lesson=item.strip(), source=self.config.name, difficulty=level)
            for item in lessons
            if isinstance(item, str) and item.strip()
        )

    @staticmethod
    def _extract_text(data: dict[str, Any]) -> str:
        choices = data.get("choices")
        if isinstance(choices, list) and choices:
            message = choices[0].get("message", {})
            content = message.get("content") if isinstance(message, dict) else None
            if isinstance(content, str):
                return content
        raise RuntimeError("Teacher response did not contain message content")


OPENROUTER = ProviderConfig("openrouter", "https://openrouter.ai/api/v1/chat/completions", "OPENROUTER_API_KEY", "openai/gpt-4o-mini")
GROQ = ProviderConfig("groq", "https://api.groq.com/openai/v1/chat/completions", "GROQ_API_KEY", "llama-3.3-70b-versatile")
GOOGLE = ProviderConfig("google", "https://generativelanguage.googleapis.com/v1beta/openai/chat/completions", "GOOGLE_API_KEY", "gemini-2.5-flash")
