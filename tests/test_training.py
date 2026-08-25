import unittest

from jarvis.training import ExternalTeacher, TeachingExample, TrainingEngine


class DemoTeacher(ExternalTeacher):
    def teach(self, subject: str, level: float):
        yield TeachingExample(subject, "gravity describes attraction between masses", "demo-teacher")
        yield TeachingExample(subject, "invalid lesson", "demo-teacher")


class TrainingTests(unittest.TestCase):
    def test_training_keeps_teacher_external_and_stores_learning(self):
        engine = TrainingEngine()
        result = engine.train(
            "physics",
            DemoTeacher(),
            validator=lambda example: example.lesson.startswith("gravity"),
        )
        self.assertEqual(result.score, 0.5)
        recalled = engine.memory.recall("physics")
        self.assertEqual(len(recalled), 1)
        self.assertEqual(recalled[0].source, "demo-teacher")

    def test_empty_teacher_does_not_create_fake_knowledge(self):
        class EmptyTeacher(ExternalTeacher):
            def teach(self, subject, level):
                return ()
        result = TrainingEngine().train("math", EmptyTeacher())
        self.assertEqual(result.learned, ())
        self.assertEqual(result.score, 0.0)


if __name__ == "__main__":
    unittest.main()
