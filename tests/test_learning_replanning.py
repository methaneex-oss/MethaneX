import unittest

from jarvis.memory_consolidation import ExperienceRecord, MemoryConsolidator
from jarvis.replanning import Replanner


class LearningReplanningTests(unittest.TestCase):
    def test_repeated_experience_becomes_lesson(self):
        records = [
            ExperienceRecord("service degraded", "inspect logs", "root cause found", True, 0.9),
            ExperienceRecord("service degraded", "inspect logs", "root cause found", True, 0.8),
            ExperienceRecord("service degraded", "restart", "temporary recovery", False, 0.6),
        ]
        lessons = MemoryConsolidator().consolidate(records)
        self.assertTrue(lessons)
        self.assertIn("prefer", lessons[0].guidance)
        self.assertEqual(lessons[0].observations, 2)

    def test_failed_step_triggers_replan(self):
        decision = Replanner().decide(
            goal="restore service",
            plan_steps=["inspect", "repair", "verify"],
            failed_step="repair",
            observed_result="repair failed",
            confidence=0.2,
        )
        self.assertTrue(decision.replan)
        self.assertIn("inspect", decision.alternatives)

    def test_stable_plan_does_not_replan(self):
        decision = Replanner().decide(
            goal="observe",
            plan_steps=["inspect"],
            failed_step=None,
            observed_result="healthy",
            confidence=0.9,
        )
        self.assertFalse(decision.replan)


if __name__ == "__main__":
    unittest.main()
