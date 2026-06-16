@echo off
setlocal ENABLEDELAYEDEXPANSION

if "%1"=="" goto missingArgument
if "%2"=="" goto missingArgument

set errorResult=0
set pluginDirectory=%~dp0..
set outputDirectory=%pluginDirectory%\Package
set baseUnrealDirectory=
set "targets=-Rocket"

set engineVersion=%1
set "shortVersion=%engineVersion:UE_=%"
for /f "tokens=2*" %%i in ('reg query "HKLM\SOFTWARE\EpicGames\Unreal Engine\%shortVersion%" /v InstalledDirectory') do (
	if [%%j] NEQ [] (
		set "baseUnrealDirectory=%%j"
	)
)
if [%baseUnrealDirectory%] EQU [] (
	echo Engine version %1 not found.
	set errorResult=1
	goto end
)

if "%3"=="" goto run
if "%3"=="-minimal" (
	set "targets=-TargetPlatforms=Win64"
) else (
	set "targets=-TargetPlatforms=%3"
)

if "%4"=="" goto run
set pluginDirectory=%3

if "%5"=="" goto run
set outputDirectory=%4

:run
echo Looking for Unreal at '%baseUnrealDirectory%\Engine\Build\BatchFiles\RunUAT.bat'
if not exist "%baseUnrealDirectory%\Engine\Build\BatchFiles\RunUAT.bat" (
	echo Engine version %1 not found.
	set errorResult=1
	goto end
) else (
	echo Using engine installed at '%%j'
)

if exist "%outputDirectory%\%1" (
	rmdir "%outputDirectory%\%1" /S /Q
)
mkdir "%outputDirectory%\%1"

if exist "%pluginDirectory%/Plugins/CallInEditorContainer/Binaries" (
	rmdir "%pluginDirectory%\Plugins\CallInEditorContainer\Binaries" /S /Q
)

call pwsh.exe -ExecutionPolicy Unrestricted -command "./ChangePluginVersion.ps1 '%pluginDirectory%\Plugins\CallInEditorContainer\CallInEditorContainer.uplugin' %2"
call "%baseUnrealDirectory%\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -plugin="%pluginDirectory%\Plugins\CallInEditorContainer\CallInEditorContainer.uplugin" -package="%outputDirectory%\%1" %targets%
if %ERRORLEVEL% NEQ 0 (
	set errorResult=%ERRORLEVEL%
	goto error
)
goto end

:missingArgument
echo "Missing argument 'UE version' 'Plugin version' [-minimal|targetPlatform] [pluginDirectory] [outputDirectory]"
set errorResult=1
goto end

:error
echo Failed to build plugin. RunUAT exited with code %errorResult%
goto end

:end
echo Completed with result %errorResult%
exit /B %errorResult%
