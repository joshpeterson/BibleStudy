@echo off

if "%DOXYGEN_DIR%" == "" goto :error

pushd Doxygen

echo Removing old documentation...
if exist html rd /s /q html

echo Creating new documentation...
"%DOXYGEN_DIR%"\doxygen DoxyFile

popd

goto :end

:error

echo Please set the DOXYGEN_DIR environment variable to the directory where doxygen.exe exists.

:end
