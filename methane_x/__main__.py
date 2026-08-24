from .brain import Brain
from .config import Settings
from .voice import WakeWordDetector


def main() -> None:
    settings = Settings.from_env()
    brain = Brain(memory_path=settings.memory_path)
    wake = WakeWordDetector(settings.wake_words)
    print("JARVIS online.")
    print("Use 'Jarvis <command>' or 'Hey Jarvis <command>'. Type 'exit' to stop.")

    try:
        while True:
            try:
                text = input("You > ").strip()
            except (EOFError, KeyboardInterrupt):
                print("\\nJARVIS > Shutdown requested.")
                break
            if not text:
                continue
            if text.casefold() in {"exit", "quit", "shutdown"}:
                print("JARVIS > Shutdown requested.")
                break
            if not wake.matches(text):
                continue

            command = text
            lowered = command.casefold()
            matched = False
            for word in settings.wake_words:
                if lowered == word:
                    command = "status"
                    matched = True
                    break
                prefix = word + " "
                if lowered.startswith(prefix):
                    command = command[len(word):].strip(" ,:-")
                    matched = True
                    break
            if not matched:
                print("JARVIS > I heard the wake word, but I could not isolate the command.")
                continue
            print(f"JARVIS > {brain.process(command or 'status')}")
    finally:
        brain.memory.close()


if __name__ == "__main__":
    main()
