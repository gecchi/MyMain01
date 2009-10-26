REM %変数:~開始位置,長さ%で文字列を抜き出せる。
set DATE_TMP=%DATE:/=%
set TIME_TMP=%TIME: =0%
set YYYY=%DATE_TMP:~0,4%
set YY=%DATE_TMP:~2,2%
set MM=%DATE_TMP:~4,2%
set DD=%DATE_TMP:~6,2%
set HH=%TIME_TMP:~0,2%
set MI=%TIME_TMP:~3,2%
set SS=%TIME_TMP:~6,2%
set SSS=%TIME_TMP:~9,2%
set DATETIME=%yyyy%%mm%%dd%%hh%%mi%%ss%_%sss%
cd MyStg2nd
set LOGFILE=log\%DATETIME%.log
DebugCdt\MyStg2nd.exe  2>&1) >> %LOGFILE%
