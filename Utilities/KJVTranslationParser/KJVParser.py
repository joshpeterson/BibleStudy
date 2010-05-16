from BeautifulSoup import BeautifulSoup
import urllib2
import re

index = urllib2.urlopen("http://quod.lib.umich.edu/k/kjv/browse.html")
indexSoup = BeautifulSoup(index)
baseUrl = "http://quod.lib.umich.edu"
verseNumber = 0

bibleFile = open("KJV.txt", "w")

bible = []

for relativeBookUrl in indexSoup.findAll(href=re.compile("^/cgi.*")):
    fullBookUrl = baseUrl + relativeBookUrl['href']
    book = urllib2.urlopen(fullBookUrl)
    bookSoup = BeautifulSoup(book)
    lines = str(bookSoup).split("<br />")
    header = lines[0].split("</h2>")[0]
    
    book = header.split("<h2>")[1]
    print "Getting book: " + book

    lines[0] = lines[0].split("</h2>")[1]
    chapter = 0
    for line in lines:
        if line.count("<h3>") > 0:
            chapter = chapter + 1
            verse = 0

        verse = verse + 1
        if line.count("]"):
            verseText = line.split("] ")[1]

            verseEntry = str(verseNumber) + "*" + book + "*" + str(chapter) + "*" + str(verse) + "*" + verseText
            bible.append(verseEntry)
            verseNumber = verseNumber + 1

for line in bible:
    bibleFile.write(line + "\n")
bibleFile.close()
