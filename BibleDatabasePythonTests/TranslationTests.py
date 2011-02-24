import unittest
from BibleDatabase import Translation
from BibleDatabase import SearchResultsSerial

class TestTranslation(unittest.TestCase):
    def setUp(self):
        self.translation = Translation()
        self.translation.resume("../Translations/TT.buf")

    def testShortName(self):
        self.assertEquals(self.translation.short_name, "TT")
        
    def testLongName(self):
        self.assertEquals(self.translation.long_name, "Test Translation")

    def testGetVerse(self):
        verse = self.translation.get_verse(3)
        self.assertEquals(verse.book, "Genesis")
        self.assertEquals(verse.chapter, 1)
        self.assertEquals(verse.verse, 4)

    def testSearch(self):
        results = SearchResultsSerial("beginning")
        self.translation.search(results, 0)
        self.assertEquals(results.num_results(), 7)
        self.assertEquals(results.at(0), 0)
        self.assertEquals(results.translation_at(0), "Test Translation")

if __name__ == "__main__":
    unittest.main()
