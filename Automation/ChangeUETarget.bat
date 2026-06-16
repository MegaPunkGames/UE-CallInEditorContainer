@echo off

if "%1"=="" goto missingArgument

set errorResult=0
set engineVersion=%1
set "shortVersion=%engineVersion:UE_=%"

echo Updating uproject version...
call pwsh.exe -ExecutionPolicy Unrestricted -command "./ChangeUProjectVersion.ps1 %shortVersion%"

call "C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "%cd%\..\CIEContainer.uproject"
echo:

if %ERRORLEVEL% NEQ 0 (
	set errorResult=%ERRORLEVEL%
	goto error
)
goto end

:missingArgument
echo Missing argument 'Version String'
set errorResult=1
goto end

:error
echo Failed to change target version plugin. Exited with code %ERRORLEVEL%
goto end

:end
echo Completed with result %errorResult%
exit /B %errorResult%
