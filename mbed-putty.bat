echo off
cls

set MBED_ENUMERATOR="mbed-port-enumerator.exe"
set PUTTY="putty.exe"

if not exist "%PUTTY%" (
  echo.
  echo   ERROR: %PUTTY% executable was not found...
  echo   Please download the portable Putty.exe and place it in the folder
  echo.
  pause
  exit
)

for /f "tokens=*" %%i in ('%MBED_ENUMERATOR%') do (
  set COM_PORT=%%i
)
echo Found MBED connected on '%COM_PORT%'

for %%a in (%COM_PORT%) do (
  start "" "%PUTTY%" -serial %%a
)
