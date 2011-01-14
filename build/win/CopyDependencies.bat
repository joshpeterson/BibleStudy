@echo off
if "%1"=="" goto :error

set DEST_DIR=Output\%1

if not exist %DEST_DIR%\Translations mkdir %DEST_DIR%\Translations
echo Copying translation files
copy Translations\*.buf %DEST_DIR%\Translations

if not exist %DEST_DIR%\icons mkdir %DEST_DIR%\icons
echo Copying icon files
copy icons\*.png %DEST_DIR%\icons

if "%1"=="Debug" (
    echo Copying Qt debug files
    copy %QT_DIR%\lib\QtCored4.dll %DEST_DIR%
    copy %QT_DIR%\lib\QtGuid4.dll %DEST_DIR%
) else (
    echo Copying Qt release files
    copy %QT_DIR%\lib\QtCore4.dll %DEST_DIR%
    copy %QT_DIR%\lib\QtGui4.dll %DEST_DIR%
)

goto :end

:error
echo Please pass Debug or Release as the first argument.

:end
