#!/bin/bash

# update forward declaration 
replace_begin="\/\/\/\/ forward declaration begin"
vvfd=`/bin/find ./src/jp/gecchi/VioletVrain -name '*.h' | xargs grep -E '^class' | sed 's/\(.\+:\)\(class [A-Za-z0-9_]\+\)\(.\+$\)/\2;/g' | sort | uniq`
replace_end="\/\/\/\/ forward declaration end"

perl -i -0pe "s/${replace_begin}[\r\n _a-zA-Z0-9;\/<>]+${replace_end}/${replace_begin}\n${vvfd}\n${replace_end}/gm" src/VioletVrain.h


