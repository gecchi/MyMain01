bash.exe -c ' echo \#define VERSION \"VER 0.30.`git log --oneline --no-merges | wc -l`\"  >  Version.h '
