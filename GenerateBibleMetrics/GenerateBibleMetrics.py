import sys
import unittest
import BibleDatabase

class WordDataTest(unittest.TestCase):
    def testAddWordData(self):
        wordData = WordData()
        wordData.add("foo", 1)
        self.assertEquals(wordData.count("foo"), 1)

    def testAddWordTwice(self):
        wordData = WordData()
        wordData.add("foo", 3)
        wordData.add("foo", 15)
        self.assertEquals(wordData.count("foo"), 2)

    def testGetWordVerseIds(self):
        wordData = WordData()
        wordData.add("foo", 3)
        wordData.add("foo", 15)
        self.assertEquals(wordData.verses("foo"), [3, 15])

class WordData:
    def __init__(self):
        self.words = {}

    def add(self, word, verse_id):
        if word in self.words:
            self.words[word].append(verse_id)
        else:
            self.words[word] = [verse_id]

    def count(self, word):
        return len(self.words[word])

    def verses(self, word):
        return self.words[word]

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "test":
        del sys.argv[1]
        unittest.main()
    else:
        raise("Not implemented yet.")
