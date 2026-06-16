@echo off

if "%1"=="" goto missingArgument
if "%2"=="" goto missingArgument

set errorResult=0
set pluginDirectory=..\Plugins\CallInEditorContainer
set packageDirectory=..\Package
set outputfile=%packageDirectory%\CallInEditorContainer_%2_%1.zip
set zipExecutable=C:\Program Files\7-Zip\7z.exe

:run
if not exist "%zipExecutable%" (
	echo 7-Zip executable not found.
	set errorResult=1
	goto end
)

if not exist "%packageDirectory%\%1\CallInEditorContainer.uplugin" (
	echo Packaged plugin not found.
	set errorResult=1
	goto end
)

if exist "%outputfile%" (
	call del %outputfile% /f
)
call mkdir "%packageDirectory%\%1\Config"
call mkdir "%packageDirectory%\%1\CallInEditorContainer"
call copy "%pluginDirectory%\Config" "%packageDirectory%\%1\Config\
call rmdir "%packageDirectory%\%1\Binaries"  /S /Q
call rmdir "%packageDirectory%\%1\Intermediate"  /S /Q
FOR /d %%a IN ("%packageDirectory%\%1\*") DO IF /i NOT "%%~nxa"=="CallInEditorContainer" call move "%packageDirectory%\%1\%%~nxa" "%packageDirectory%\%1\CallInEditorContainer\%%~nxa"
move "%packageDirectory%\%1\CallInEditorContainer.uplugin" "%packageDirectory%\%1\CallInEditorContainer\CallInEditorContainer.uplugin"

call "%zipExecutable%" a -r "%outputfile%" "%packageDirectory%\%1\*"
set errorResult=%ERRORLEVEL%
goto end

:missingArgument
echo Missing argument 'UE version' 'Plugin version'
set errorResult=1
goto end

:error
echo Failed to build plugin. RunUAT exited with code %ERRORLEVEL%
goto end

:end
echo Completed with result %errorResult%
exit /B %errorResult%
