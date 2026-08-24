import unittest

from jarvis.adaptation import AdaptationLedger
from jarvis.simulation import Simulator
from jarvis.world_model import SelfModel, WorldModel


class OrganismCoreTests(unittest.TestCase):
    def test_world_and_self_models(self):
        world = WorldModel()
        entity = world.observe("server", {"status": "degraded"}, 0.8)
        world.relate("server", "owned_by", "user")
        self_model = SelfModel()
        self_model.register_capability("reasoning")
        self_model.register_limitation("no_sensor")
        self_model.record_metric("decision_latency", 0.2)
        self.assertEqual(entity.attributes["status"], "degraded")
        self.assertIn(("server", "owned_by", "user"), world.relations)
        self.assertIn("reasoning", self_model.capabilities)

    def test_simulation_orders_candidates(self):
        outcomes = Simulator().evaluate(
            [("a", ["inspect"]), ("b", ["inspect", "repair"])],
            lambda steps: 0.8 if len(steps) == 1 else 0.4,
        )
        self.assertEqual(outcomes[0].strategy, "a")
        self.assertTrue(outcomes[0].success)

    def test_adaptation_requires_evidence_and_benefit(self):
        ledger = AdaptationLedger()
        ledger.propose("planner", "improve search", ["repeated planning failures"], 0.8)
        ledger.propose("memory", "replace store", ["slow reads"], 0.4)
        self.assertEqual(len(ledger.actionable()), 1)


if __name__ == "__main__":
    unittest.main()
