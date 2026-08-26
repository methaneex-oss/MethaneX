import unittest

from jarvis.adaptation import AdaptationProposal
from jarvis.evolution import EvolutionEngine


class EvolutionEngineTests(unittest.TestCase):
    def test_accepts_candidate_that_improves_baseline(self):
        engine = EvolutionEngine()
        proposal = AdaptationProposal("reasoning", "use a shorter planning path", ("repeated latency",), 0.8)

        results = engine.evaluate([proposal], lambda target, change: (0.5, 0.8))

        self.assertEqual(len(results), 1)
        self.assertTrue(results[0].accepted)
        self.assertAlmostEqual(results[0].improvement, 0.3)
        self.assertEqual(len(engine.accepted()), 1)

    def test_rejects_regression(self):
        engine = EvolutionEngine()
        proposal = AdaptationProposal("memory", "change retrieval ordering", ("missed recall",), 0.8)

        result = engine.evaluate([proposal], lambda target, change: (0.8, 0.6))[0]

        self.assertFalse(result.accepted)
        self.assertLess(result.improvement, 0.0)

    def test_rejects_non_reversible_change(self):
        engine = EvolutionEngine()
        proposal = AdaptationProposal("core", "replace live architecture", ("test",), 1.0, reversible=False)

        result = engine.evaluate([proposal], lambda target, change: (0.2, 1.0))[0]

        self.assertFalse(result.accepted)
        self.assertIn("non-reversible", result.reason)

    def test_invalid_threshold_is_rejected(self):
        engine = EvolutionEngine()
        with self.assertRaises(ValueError):
            engine.evaluate([], lambda target, change: (0.0, 0.0), minimum_improvement=1.1)


if __name__ == "__main__":
    unittest.main()
