ECHO OFF
REM 更新されていればコンパイル
FOR /F %%X IN ('dir /o-d /b *.fx') DO CALL :_EXECUTE_RUBY_ %%X
EXIT /B

:_EXECUTE_RUBY_
ECHO _exec_compile_fx_file.rb %1 fxo
ruby _exec_compile_fx_file.rb %1 fxo
:EOF
