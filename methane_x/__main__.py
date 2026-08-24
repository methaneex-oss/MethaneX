from pathlib import Path

from .brain import Brain
from .voice import WakeWordDetector


def main() -> None:
    data_dir = Path.home() / ".methane_x"
    brain = Brain(memory_path=data_dir / "memory.db")
    wake = WakeWordDetector()
    print("MethaneX JARVIS prototype online.")
    print("Say/type 'Hey Jarvis' or 'Jarvis' before a command. Type 'exit' to stop.")

    while True:
        try:
            text = input("You > ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nJarvis > Shutdown requested.")
            break

        if not text:
            continue

        normalized = text.strip()
        if wake.matches(normalized):
            normalized = "status"
        elif normalized.casefold().startswith("jarvis "):
            normalized = normalized[7:].strip()

        response = brain.process(normalized)
        print(f"Jarvis > {response}")
        if brain.perceive(normalized).kind == "shutdown":
            brain.memory.close()
            break


if __name__ == "__main__":
    main()
