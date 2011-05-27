

fx_timestamp = File::stat("CubeMapMeshEffect.fx").mtime.strftime("%Y%m%d%H%M%S").to_i
p fx_timestamp
if File.exist?("hoge") then
  fxo_timestamp = File::stat("CubeMapMeshEffect.fxo").mtime.strftime("%Y%m%d%H%M%S").to_i
else
  fxo_timestamp = 0
end
p fxo_timestamp
if fx_timestamp > fxo_timestamp then
  cmd = '"%DXSDK_DIR%Utilities\bin\x86\fxc.exe" CubeMapMeshSetEffect.fx /T fx_2_0 /D VS_VERSION=vs_2_0 /D PS_VERSION=ps_2_0 /Fo CubeMapMeshSetEffect.fxo'
  system %Q|cmd /C start #{cmd}|
  print "---"
  cmd = '"%DXSDK_DIR%Utilities\bin\x86\fxc.exe" CubeMapMeshSetEffect.fx /T fx_2_0 /D VS_VERSION=vs_3_0 /D PS_VERSION=ps_3_0 /Fo CubeMapMeshSetEffect.fxo'
  system %Q|cmd /C start #{cmd}|
end
