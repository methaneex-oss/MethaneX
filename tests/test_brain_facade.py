import unittest

from jarvis.brain import Brain
from jarvis.attention import Focus


class BrainFacadeTests(unittest.TestCase):
    def test_brain_connects_cognitive_subsystems(self):
        brain = Brain()
        result = brain.think(
            "inspect system",
            observations=[Focus("system health", 0.9, 0.8, 0.4)],
            facts=["system is unknown"],
            options=[("inspect", ["inspect system"])],
            execute=lambda action: action,
        )
        snapshot = brain.snapshot()
        self.assertEqual(snapshot.identity, "JARVIS")
        self.assertEqual(snapshot.cycles, 1)
        self.assertEqual(result.action_output, "inspect system")


if __name__ == "__main__":
    unittest.main()
