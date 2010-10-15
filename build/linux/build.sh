#!/bin/sh
cd BibleDatabase
qmake
make

cd ../BibleDatabaseBehaviors
qmake
make

cd ../BibleStudyGui
qmake
make

cd ..
make

cd Output
cp ../Translations Translations/
cp ../icons icons/
