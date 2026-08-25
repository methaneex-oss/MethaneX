import unittest

from jarvis.recovery import FailureClass, RecoveryEngine


class RecoverySubstrateTests(unittest.TestCase):
    def test_domain_classifier_controls_failure_class(self):
        engine = RecoveryEngine(lambda evidence: FailureClass.STRATEGY if "bad-plan" in evidence else FailureClass.UNKNOWN)
        decision = engine.decide(["bad-plan"], strategy="generate another candidate", confidence=0.7)
        self.assertEqual(decision.failure, FailureClass.STRATEGY)
        self.assertEqual(decision.action, "generate another candidate")

    def test_default_does_not_assume_domain_knowledge(self):
        decision = RecoveryEngine().decide(["timeout"], strategy="observe")
        self.assertEqual(decision.failure, FailureClass.UNKNOWN)


if __name__ == "__main__":
    unittest.main()
