REM コンパイルしています・・・。エラー時はPAUSEします。
"%DXSDK_DIR%\Utilities\bin\x64\fxc.exe" %1 /O3 /T fx_2_0 /Fo 3_0_%2
@if not %ERRORLEVEL% == 0 (
  pause
  exit
) else (
  copy /Y 3_0_%2 ..\..\..\VioletVreath_launcher\VV_rs\skin\_system_\effect
  copy /Y 3_0_%2 ..\..\..\Mogera\MgrRs\effect
  copy /Y 3_0_%2 ..\..\..\Hogera\HgrRs\effect
  copy /Y 3_0_%2 ..\..\..\SimpleSample\SS_rs\effect
  copy /Y 3_0_%2 ..\..\..\VVViewer\VvvRs\effect
  copy /Y 3_0_%2 ..\..\..\VioletVrain\VvRs\effect
  exit
)

