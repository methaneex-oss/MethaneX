from __future__ import annotations

from .brain import Brain


def main() -> None:
    brain = Brain()
    print("JARVIS cognitive core online. Type 'exit' to stop.")
    while True:
        command = input("You: ").strip()
        if command.casefold() in {"exit", "quit", "shutdown"}:
            print("JARVIS: Shutdown requested.")
            return
        if not command:
            continue
        result = brain.think(
            command,
            options=[("understand", ["analyze objective", "select strategy"])],
        )
        strategy = result.decision.strategy
        print(f"JARVIS: {strategy.name if strategy else 'I need more information.'}")


if __name__ == "__main__":
    main()
