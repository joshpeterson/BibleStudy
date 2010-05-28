@echo off

set PATH=%QT_DIR%\bin;%PATH%
set QMAKESPEC=win32-msvc2005

qmake -Wall -tp vc BibleDatabase.pro
qmake -Wall -tp vc BibleStudy.pro
qmake -Wall -tp vc Behaviors\BibleStudyBehaviors.pro
