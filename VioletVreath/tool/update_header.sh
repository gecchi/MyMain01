#!/bin/bash

cd ..

# update Version.h
echo \#define VERSION \"VER 0.30.`git log --oneline --no-merges | wc -l`\"  >  src/jp/gecchi/VioletVreath/Version.h

# update CommonActorsHeader
CommonHeader=src/jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h
echo '#ifndef VVCOMMONACTORSHEADER_H_' >  ${CommonHeader}
echo '#define VVCOMMONACTORSHEADER_H_' >> ${CommonHeader}
echo '#include "jp/gecchi/VioletVreath/VioletVreath.h"' >> ${CommonHeader} 
echo '' >> ${CommonHeader}
/bin/find . -name '*.h' | grep '.*\/actor\/common\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${CommonHeader}
echo '' >> ${CommonHeader} 
/bin/find . -name '*.h' | grep '.*\/actor\/effect\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${CommonHeader}
echo '' >> ${CommonHeader} 
/bin/find . -name '*.h' | grep '.*\/actor\/item\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${CommonHeader}
echo '' >> ${CommonHeader} 
/bin/find . -name '*.h' | grep '.*\/actor\/label\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${CommonHeader}
echo '' >> ${CommonHeader} 
/bin/find . -name '*.h' | grep '.*\/actor\/chikei\/wall\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${CommonHeader}
echo '' >> ${CommonHeader} 
echo '#endif /*VVCOMMONACTORSHEADER_H_*/' >> ${CommonHeader}



# update EnemysHeader
EnemysHeader=src/jp/gecchi/VioletVreath/actor/VVEnemysHeader.h
echo '#ifndef VVENEMYSHEADER_H_' >  ${EnemysHeader}
echo '#define VVENEMYSHEADER_H_' >> ${EnemysHeader}
echo '#include "jp/gecchi/VioletVreath/VioletVreath.h"' >> ${EnemysHeader} 
echo '' >> ${EnemysHeader}
echo '#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"' >> ${EnemysHeader}
echo '#include "jp/ggaf/lib/scene/RotateFormationScene.h"' >> ${EnemysHeader}
echo '' >> ${EnemysHeader}
/bin/find . -name '*.h' | grep '.*\/actor\/enemy\/.*' | sed 's/^\.\/src\//#include "/g' | sed 's/$/"/g' >> ${EnemysHeader}
echo '' >> ${EnemysHeader}
echo '#endif /*VVENEMYSHEADER_H_*/' >> ${EnemysHeader}



# update forward declaration 
replace_begin="\/\/\/\/ forward declaration begin"
vvfd=`/bin/find ./src/jp/gecchi/VioletVreath -name '*.h' | xargs grep -E '^class' | sed 's/\(.\+:\)\(class [A-Za-z0-9_]\+\)\(.\+$\)/\2;/g' | sort | uniq`
replace_end="\/\/\/\/ forward declaration end"

perl -i -0pe "s/${replace_begin}[\r\n _a-zA-Z0-9;\/<>]+${replace_end}/${replace_begin}\n${vvfd}\n${replace_end}/gm" src/jp/gecchi/VioletVreath/VioletVreath.h


