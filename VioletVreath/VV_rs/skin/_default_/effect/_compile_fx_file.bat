REM �R���p�C�����Ă��܂��E�E�E�B�G���[����PAUSE���܂��B
"%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" %1 /O3 /T fx_2_0 /Fo 3_0_%2
@if not %ERRORLEVEL% == 0 (
  pause
  exit
) else (
  copy /Y 3_0_%2 ..\..\..\..\..\Mogera\MgrRs\effect
  copy /Y 3_0_%2 ..\..\..\..\..\SimpleSample\SS_rs\effect
  copy /Y 3_0_%2 ..\..\..\..\..\VVViewer\VvvRs\effect
  exit
)

