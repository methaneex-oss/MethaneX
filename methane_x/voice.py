from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


class SpeechToText(Protocol):
    def transcribe(self, audio: bytes) -> str: ...


class TextToSpeech(Protocol):
    def synthesize(self, text: str) -> bytes: ...


@dataclass(frozen=True)
class WakeWordDetector:
    words: tuple[str, ...] = ("jarvis", "hey jarvis")

    def matches(self, text: str) -> bool:
        normalized = text.casefold().strip()
        return any(normalized == word or normalized.endswith(" " + word) for word in self.words)


class ConsoleSpeech:
    """Hardware-independent development adapter; real STT/TTS providers implement the protocols."""

    def listen(self) -> str:
        return input("You: ")

    def speak(self, text: str) -> None:
        print(f"JARVIS: {text}")
