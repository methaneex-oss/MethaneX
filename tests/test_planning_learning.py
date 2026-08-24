import unittest

from methane_x.learning import Experience, LearningEngine
from methane_x.memory import MemoryStore
from methane_x.planning import Planner, TaskState


class PlanningLearningTests(unittest.TestCase):
    def test_planner_creates_executable_task(self):
        plan = Planner().create("check the system")
        task = Planner().next(plan)
        self.assertIsNotNone(task)
        assert task is not None
        self.assertEqual(task.state, TaskState.PENDING)

    def test_learning_can_store_validated_experience(self):
        memory = MemoryStore()
        engine = LearningEngine(memory)
        lesson = engine.learn(Experience("test goal", "test action", "success", True))
        self.assertIsNotNone(lesson)
        self.assertEqual(len(tuple(memory.all())), 1)


if __name__ == "__main__":
    unittest.main()
