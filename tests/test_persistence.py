import tempfile
import unittest
from pathlib import Path

from jarvis.persistence import StateJournal


class PersistenceTests(unittest.TestCase):
    def test_round_trip(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            journal = StateJournal(path)
            journal.save({"identity": "JARVIS", "cycles": 3})
            self.assertEqual(journal.load()["cycles"], 3)

    def test_corrupt_state_fails_safe(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "state.json"
            path.write_text("not-json", encoding="utf-8")
            self.assertEqual(StateJournal(path).load(), {})


if __name__ == "__main__":
    unittest.main()
