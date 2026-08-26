import unittest

from jarvis.autonomy import AutonomousController


class AutonomousControllerTests(unittest.TestCase):
    def test_autonomy_runs_and_stops_when_decision_is_complete(self):
        controller = AutonomousController()
        result = controller.run(
            "inspect system",
            options=[("inspect", ["inspect system"])],
            execute=lambda action: action,
        )
        self.assertEqual(len(result.cycles), 1)
        self.assertEqual(result.stop_reason, "decision_complete")
        self.assertFalse(controller.state.active)
        self.assertEqual(controller.state.steps, 1)

    def test_autonomy_can_continue_based_on_observation(self):
        controller = AutonomousController()
        result = controller.run(
            "inspect system",
            options=[("inspect", ["inspect system"])],
            continue_if=lambda _: True,
            max_cycles=2,
        )
        self.assertEqual(len(result.cycles), 2)
        self.assertEqual(result.stop_reason, "cycle_limit")
        self.assertEqual(controller.state.steps, 2)

    def test_invalid_goal_and_cycle_limit_are_rejected(self):
        controller = AutonomousController()
        with self.assertRaises(ValueError):
            controller.run("   ")
        with self.assertRaises(ValueError):
            controller.run("test", max_cycles=0)


if __name__ == "__main__":
    unittest.main()
