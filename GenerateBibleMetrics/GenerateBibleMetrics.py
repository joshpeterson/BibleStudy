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

    def testGetCountForWordThatHasNotBeenAdded(self):
        wordData = WordData()
        self.assertEquals(wordData.count("foo"), 0)

    def testGetVersesForWordThatHasNotBeenAdded(self):
        wordData = WordData()
        self.assertEquals(wordData.verses("foo"), [])

class WordData:
    def __init__(self):
        self.words = {}

    def add(self, word, verse_id):
        if word in self.words:
            self.words[word].append(verse_id)
        else:
            self.words[word] = [verse_id]

    def count(self, word):
        if word in self.words:
            return len(self.words[word])
        else:
            return 0

    def verses(self, word):
        if word in self.words:
            return self.words[word]
        else:
            return []

class WordSearcherTest(unittest.TestCase):
    def setUp(self):
        self.translation = BibleDatabase.Translation()
        self.translation.resume("../Translations/TT.buf")

    def testIterateOneWordFirstFour(self):
        searcher = WordSearcher(self.translation)
        self.assertEquals(searcher.findWords(1, 4), ["In", "the", "beginning", "God"])

    def testIterateOneWordFirstFive(self):
        searcher = WordSearcher(self.translation)
        self.assertEquals(searcher.findWords(1, 5), ["In", "the", "beginning", "God", "created"])

class WordSearcher:
    def __init__(self, translation):
        self.translation = translation

    def findWords(self, numWordsInEntry, numEntries):
        words = []
        for verse_id in range(0, self.translation.num_verses):
            verse = self.translation.get_verse(verse_id)
            verse_words = verse.text.split(" ")
            for word in verse_words:
                words.append(word)
                if len(words) == numEntries:
                    return words

        return words

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "test":
        del sys.argv[1]
        unittest.main()
    else:
        raise("Not implemented yet.")
