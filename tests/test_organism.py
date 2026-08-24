import unittest

from jarvis.organism import OrganismState, ProcessState


class OrganismTests(unittest.TestCase):
    def test_self_model_tracks_processes_and_capabilities(self):
        organism = OrganismState()
        organism.self_model.register_capability("reasoning")
        organism.self_model.register_limitation("no_camera")
        organism.self_model.set_process("cognition", ProcessState.THINKING)
        self.assertIn("reasoning", organism.self_model.capabilities)
        self.assertIn("no_camera", organism.self_model.limitations)
        self.assertEqual(organism.self_model.active_processes["cognition"], ProcessState.THINKING)

    def test_experience_drives_explicit_adaptation_proposal(self):
        organism = OrganismState()
        organism.observe("strategy", "failed", False)
        organism.observe("strategy", "worked", True)
        proposal = organism.propose_adaptation(
            "strategy-selection",
            "mixed outcomes require better selection",
            ["strategy failed once", "strategy worked once"],
            0.7,
        )
        self.assertAlmostEqual(organism.success_rate("strategy"), 0.5)
        self.assertEqual(proposal.target, "strategy-selection")
        self.assertTrue(proposal.reversible)


if __name__ == "__main__":
    unittest.main()
