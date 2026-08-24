import unittest

from methane_x.brain import Brain


class BrainTests(unittest.TestCase):
    def setUp(self) -> None:
        self.brain = Brain()

    def test_status(self) -> None:
        self.assertIn("Online", self.brain.process("status"))

    def test_memory_round_trip(self) -> None:
        self.brain.process("remember the prototype is called MethaneX")
        response = self.brain.process("what is the prototype called")
        self.assertIn("MethaneX", response)

    def test_action_adapter(self) -> None:
        self.brain.register_action("ping", lambda _: "pong")
        self.assertEqual(self.brain.process("ping device"), "pong")

    def test_shutdown_event(self) -> None:
        self.assertEqual(self.brain.perceive("exit").kind, "shutdown")


if __name__ == "__main__":
    unittest.main()
