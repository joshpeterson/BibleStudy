@echo off
if "%PYTHON_DIR%"=="" goto :error

set PYTHONPATH=..\Output\release
for %%i in (*.py) do call :run %%i
goto :end

:run
echo.
echo Running tests in %1:
"%PYTHON_DIR%\python" %1
goto :end

:error
echo Please set the PYTHON_DIR environment variable.

:end
