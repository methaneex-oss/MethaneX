import tempfile
import unittest
from pathlib import Path

from jarvis.brain import Brain


class BrainTests(unittest.TestCase):
    def test_world_and_self_state_survives_restart(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            brain = Brain(state_path=path)
            brain.observe("server", {"status": "degraded", "region": "africa"}, 0.9)
            brain.relate("server", "owned_by", "user")
            brain.record_capability("reasoning")
            brain.record_limitation("no_sensor")
            brain.record_metric("decision_latency", 0.12)
            goal = brain.add_goal("restore service", priority=0.9)
            brain.think(
                "inspect system",
                facts=["server is degraded"],
                options=[("inspect", ["inspect system"])],
                execute=lambda action: action,
            )

            restored = Brain(state_path=path)
            self.assertEqual(restored.world.entities["server"].attributes["status"], "degraded")
            self.assertIn(("server", "owned_by", "user"), restored.world.relations)
            self.assertIn("reasoning", restored.self_model.capabilities)
            self.assertIn("no_sensor", restored.self_model.limitations)
            self.assertAlmostEqual(restored.self_model.performance["decision_latency"], 0.12)
            self.assertIn(goal.id, restored.goals.goals)
            self.assertGreaterEqual(len(restored.continuity.experiences), 1)
            self.assertGreaterEqual(restored.cycle.state.cycle_id, 1)

    def test_corrupt_state_fails_closed_without_crashing(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            path.write_text("{not valid json", encoding="utf-8")
            brain = Brain(state_path=path)
            self.assertEqual(brain.snapshot().cycles, 0)
            self.assertEqual(brain.snapshot().experiences, 0)

    def test_malformed_records_are_ignored(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            path.write_text(
                '{"cycles": 2, "experiences": [{"cycle_id": "bad"}, null], '
                '"goals": [{"objective": "valid", "priority": "bad"}, {"objective": ""}], '
                '"world": {"entities": {"node": {"confidence": "bad"}}, "relations": [["a", "b"]]}}',
                encoding="utf-8",
            )
            brain = Brain(state_path=path)
            self.assertEqual(brain.snapshot().cycles, 2)
            self.assertIn("valid", {goal.objective for goal in brain.goals.goals.values()})
            self.assertIn("node", brain.world.entities)


if __name__ == "__main__":
    unittest.main()
