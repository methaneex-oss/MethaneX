import tempfile
import unittest
from pathlib import Path

from jarvis.training import ExternalTeacher, TeachingExample, TrainingEngine, TrainingMemory


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

    def test_validated_learning_survives_restart(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "training.json"
            engine = TrainingEngine(TrainingMemory(path))
            engine.train(
                "physics",
                DemoTeacher(),
                validator=lambda example: example.lesson.startswith("gravity"),
            )

            restored = TrainingMemory(path)
            lessons = restored.recall("physics")
            self.assertEqual(len(lessons), 1)
            self.assertEqual(lessons[0].lesson, "gravity describes attraction between masses")
            self.assertEqual(lessons[0].source, "demo-teacher")

    def test_corrupt_training_state_is_ignored(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "training.json"
            path.write_text('{"lessons": {"physics": ["bad-entry", {"lesson": 4}]}}', encoding="utf-8")
            memory = TrainingMemory(path)
            self.assertEqual(memory.recall("physics"), ())


if __name__ == "__main__":
    unittest.main()
