import unittest

from jarvis.cognition import BeliefStatus, CognitiveWorkspace, Metacognition
from jarvis.cognitive_engine import CognitiveEngine


class CognitiveEngineTests(unittest.TestCase):
    def test_workspace_tracks_beliefs_and_uncertainty(self):
        workspace = CognitiveWorkspace("repair system")
        belief = workspace.add_belief("system is degraded", 0.8, "sensor")
        belief.update(0.9, BeliefStatus.SUPPORTED)
        workspace.add_uncertainty("root cause unknown")
        self.assertEqual(belief.status, BeliefStatus.SUPPORTED)
        self.assertIn("uncertainty: root cause unknown", workspace.context())

    def test_engine_selects_and_evaluates_strategy(self):
        engine = CognitiveEngine()
        decision = engine.decide(
            "restore service",
            facts=["service is unavailable"],
            options=[
                ("inspect first", ["inspect logs"]),
                ("restart immediately", ["restart service", "verify service"]),
            ],
        )
        self.assertIsNotNone(decision.strategy)
        self.assertIsNotNone(decision.evaluation)
        self.assertGreaterEqual(decision.evaluation.confidence, 0.0)
        self.assertLessEqual(decision.evaluation.confidence, 1.0)

    def test_metacognition_is_bounded(self):
        workspace = CognitiveWorkspace("test")
        for _ in range(20):
            workspace.add_uncertainty("unknown")
        evaluation = Metacognition().evaluate(workspace, "gather evidence")
        self.assertGreaterEqual(evaluation.confidence, 0.0)
        self.assertLessEqual(evaluation.confidence, 1.0)


if __name__ == "__main__":
    unittest.main()
