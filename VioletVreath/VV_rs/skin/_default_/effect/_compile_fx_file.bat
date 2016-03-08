REM コンパイルしています・・・。エラー時はPAUSEします。
REM   "%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" %1 /O3 /T fx_2_0 /D VS_VERSION=vs_2_0 /D PS_VERSION=ps_2_0 /Fo 2_0_%2
REM  @if not %ERRORLEVEL% == 0 pause
"%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" %1 /O3 /T fx_2_0 /D VS_VERSION=vs_3_0 /D PS_VERSION=ps_3_0 /Fo 3_0_%2
@if not %ERRORLEVEL% == 0 pause
exit
