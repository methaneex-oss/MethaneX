from __future__ import annotations

import json
import os
from unittest.mock import patch

from jarvis.teachers import GROQ, GOOGLE, OPENROUTER, HTTPTeacher


def test_teacher_uses_environment_credential_and_parses_lessons() -> None:
    teacher = HTTPTeacher(OPENROUTER)
    payload = {"choices": [{"message": {"content": json.dumps(["Earth orbits the Sun.", "The Moon orbits Earth."])}}]}
    with patch.dict(os.environ, {"OPENROUTER_API_KEY": "test-key"}), patch("jarvis.teachers.urlopen") as mocked:
        response = mocked.return_value.__enter__.return_value
        response.read.return_value = json.dumps(payload).encode()
        lessons = teacher.teach("astronomy")
    assert len(lessons) == 2
    assert lessons[0].source == "openrouter"
    request = mocked.call_args.args[0]
    assert request.headers["Authorization"] == "Bearer test-key"


def test_all_supported_provider_configs_have_credentials_and_endpoints() -> None:
    assert OPENROUTER.api_key_env == "OPENROUTER_API_KEY"
    assert GROQ.api_key_env == "GROQ_API_KEY"
    assert GOOGLE.api_key_env == "GOOGLE_API_KEY"
    assert all(config.base_url.startswith("https://") for config in (OPENROUTER, GROQ, GOOGLE))


def test_missing_credential_fails_without_network_call() -> None:
    teacher = HTTPTeacher(GROQ)
    with patch.dict(os.environ, {}, clear=True), patch("jarvis.teachers.urlopen") as mocked:
        try:
            teacher.teach("physics")
        except RuntimeError as exc:
            assert "GROQ_API_KEY" in str(exc)
        else:
            raise AssertionError("Missing credential should fail")
        mocked.assert_not_called()
