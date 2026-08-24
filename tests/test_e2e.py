import tempfile
import unittest
from pathlib import Path

from methane_x.brain import Brain
from methane_x.memory import MemoryStore
from methane_x.verification import VerifiedExecutor


class EndToEndTests(unittest.TestCase):
    def test_memory_reasoning_action_verification_cycle(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "jarvis.db"
            brain = Brain(memory_path=path)

            self.assertIn("Stored", brain.process("remember my project is JARVIS"))
            response = brain.process("what is my project")
            self.assertIn("JARVIS", response)

            brain.register_action("ping", lambda _: "pong", capability="system.ping")
            with self.assertRaises(PermissionError):
                brain.process("ping")
            brain.allow_capability("system.ping")
            self.assertEqual(brain.process("ping"), "pong")

            verified = VerifiedExecutor(lambda _: "pong", lambda output: output == "pong")
            result = verified.run("ping")
            self.assertTrue(result.ok)
            self.assertEqual(result.attempts, 1)
            brain.memory.close()

    def test_memory_store_rejects_empty_and_closes_idempotently(self):
        store = MemoryStore()
        with self.assertRaises(ValueError):
            store.remember("   ")
        store.close()
        store.close()


if __name__ == "__main__":
    unittest.main()
