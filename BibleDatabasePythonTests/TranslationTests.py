import unittest
from BibleDatabase import Translation

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

if __name__ == "__main__":
    unittest.main()
