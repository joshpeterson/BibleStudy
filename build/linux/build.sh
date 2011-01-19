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
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib bin/BibleDatabaseBehaviors

echo "***"
echo "*** Building BibleStudyGui"
echo "***"
cd ../BibleStudyGui
qmake
make

echo "***"
echo "*** Copying metadata into Output directory"
echo "***"
cd ../Output
mkdir share
cd share
mkdir BibleStudy
cd BibleStudy
mkdir Translations
mkdir icons
cd ../..
cp ../Translations/*.buf share/BibleStudy/Translations/
cp ../icons/* share/BibleStudy/icons/

echo "***"
echo "*** Building BibleStudy"
echo "***"
cd ..
qmake
make
