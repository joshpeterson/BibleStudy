import unittest
from BibleDatabase import SearchResultsSerial

class TestVerse(unittest.TestCase):
    def setUp(self):
        self.results = SearchResultsSerial("beginning")

    def testGetSearchString(self):
        self.assertEquals(self.results.get_search_string(),"beginning")

    def testNumResults(self):
        self.assertEquals(self.results.num_results(), 0)

if __name__ == "__main__":
    unittest.main()
