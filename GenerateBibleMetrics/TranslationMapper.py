import sys
import unittest
from GenerateBibleMetrics import VerseIterator
import BibleDatabase


class TranslationMapGeneratorTest(unittest.TestCase):
    def testAddTranslation(self):
        generator = TranslationMapGenerator()

        translation = BibleDatabase.Translation()
        translation.resume("../Translations/TT.buf")

        translation2 = BibleDatabase.Translation()
        translation2.resume("../Translations/DR.buf")

        generator.addTranslation(translation)
        generator.addTranslation(translation2)

        self.assertEquals(len(generator.translations), 2)

    def testBookSetCreation(self):
        generator = TranslationMapGenerator()

        translation = BibleDatabase.Translation()
        translation.resume("../Translations/TT.buf")

        generator.addTranslation(translation)

        translationBookSet = generator.CreateTranslationBookSet()
        self.assertEquals(len(translationBookSet), 2)

    def testBookSetContents(self):
        generator = TranslationMapGenerator()

        translation = BibleDatabase.Translation()
        translation.resume("../Translations/TT.buf")

        generator.addTranslation(translation)

        translationBookSet = generator.CreateTranslationBookSet()
        self.assertTrue("Genesis" in translationBookSet)
        self.assertTrue("Exodus" in translationBookSet)

class TranslationMapGenerator:
    def __init__(self):
        self.translations = []

    def addTranslation(self, translation):
        self.translations.append(translation)

    def CreateTranslationBookSet(self):
        bookSet = set()
        for translation in self.translations:
            verses = VerseIterator(translation)
            for verse in verses:
                bookSet.add(verse.book)

        return bookSet

def GenerateTranslationBookMap(translationFileNames):
    generator = TranslationMapGenerator()
    for translationFileName in translationFileNames:
        translation = BibleDatabase.Translation()
        translation.resume(translationFileName)
        generator.addTranslation(translation)

    print generator.CreateTranslationBookSet()


if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "test":
        del sys.argv[1]
        unittest.main()
    else:
        translationFileNames = ("../Translations/DR.buf", "../Translations/KJV.buf")
        GenerateTranslationBookMap(translationFileNames)
