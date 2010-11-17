@echo off
if "%1"=="" goto :error

set DEST_DIR=Output\%1

if not exist %DEST_DIR%\Translations mkdir %DEST_DIR%\Translations
echo Copying translation files
copy Translations\*.buf %DEST_DIR%\Translations

if "%1"=="debug" (
    echo Copying Qt debug files
    copy %QT_DIR%\bin\QtCored4.dll %DEST_DIR%
    copy %QT_DIR%\bin\QtGuid4.dll %DEST_DIR%
) else (
    echo Copying Qt release files
    copy %QT_DIR%\bin\QtCore4.dll %DEST_DIR%
    copy %QT_DIR%\bin\QtGui4.dll %DEST_DIR%
)

goto :end

:error
echo Please pass debug or release as the first argument.

:end
