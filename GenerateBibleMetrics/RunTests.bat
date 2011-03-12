@echo off
if "%PYTHON_DIR%"=="" goto :error

if "%1" == "" goto :allTests

set PYTHONPATH=..\Output\release
"%PYTHON_DIR%\python" %1 test
goto :end

:allTests

set PYTHONPATH=..\Output\release
for %%i in (*.py) do call :runSpecificTest %%i
goto :end

:runSpecificTest
echo.
echo Running tests in %1
"%PYTHON_DIR%\python" %1 test
goto :end

:error
echo Please set the PYTHON_DIR environment variable.

:end

