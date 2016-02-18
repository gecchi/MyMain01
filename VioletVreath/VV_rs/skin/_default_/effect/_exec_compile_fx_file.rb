# ruby _exec_compile_fx_file.rb CubeMapMeshEffect.fx fxo
# と実行すると、CubeMapMeshEffect.fx ファイルの更新日付が新しければ
#   2_0_CubeMapMeshEffect.fxo
#   3_0_CubeMapMeshEffect.fxo
# が再コンパイルされて更新される。



# ファイル名(filename)の拡張子をextに変更する
# change_ext("sample.txt", ".html") #=> sample.html
def change_ext(filename, ext)
  return filename.gsub(/\.\w+$/, ext)
end

#MAIN
work_dir = File.expand_path(File.dirname(__FILE__)) #実行中のスクリプトのパス
effect_file = ARGV[0]
out_file = change_ext(effect_file, ".#{ARGV[1]}")
fx_timestamp = File::stat(effect_file).mtime.strftime("%Y%m%d%H%M%S").to_i
if File.exist?("3_0_#{out_file}") then
  fxo_timestamp = File::stat("3_0_#{out_file}").mtime.strftime("%Y%m%d%H%M%S").to_i
else
  fxo_timestamp = 0
end
if fx_timestamp > fxo_timestamp then
  cmd = "_compile_fx_file.bat #{effect_file} #{out_file}"
  print %Q|cmd /C start #{cmd}|
  print "\n"
  system %Q|cmd /C start #{cmd}|
end



