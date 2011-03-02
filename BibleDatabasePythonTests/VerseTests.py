import unittest
from BibleDatabase import Verse

class TestVerse(unittest.TestCase):
    def setUp(self):
        self.verse = Verse("Book", 1, 3, "Test verse text.", 10)

    def testBook(self):
        self.assertEqual(self.verse.book, "Book")

    def testChapter(self):
        self.assertEqual(self.verse.chapter, 1)

    def testVerse(self):
        self.assertEqual(self.verse.verse, 3)

    def testText(self):
        self.assertEqual(self.verse.text, "Test verse text.")

    def testId(self):
        self.assertEqual(self.verse.id, 10)

if __name__ == "__main__":
    unittest.main()
