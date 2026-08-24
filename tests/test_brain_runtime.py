import tempfile
import unittest
from pathlib import Path

from methane_x.brain import Brain


class BrainRuntimeTests(unittest.TestCase):
    def test_memory_and_reasoning_survive_restart(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "memory.db"
            first = Brain(memory_path=path)
            self.assertIn("Stored", first.process("remember my prototype is MethaneX"))
            first.memory.close()

            second = Brain(memory_path=path)
            response = second.process("what is my prototype")
            self.assertIn("MethaneX", response)
            second.memory.close()

    def test_actions_require_authorization(self):
        brain = Brain()
        brain.register_action("open", lambda _: "opened", capability="system.open")
        with self.assertRaises(PermissionError):
            brain.process("open something")
        brain.allow_capability("system.open")
        self.assertEqual(brain.process("open something"), "opened")


if __name__ == "__main__":
    unittest.main()
