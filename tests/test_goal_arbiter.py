import unittest

from jarvis.goals import GoalArbiter


class GoalArbiterTests(unittest.TestCase):
    def test_choose_highest_weighted_goal(self):
        arbiter = GoalArbiter()
        arbiter.add("routine", priority=0.3, urgency=0.2)
        urgent = arbiter.add("critical issue", priority=0.7, urgency=1.0)
        self.assertEqual(arbiter.choose().id, urgent.id)

    def test_suspended_goal_is_not_selected(self):
        arbiter = GoalArbiter()
        goal = arbiter.add("paused")
        arbiter.suspend(goal.id)
        self.assertIsNone(arbiter.choose())


if __name__ == "__main__":
    unittest.main()
