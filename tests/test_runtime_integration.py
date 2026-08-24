import tempfile
import unittest
from pathlib import Path

from methane_x.config import Settings
from methane_x.runtime import JarvisRuntime


class RuntimeIntegrationTests(unittest.TestCase):
    def test_runtime_persists_learning_and_reports_health(self):
        with tempfile.TemporaryDirectory() as tmp:
            settings = Settings(memory_path=Path(tmp) / "memory.db")
            runtime = JarvisRuntime(settings)
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
