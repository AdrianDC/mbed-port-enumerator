echo off
cls

set MBED_ENUMERATOR="mbed-port-enumerator.exe"
set PUTTY="putty.exe"

for /f %%i in ('%MBED_ENUMERATOR%') do set COM_PORT=%%i
echo Found MBED connected on '%COM_PORT%'

start "" "%PUTTY%" -serial %COM_PORT%
