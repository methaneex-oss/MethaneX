import tempfile
import unittest
from pathlib import Path

from methane_x.runtime import JarvisRuntime


class RuntimeIntegrationTests(unittest.TestCase):
    def test_runtime_persists_learning_and_reports_health(self):
        with tempfile.TemporaryDirectory() as tmp:
            runtime = JarvisRuntime()
            runtime.settings = runtime.settings.__class__(memory_path=Path(tmp) / "memory.db", wake_words=runtime.settings.wake_words, require_wake_word=runtime.settings.require_wake_word)
            runtime.memory.close()
            runtime.memory = runtime.memory.__class__(runtime.settings.memory_path)
            runtime.learning.memory = runtime.memory
            output = runtime.process("remember prototype goal")
            self.assertTrue(output)
            self.assertGreaterEqual(len(runtime.memory.all()), 1)
            self.assertTrue(all(check.ok for check in runtime.health.run()))
            runtime.close()

    def test_unauthorized_action_is_rejected(self):
        runtime = JarvisRuntime()
        with self.assertRaises(PermissionError):
            runtime.execute_verified("system.shutdown", "shutdown", lambda _: "done", lambda _: True)
        runtime.close()


if __name__ == "__main__":
    unittest.main()
