import os
import unittest
from pathlib import Path
from unittest.mock import patch

from methane_x.config import Settings


class ConfigTests(unittest.TestCase):
    def test_defaults_are_safe(self):
        settings = Settings.from_env()
        self.assertIn("jarvis", settings.wake_words)
        self.assertTrue(str(settings.memory_path).endswith(".methane_x/memory.db"))

    def test_environment_overrides(self):
        with patch.dict(os.environ, {"METHANEX_MEMORY_PATH": "~/test-memory.db", "METHANEX_WAKE_WORDS": "computer,jarvis"}, clear=False):
            settings = Settings.from_env()
        self.assertEqual(settings.memory_path, Path("~/test-memory.db").expanduser())
        self.assertEqual(settings.wake_words, ("computer", "jarvis"))


if __name__ == "__main__":
    unittest.main()
