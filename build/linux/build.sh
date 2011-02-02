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
echo "*** Building BibleStudyGui"
echo "***"
cd ../BibleStudyGui
qmake
make

echo "***"
echo "*** Copying metadata into Output directory"
echo "***"
cd ../Output
if [ ! -d "share" ]; then
    mkdir share
fi

cd share

if [ ! -d "BibleStudy" ]; then
    mkdir BibleStudy
fi

cd BibleStudy

if [ ! -d "BibleStudy" ]; then
    mkdir Translations
fi

if [ ! -d "icons" ]; then
    mkdir icons
fi

cd ../..
cp ../Translations/*.buf share/BibleStudy/Translations/
cp ../icons/* share/BibleStudy/icons/

echo "***"
echo "*** Building BibleStudy"
echo "***"
cd ..
qmake
make

echo "***"
echo "***  Running BibleDatabaseBehaviors verification tests"
echo "***"
cd Output
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib bin/BibleDatabaseBehaviors

