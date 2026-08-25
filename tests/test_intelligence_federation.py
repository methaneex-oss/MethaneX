import unittest

from jarvis.intelligence import IntelligenceFederator, IntelligenceResult


class Provider:
    def __init__(self, name, confidence):
        self.name = name
        self.confidence = confidence

    def reason(self, prompt, context):
        return IntelligenceResult(self.name, f"answer:{prompt}", self.confidence)


class IntelligenceFederationTests(unittest.TestCase):
    def test_providers_are_replaceable_and_best_is_selected(self):
        federation = IntelligenceFederator([Provider("a", 0.4), Provider("b", 0.9)])
        results = federation.query("solve", ["fact"])
        self.assertEqual(len(results), 2)
        self.assertEqual(federation.best(results).provider, "b")

    def test_provider_failure_isolated(self):
        class Broken:
            name = "broken"
            def reason(self, prompt, context):
                raise RuntimeError("offline")
        federation = IntelligenceFederator([Broken(), Provider("ok", 0.8)])
        self.assertEqual(federation.best(federation.query("x")).provider, "ok")


if __name__ == "__main__":
    unittest.main()
