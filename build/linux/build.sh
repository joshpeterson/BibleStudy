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

if [ ! -d "pixmaps" ]; then
    mkdir pixmaps
fi

if [ ! -d "applications" ]; then
    mkdir applications
fi

if [ ! -d "BibleStudy" ]; then
    mkdir BibleStudy
fi

cd BibleStudy

if [ ! -d "Translations" ]; then
    mkdir Translations
fi

cd ../..
cp ../Translations/*.buf share/BibleStudy/Translations/
cp ../BibleStudyGui/icons/bible-study.xpm share/pixmaps/
cp ../debian/bible-study.desktop share/applications/

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

