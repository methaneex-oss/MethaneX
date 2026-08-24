import unittest

from methane_x.cognitive_loop import CognitiveLoop
from methane_x.intelligence import IntelligenceResponse, IntelligenceRouter
from methane_x.planning import Planner


class FakeProvider:
    name = "test-provider"

    def generate(self, request):
        return IntelligenceResponse("planned response", self.name, 0.9)


class CognitiveLoopTests(unittest.TestCase):
    def test_run_plans_reasons_and_executes(self):
        loop = CognitiveLoop(Planner(), IntelligenceRouter([FakeProvider()]), executor=lambda text: f"executed: {text}")
        results = loop.run("check the system")
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].provider, "test-provider")
        self.assertEqual(results[0].output, "executed: planned response")


if __name__ == "__main__":
    unittest.main()
