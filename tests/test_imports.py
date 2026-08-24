import importlib
import unittest


MODULES = (
    "methane_x.async_tasks",
    "methane_x.brain",
    "methane_x.cognitive_loop",
    "methane_x.config",
    "methane_x.decision",
    "methane_x.devices",
    "methane_x.evaluation",
    "methane_x.goals",
    "methane_x.health",
    "methane_x.intelligence",
    "methane_x.jarvis",
    "methane_x.learning",
    "methane_x.memory",
    "methane_x.memory_consolidation",
    "methane_x.observability",
    "methane_x.perception",
    "methane_x.persistent_memory",
    "methane_x.planning",
    "methane_x.providers",
    "methane_x.recovery",
    "methane_x.runtime",
    "methane_x.safety",
    "methane_x.speech",
    "methane_x.tools",
    "methane_x.verification",
    "methane_x.voice",
    "jarvis",
)


class ImportSmokeTests(unittest.TestCase):
    def test_all_modules_import(self):
        for name in MODULES:
            with self.subTest(module=name):
                importlib.import_module(name)


if __name__ == "__main__":
    unittest.main()
