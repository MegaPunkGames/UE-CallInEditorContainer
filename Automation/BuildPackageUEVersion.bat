@echo off

set errorVersions=

if "%1"=="" goto missingArgument
if "%2"=="" goto missingArgument

:run
call rmdir "..\Package\%1"  /S /Q
echo Building for '%1'...
call BuildUEVersion.bat %1 %2 -minimal
if %ERRORLEVEL% NEQ 0 (
	echo Failed with error=%ERRORLEVEL%.
) else (
  echo Packaging for '%1'...
  call PackageUEVersion.bat %1 %2
  if %ERRORLEVEL% NEQ 0 (
	  echo Failed with error=%ERRORLEVEL%.
  ) else (
	  echo Success.
	)
)
goto end

:missingArgument
echo Missing argument 'UE version' 'Plugin version'
set errorResult=1
goto end

:end
echo.
echo.
echo ----------------------------------------------------
if %errorResult% NEQ 0 (
  echo Package failed for version^(s^): %1
) else (
  echo Package completed successfully!!!
)
echo ----------------------------------------------------
