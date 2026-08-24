import unittest

from methane_x.health import HealthMonitor


class HealthTests(unittest.TestCase):
    def test_reports_healthy_and_failed_subsystems(self):
        monitor = HealthMonitor()
        monitor.register("memory", lambda: "sqlite available")
        monitor.register("broken", lambda: (_ for _ in ()).throw(RuntimeError("offline")))
        checks = monitor.run()
        self.assertEqual(len(checks), 2)
        self.assertTrue(checks[0].ok)
        self.assertFalse(checks[1].ok)
        self.assertFalse(monitor.snapshot()["healthy"])


if __name__ == "__main__":
    unittest.main()
