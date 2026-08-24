from pathlib import Path

from .brain import Brain
from .config import Settings
from .voice import WakeWordDetector


def main() -> None:
    settings = Settings.from_env()
    brain = Brain(memory_path=settings.memory_path)
    wake = WakeWordDetector(settings.wake_words)
    print("MethaneX JARVIS prototype online.")
    print("Say/type 'Hey Jarvis' or 'Jarvis' before a command. Type 'exit' to stop.")

    try:
        while True:
            try:
                text = input("You > ").strip()
            except (EOFError, KeyboardInterrupt):
                print("\nJarvis > Shutdown requested.")
                break
            if not text:
                continue
            if text.casefold() in {"exit", "quit", "shutdown"}:
                print("Jarvis > Shutdown requested.")
                break
            if not wake.matches(text):
                continue
            command = text
            matched = False
            for word in settings.wake_words:
                if command.casefold() == word:
                    command = "status"
                    matched = True
                    break
                prefix = word + " "
                if command.casefold().startswith(prefix):
                    command = command[len(word):].strip(" ,:—-")
                    matched = True
                    break
            if not matched or not command:
                print("Jarvis > Yes?")
                continue
            response = brain.process(command)
            print(f"Jarvis > {response}")
    finally:
        brain.memory.close()


if __name__ == "__main__":
    main()
