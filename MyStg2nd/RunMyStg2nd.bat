set LOGFILE=C:\cygwin\workspace\MyStg2nd\log\%1%date:~-10,4%%date:~-5,2%%date:~-2,2%%time:~-11,2%%time:~3,2%%time:~6,2%.log
cd C:\cygwin\workspace\MyStg2nd
C:\cygwin\workspace\MyStg2nd\DebugCdt\MyStg2nd.exe  2>&1) >> %LOGFILE%
