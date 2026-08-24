import unittest

from methane_x.verification import VerifiedExecutor


class VerificationTests(unittest.TestCase):
    def test_success_on_first_attempt(self):
        executor = VerifiedExecutor(lambda _: "done", lambda value: value == "done")
        result = executor.run("action")
        self.assertTrue(result.ok)
        self.assertEqual(result.attempts, 1)

    def test_retry_is_bounded(self):
        calls = []
        executor = VerifiedExecutor(lambda _: calls.append(1) or "bad", lambda _: False, max_attempts=2)
        result = executor.run("action")
        self.assertFalse(result.ok)
        self.assertEqual(result.attempts, 2)
        self.assertEqual(len(calls), 2)


if __name__ == "__main__":
    unittest.main()
