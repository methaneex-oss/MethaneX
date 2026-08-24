import unittest

from methane_x.goals import GoalManager, GoalState


class GoalTests(unittest.TestCase):
    def test_priority_selects_active_goal(self):
        manager = GoalManager()
        low = manager.propose("low", priority=0.2)
        high = manager.propose("high", priority=0.9)
        manager.activate(low.id)
        manager.activate(high.id)
        self.assertEqual(manager.choose_next().id, high.id)

    def test_goal_lifecycle(self):
        manager = GoalManager()
        goal = manager.propose("learn", rationale="improve future decisions")
        self.assertEqual(goal.state, GoalState.PROPOSED)
        manager.activate(goal.id)
        manager.complete(goal.id)
        self.assertEqual(goal.state, GoalState.COMPLETED)


if __name__ == "__main__":
    unittest.main()
