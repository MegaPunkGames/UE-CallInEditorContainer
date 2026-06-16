@echo off

set errorVersions=
set versionFile=SupportedVersions.txt

if "%1"=="" goto missingArgument
if "%2"=="" goto run
set versionFile="%2"

:run
if exist "..\Package" (
	call rmdir "..\Package"  /S /Q
)

set earliestVersion=0
for /F "eol=; tokens=1,2 delims=," %%i in (%versionFile%) do (
	if "!earliestVersion!"=="0" (
		set earliestVersion=%%i
	)

	call BuildPackageUEVersion.bat %%i %1 -minimal
	if %ERRORLEVEL% NEQ 0 (
		if "!errorVersions!"=="" (
			set errorVersions=%%i
		) else (
			set errorVersions="%errorVersions%, %%i"
		)
		echo Failed with error=%ERRORLEVEL%.
	)
)

call ChangeUETarget.bat !earliestVersion!

goto end

:missingArgument
echo Missing argument 'Plugin version'
set errorResult=1
goto end

:end
echo.
echo.
echo ----------------------------------------------------
if %errorResult% NEQ 0 (
  if "%errorVersions%"=="" (
    echo Package completed successfully!!!
  ) else (
    echo Package failed for version^(s^): %errorVersions%
  )
)
echo ----------------------------------------------------
