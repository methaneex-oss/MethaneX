import unittest

from methane_x.safety import ActionGuard, ActionRequest, CapabilityPolicy


class SafetyTests(unittest.TestCase):
    def test_capability_is_denied_by_default(self):
        guard = ActionGuard(CapabilityPolicy())
        with self.assertRaises(PermissionError):
            guard.authorize(ActionRequest("filesystem.write", "write a file"))

    def test_explicit_capability_can_be_authorized(self):
        policy = CapabilityPolicy()
        policy.allow("filesystem.read")
        ActionGuard(policy).authorize(ActionRequest("filesystem.read", "read a file"))


if __name__ == "__main__":
    unittest.main()
