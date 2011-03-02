@echo off
if "%PYTHON_DIR%"=="" goto :error

set PYTHONPATH=..\Output\release
"%PYTHON_DIR%\python" GenerateBibleMetrics.py test
goto :end

:error
echo Please set the PYTHON_DIR environment variable.

:end

