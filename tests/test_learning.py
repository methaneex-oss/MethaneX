import unittest

from jarvis.learning import Curriculum, LearningLoop, TrainingQuestion
from jarvis.training import ExternalTeacher, TeachingExample


class PhysicsTeacher(ExternalTeacher):
    def teach(self, subject: str, level: float):
        return (
            TeachingExample(subject, "Force is mass times acceleration.", "physics-teacher"),
            TeachingExample(subject, "Energy is the capacity to do work.", "physics-teacher"),
        )


class LearningLoopTests(unittest.TestCase):
    def test_study_and_assess(self):
        loop = LearningLoop()
        lessons = loop.study(Curriculum("physics", levels=[0.25, 0.5]), PhysicsTeacher())
        self.assertEqual(len(lessons), 4)
        result = loop.assess(
            "physics",
            [
                TrainingQuestion("What relates force?", ("force", "mass", "acceleration")),
                TrainingQuestion("What is energy?", ("energy", "capacity")),
                TrainingQuestion("What is entropy?", ("entropy",)),
            ],
        )
        self.assertEqual(result.questions_answered, 2)
        self.assertAlmostEqual(result.score, 2 / 3)
        self.assertIn("entropy", result.weaknesses)

    def test_empty_assessment_is_safe(self):
        result = LearningLoop().assess("unknown", [])
        self.assertEqual(result.score, 0.0)
        self.assertEqual(result.questions_answered, 0)


if __name__ == "__main__":
    unittest.main()
