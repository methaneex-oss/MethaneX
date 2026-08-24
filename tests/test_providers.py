import os
import unittest
from unittest.mock import patch

from methane_x.providers import HTTPJSONProvider


class ProviderTests(unittest.TestCase):
    def test_missing_endpoint_fails_cleanly(self):
        provider = HTTPJSONProvider("test", "METHANEX_TEST_ENDPOINT")
        with patch.dict(os.environ, {}, clear=True):
            with self.assertRaises(RuntimeError):
                provider.generate(type("R", (), {"prompt": "hello", "context": ()})())


if __name__ == "__main__":
    unittest.main()
