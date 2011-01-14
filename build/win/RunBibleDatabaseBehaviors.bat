@echo off
if "%1" == "" goto :error

Output\%1\BibleDatabaseBehaviors.exe
goto :end

:error
echo Please specify the configuration (Debug or Release) as the argument.

:end
