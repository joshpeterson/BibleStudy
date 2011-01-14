@echo off

if "%INSTALLJAMMER_DIR%" == "" goto :error

"%INSTALLJAMMER_DIR%"\installjammer --build Installer/BibleStudyInstall.mpi
goto :end

:error
echo Please set the INSTALLJAMMER_DIR environment variable.

:end
