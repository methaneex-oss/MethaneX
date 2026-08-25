import unittest

from jarvis.brain import Brain


class BrainSurfaceTests(unittest.TestCase):
    def test_brain_exposes_core_cognitive_subsystems(self):
        brain = Brain()
        for name in ("world", "self_model", "continuity", "attention", "conflicts", "adaptations", "goals", "intelligence", "recovery", "simulator", "consolidator", "cycle"):
            self.assertTrue(hasattr(brain, name), name)

    def test_goal_persists_through_state_journal(self):
        import tempfile
        from pathlib import Path
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            first = Brain(state_path=path)
            goal = first.add_goal("maintain system", priority=0.9)
            second = Brain(state_path=path)
            chosen = second.choose_goal()
            self.assertIsNotNone(chosen)
            self.assertEqual(chosen.objective, goal.objective)


if __name__ == "__main__":
    unittest.main()
