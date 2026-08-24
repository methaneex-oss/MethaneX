from __future__ import annotations

from typing import Protocol

class SpeechToText(Protocol):
    def listen(self) -> str: ...

class TextToSpeech(Protocol):
    def speak(self, text: str) -> None: ...

class ConsoleSpeech:
    """Hardware-independent speech adapter for the first testable build."""
    def listen(self) -> str:
        return input("You 🎙️ > ").strip()
    def speak(self, text: str) -> None:
        print(f"Jarvis 🔊 > {text}")

class OptionalSpeechInfo:
    """Documents optional real STT/TTS dependencies without forcing them into core."""
    STT_OPTIONS = ("faster-whisper", "vosk")
    TTS_OPTIONS = ("piper", "pyttsx3")
