REM コンパイルしています・・・。エラー時はPAUSEします。
"%DXSDK_DIR%\Utilities\bin\x64\fxc.exe" %1 /O3 /T fx_2_0 /Fo 3_0_%2
@if not %ERRORLEVEL% == 0 (
  pause
  exit
) else (
REM  copy /Y 3_0_%2 ..\..\..\..\..\Mogera\MgrRs\effect
REM  copy /Y 3_0_%2 ..\..\..\..\..\Hogera\HgrRs\effect
REM  copy /Y 3_0_%2 ..\..\..\..\..\SimpleSample\SS_rs\effect
REM  copy /Y 3_0_%2 ..\..\..\..\..\VVViewer\VvvRs\effect
REM  copy /Y 3_0_%2 ..\..\..\..\..\VioletVrain\VvRs\effect
  exit
)

