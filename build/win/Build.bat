@echo off

set CONFIGURATION=Release

if "%1" == "" goto :default

if "%1" == "Debug" goto :configuration
if "%1" == "Release" goto :configuration

echo Invalid configuration specified, please pass Debug or Release.
goto :end

:configuration

set CONFIGURATION=%1
goto :build

:default

echo Building Release configuration by default (to build Debug configuration pass Debug as the argument).
echo.

:build

echo Generating Visual Studio project files...
call build\win\GenerateVisualStudioProjectFiles.bat
echo.

echo Building BibleStudy...
call build\win\BuildBibleStudySolution.bat %CONFIGURATION%
echo.

echo Copying dependencies...
call build\win\CopyDependencies.bat %CONFIGURATION%
echo.

echo Validating BibleDatabase behaviors.
call build\win\RunBibleDatabaseBehaviors.bat %CONFIGURATION%
echo.

:end
