import unittest

from methane_x.decision import Candidate, DecisionEngine


class DecisionTests(unittest.TestCase):
    def test_best_strategy_balances_value_confidence_and_risk(self):
        engine = DecisionEngine()
        chosen = engine.choose([
            Candidate("fast", expected_value=0.9, confidence=0.4, risk=0.1),
            Candidate("safe", expected_value=0.7, confidence=0.95, risk=0.05),
        ])
        self.assertIsNotNone(chosen)
        self.assertEqual(chosen.strategy, "safe")


if __name__ == "__main__":
    unittest.main()
