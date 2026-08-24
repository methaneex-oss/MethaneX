from __future__ import annotations

import os
import urllib.error
import urllib.request
import json
from dataclasses import dataclass

from .intelligence import IntelligenceRequest, IntelligenceResponse


@dataclass
class HTTPJSONProvider:
    """Generic provider boundary. The brain depends only on IntelligenceProvider."""
    name: str
    endpoint_env: str
    api_key_env: str | None = None

    def generate(self, request: IntelligenceRequest) -> IntelligenceResponse:
        endpoint = os.getenv(self.endpoint_env)
        if not endpoint:
            raise RuntimeError(f"Provider endpoint is not configured: {self.endpoint_env}")
        payload = json.dumps({"prompt": request.prompt, "context": list(request.context)}).encode()
        headers = {"Content-Type": "application/json"}
        if self.api_key_env and os.getenv(self.api_key_env):
            headers["Authorization"] = f"Bearer {os.environ[self.api_key_env]}"
        req = urllib.request.Request(endpoint, data=payload, headers=headers, method="POST")
        try:
            with urllib.request.urlopen(req, timeout=30) as response:
                data = json.loads(response.read().decode())
        except (urllib.error.URLError, TimeoutError, json.JSONDecodeError) as exc:
            raise RuntimeError(f"Provider request failed: {exc}") from exc
        text = str(data.get("text", ""))
        confidence = float(data.get("confidence", 0.5))
        return IntelligenceResponse(text=text, provider=self.name, confidence=max(0.0, min(1.0, confidence)))
