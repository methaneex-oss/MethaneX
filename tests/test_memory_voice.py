import tempfile
import unittest
from pathlib import Path

from methane_x.memory import MemoryStore
from methane_x.voice import WakeWordDetector


class MemoryVoiceTests(unittest.TestCase):
    def test_memory_persists_across_store_instances(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "memory.db"
            first = MemoryStore(path)
            first.remember("prototype identity", tier=1, source="system")
            first.close()
            second = MemoryStore(path)
            self.assertEqual(second.all()[0].content, "prototype identity")
            self.assertEqual(second.all()[0].tier, 1)
            second.close()

    def test_wake_word(self):
        detector = WakeWordDetector()
        self.assertTrue(detector.matches("Hey Jarvis"))
        self.assertTrue(detector.matches("please wake up Jarvis"))
        self.assertFalse(detector.matches("hello assistant"))


if __name__ == "__main__":
    unittest.main()
