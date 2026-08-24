from __future__ import annotations

from dataclasses import dataclass
from typing import Protocol


class SpeechToText(Protocol):
    def listen(self) -> str: ...


class TextToSpeech(Protocol):
    def speak(self, text: str) -> None: ...


class StreamingSTT(Protocol):
    def transcribe(self, audio: bytes) -> str: ...


class StreamingTTS(Protocol):
    def synthesize(self, text: str) -> bytes: ...


@dataclass
class SpeechSession:
    stt: StreamingSTT | None = None
    tts: StreamingTTS | None = None
    active: bool = False

    def start(self) -> None:
        self.active = True

    def stop(self) -> None:
        self.active = False

    def transcribe(self, audio: bytes) -> str:
        if not self.stt:
            raise RuntimeError("No STT provider configured")
        return self.stt.transcribe(audio)

    def speak(self, text: str) -> bytes:
        if not self.tts:
            raise RuntimeError("No TTS provider configured")
        return self.tts.synthesize(text)


class ConsoleSpeech:
    """Hardware-independent speech adapter for the first testable build."""
    def listen(self) -> str:
        return input("You 🎙️ > ").strip()

    def speak(self, text: str) -> None:
        print(f"Jarvis 🔊 > {text}")


class OptionalSpeechInfo:
    STT_OPTIONS = ("faster-whisper", "vosk")
    TTS_OPTIONS = ("piper", "pyttsx3")
