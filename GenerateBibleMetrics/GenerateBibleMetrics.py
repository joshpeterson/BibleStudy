import sys
import re
import unittest
import BibleDatabase
from operator import itemgetter

class WordDataTest(unittest.TestCase):
    def testAddWordData(self):
        wordData = WordData("Foo", "F")
        wordData.add("foo", 1)
        self.assertEquals(wordData.count("foo"), 1)

    def testAddWordTwice(self):
        wordData = WordData("Foo", "F")
        wordData.add("foo", 3)
        wordData.add("foo", 15)
        self.assertEquals(wordData.count("foo"), 2)

    def testAddWordDifferentCasing(self):
        wordData = WordData("Foo", "F")
        wordData.add("foo", 3)
        wordData.add("Foo", 15)
        self.assertEquals(wordData.count("foo"), 2)

    def testGetWordVerseIds(self):
        wordData = WordData("Foo", "F")
        wordData.add("foo", 3)
        wordData.add("foo", 15)
        self.assertEquals(wordData.verses("foo"), [3, 15])

    def testGetCountForWordThatHasNotBeenAdded(self):
        wordData = WordData("Foo", "F")
        self.assertEquals(wordData.count("foo"), 0)

    def testGetVersesForWordThatHasNotBeenAdded(self):
        wordData = WordData("Foo", "F")
        self.assertEquals(wordData.verses("foo"), [])

    def testWordDataNames(self):
        wordData = WordData("Foo", "F")
        self.assertEquals(wordData.longName, "Foo")
        self.assertEquals(wordData.shortName, "F")

class WordData:
    def __init__(self, longName, shortName):
        self.words = {}
        self.longName = longName
        self.shortName = shortName

    def add(self, word, verse_id):
        word = word.lower()
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

class WordSplitterTest(unittest.TestCase):
    def testSplitIntoSingleWordsShort(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning God", 1), ["In", "the", "beginning", "God"])

    def testSplitIntoSingleWordsLong(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning God created the earth", 1), ["In", "the", "beginning", "God", "created", "the", "earth"])

    def testSplitIntoDoubleWords(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning God", 2), ["In the", "the beginning", "beginning God"])

    def testSplitInto3Words(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning God", 3), ["In the beginning", "the beginning God"])

    def testSplitInto3WordsLong(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning God created the earth", 3), ["In the beginning", "the beginning God", "beginning God created", "God created the", "created the earth"])

    def testSplitOnPeriod(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In. the beginning God", 1), ["In", "the", "beginning", "God"])

    def testSplitOnComma(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In, the beginning God", 1), ["In", "the", "beginning", "God"])
        
    def testSplitOnColon(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning: God", 1), ["In", "the", "beginning", "God"])

    def testSplitOnSemiColon(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.findWords("In the beginning;God", 1), ["In", "the", "beginning", "God"])

    def testWordListToString(self):
        splitter = WordSplitter()
        self.assertEquals(splitter.wordListToString(["foo", "bar", "baz"]), "foo bar baz")

class WordSplitter:
    def findWords(self, text, numWordsInEachEntry):
        wordList = []
        individual_words = re.findall(r'\w+', text)

        for i in range(0, len(individual_words)):
            if i + numWordsInEachEntry-1 < len(individual_words):
                wordList.append(self.wordListToString(individual_words[i:i + numWordsInEachEntry]))

        return wordList

    def wordListToString(self, wordList):
        output = ""
        for word in wordList:
            output += word + " "

        return output[:len(output)-1]

class VerseIteratorTest(unittest.TestCase):
    def setUp(self):
        self.translation = BibleDatabase.Translation()
        self.translation.resume("../Translations/TT.buf")

    def testVerseIterator(self):
        verses = VerseIterator(self.translation)

        num_verses_iterated = 0
        for verse in verses:
            num_verses_iterated += 1

        self.assertEquals(num_verses_iterated, self.translation.num_verses)

class VerseIterator:
    def __init__(self, translation):
        self.translation = translation
        self.current_verse_id = -1

    def __iter__(self):
        return self

    def next(self):
        if self.current_verse_id >= self.translation.num_verses - 1:
            raise StopIteration
        else:
            self.current_verse_id += 1
            return self.translation.get_verse(self.current_verse_id)

def GenerateForTranslation(translationFileName, numberOfWordsInGroup):
    translation = BibleDatabase.Translation()
    translation.resume(translationFileName)
    verses = VerseIterator(translation)
    wordData = WordData(translation.long_name, translation.short_name)
    splitter = WordSplitter()

    stopWords = ("a", "i", "of", "and", "or", "but", "to", "the", "in", "that", "with", "for", "from", "of the", "and the", "in the", "to the", "for the", "from the")

    for verse in verses:
        words = splitter.findWords(verse.text, numberOfWordsInGroup)
        for word in words:
            word = word.lower()
            if not word in stopWords:
                wordData.add(word, verse.id)

    counter = {}
    for entry in wordData.words.keys():
        counter[entry] = len(wordData.words[entry])

    sorted_counter = sorted(counter.iteritems(), key=itemgetter(1), reverse=True)

    i = 0
    for key in sorted_counter:
        print key
        i += 1
        if i == 20:
            break

    return wordData

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "test":
        del sys.argv[1]
        unittest.main()
    else:
        if len(sys.argv) != 3:
            print "Usage: GenerateBibleMetrics.py <translation file name> <number of words in group>"
        else:
            wordData = GenerateForTranslation(sys.argv[1], int(sys.argv[2]))

