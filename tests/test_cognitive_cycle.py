import unittest

from jarvis.cognitive_cycle import CognitiveCycle


class CognitiveCycleTests(unittest.TestCase):
    def test_cycle_runs_decision_action_and_reflection(self):
        cycle = CognitiveCycle()
        result = cycle.run(
            "inspect system",
            facts=["system is unknown"],
            options=[("inspect", ["inspect system"])],
            execute=lambda action: action,
        )
        self.assertIsNotNone(result.decision.strategy)
        self.assertEqual(result.action_output, "inspect system")
        self.assertEqual(cycle.state.phase, "idle")
        self.assertTrue(result.reflection.what_worked)

    def test_cycle_is_bounded_to_one_decision_action_reflection_pass(self):
        cycle = CognitiveCycle()
        result = cycle.run("test", options=[("observe", ["observe"])])
        self.assertEqual(cycle.state.cycle_id, 1)
        self.assertEqual(len(cycle.state.history), 2)
        self.assertIsNotNone(result.reflection)


if __name__ == "__main__":
    unittest.main()
