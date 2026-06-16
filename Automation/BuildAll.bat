@echo off

setlocal enabledelayedexpansion

set errorVersions=
set "builtVersions=None"
set versionFile=SupportedVersions.txt
if "%1"=="" goto missingArgument

if "%3"=="" goto run
set versionFile="%3"

:run
set errorExit=0
set earliestVersion=0
for /F "eol=; tokens=1,2 delims=," %%i in (%versionFile%) do (
	if "!errorExit!"=="0" (
		echo Building for '%%i'...

		if "!earliestVersion!"=="0" (
			set earliestVersion=%%i
		)

		if "%2"=="-minimal" (
			set "foundVersion=!builtVersions:%%j=_!"
		) else (
			set "foundVersion=!builtVersions!"
		)

		if "!foundVersion!"=="!builtVersions!" (
			call BuildUEVersion.bat %%i %1 %2
			if !ERRORLEVEL! NEQ 0 (
				echo Failed with error=!ERRORLEVEL!.
				if "%2"=="-minimal" (
					set errorExit=1
				) else (
					if "!errorVersions!"=="" (
							set errorVersions=%%i
						) else (
							set errorVersions=!errorVersions!, %%i
						)
				)
			) else (
				set builtVersions=!builtVersions! %%j
				echo Success !builtVersions!.
			)
		) else (
			echo %%j already built for target %%i, skipping.
		)
	)
)

call ChangeUETarget.bat !earliestVersion!
goto end

:missingArgument
echo "Missing argument 'Plugin version' [-minimal] [versionFile]"
set errorResult=1
goto end

:end
echo.
echo.
echo ----------------------------------------------------
if "%errorVersions%"=="" (
	echo Build for versions '!builtVersions:None =!' completed successfully!!!
) else (
	echo Build failed for version^(s^): !errorVersions!
)
echo ----------------------------------------------------

