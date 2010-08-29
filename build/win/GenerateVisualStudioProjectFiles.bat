@echo off

if "%QT_DIR%" == "" goto :qterror
if "%BOOST_DIR%" == "" goto :boosterror
if "%GOOGLE_PROTOBUF_DIR%" == "" goto :protobuferror

set PATH=%QT_DIR%\bin;%PATH%
set QMAKESPEC=win32-msvc2005

qmake -Wall -tp vc BibleDatabase.pro
qmake -Wall -tp vc BibleDatabaseBehaviors.pro
qmake -Wall -tp vc BibleStudyGui.pro
qmake -Wall -tp vc BibleStudy.pro

goto :end

:qterror
echo Please set the QT_DIR environment variable (example: C:\Qt\4.4.0).
goto :end

:boosterror
echo Please set the BOOST_DIR environment variable (example: C:\Program Files\boost\boost_1_39).
goto :end

:protobuferror
echo Please set the GOOGLE_PROTOBUF_DIR environment variable (example: C:\Program Files\protobuf-2.0.1\protobuf-2.0.1\vsprojects).
goto :end

:end
