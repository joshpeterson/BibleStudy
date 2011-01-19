#!/bin/sh
echo "***"
echo "*** Cleaning BibleDatabase"
echo "***"
cd BibleDatabase
make distclean

echo "***"
echo "*** Cleaning BibleDatabaseBehaviors"
echo "***"
cd ../BibleDatabaseBehaviors
make distclean

echo "***"
echo "*** Cleaning BibleStudyGui"
echo "***"
cd ../BibleStudyGui
make distclean

echo "***"
echo "*** Cleaning BibleStudy"
echo "***"
cd ..
make distclean

echo "***"
echo "*** Removing metadata from Output directory"
echo "***"
rm -rf Output/*
