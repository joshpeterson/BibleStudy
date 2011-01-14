@echo off
if "%1" == "" goto :error

vcbuild /rebuild "BibleStudy.sln" "%1|Win32"
goto :end

:error
echo Please specify the configuration (Debug or Release) as the argument.

:end
