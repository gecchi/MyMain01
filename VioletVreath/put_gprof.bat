C:\cygwin\mingw\bin\gprof "GprofCdt\VioletVreath.exe" gmon.out -p > gprofp_result.txt
C:\cygwin\mingw\bin\gprof "GprofCdt\VioletVreath.exe" gmon.out -q > gprofq_result.txt
C:\cygwin\mingw\bin\gprof "GprofCdt\VioletVreath.exe" gmon.out -A > gprofA_result.txt
cygstart gprofp_result.txt
cygstart gprofq_result.txt
cygstart gprofA_result.txt