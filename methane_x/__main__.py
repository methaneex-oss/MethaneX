from .brain import Brain


def main() -> None:
    brain = Brain()
    print("MethaneX JARVIS prototype online.")
    print("Type 'Jarvis status', 'Jarvis remember ...', or 'exit'.")

    while True:
        try:
            text = input("You > ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nJarvis > Shutdown requested.")
            break

        if not text:
            continue

        # Prototype wake-word gate: commands can be spoken with or without the wake word.
        if text.lower().startswith("jarvis"):
            text = text[6:].strip(" ,:—-") or "status"

        response = brain.process(text)
        print(f"Jarvis > {response}")
        if brain.perceive(text).kind == "shutdown":
            break


if __name__ == "__main__":
    main()
