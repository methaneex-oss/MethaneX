import tempfile
import unittest
from pathlib import Path
from methane_x.jarvis import Jarvis
from methane_x.persistent_memory import PersistentMemory

class JarvisRuntimeTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.memory = PersistentMemory(Path(self.tmp.name) / "memory.db")
        self.jarvis = Jarvis(memory=self.memory)

    def tearDown(self):
        self.memory.close()
        self.tmp.cleanup()

    def test_status(self):
        result = self.jarvis.process("status")
        self.assertIn("Online", result)
        self.assertIn("Memory: 0", result)

    def test_memory_survives_restart(self):
        self.jarvis.process("remember the prototype is called MethaneX")
        self.memory.close()
        restored = PersistentMemory(Path(self.tmp.name) / "memory.db")
        self.assertEqual(restored.count(), 1)
        self.assertTrue(restored.search("MethaneX"))
        restored.close()

    def test_shutdown(self):
        self.assertIn("Shutdown", self.jarvis.process("shutdown"))
        self.assertFalse(self.jarvis.running)

    def test_tool_loop(self):
        self.jarvis.register_tool("ping", lambda _: "pong")
        self.assertEqual(self.jarvis.process("ping"), "pong")

if __name__ == "__main__":
    unittest.main()
