#!/bin/sh
echo "***"
echo "*** Building BibleDatabase"
echo "***"
cd BibleDatabase
qmake
make

echo "***"
echo "*** Building BibleDatabaseBehaviors"
echo "***"
cd ../BibleDatabaseBehaviors
qmake
make

echo "***"
echo "***  Running BibleDatabaseBehaviors verification tests"
echo "***"
cd ../Output
./BibleDatabaseBehaviors

echo "***"
echo "*** Building BibleStudyGui"
echo "***"
cd ../BibleStudyGui
qmake
make

echo "***"
echo "*** Building BibleStudy"
echo "***"
cd ..
qmake
make

echo "***"
echo "*** Copying metadata into Output directory"
echo "***"
cd Output
cp ../Translations/* Translations/
cp ../icons/* icons/
