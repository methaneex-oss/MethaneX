import tempfile
import unittest
from pathlib import Path

from jarvis.brain import Brain


class BrainPersistenceTests(unittest.TestCase):
    def test_cycles_and_identity_survive_restart(self):
        with tempfile.TemporaryDirectory() as directory:
            state = Path(directory) / "jarvis-state.json"
            first = Brain(state_path=state)
            first.self_model.register_capability("reasoning")
            first.think(
                "inspect system",
                options=[("inspect", ["inspect system"])],
                execute=lambda action: action,
            )
            snapshot = first.snapshot()
            self.assertEqual(snapshot.cycles, 1)

            second = Brain(state_path=state)
            restored = second.snapshot()
            self.assertEqual(restored.identity, "JARVIS")
            self.assertEqual(restored.cycles, 1)
            self.assertIn("reasoning", second.self_model.capabilities)


if __name__ == "__main__":
    unittest.main()
