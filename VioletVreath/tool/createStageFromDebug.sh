#!/bin/bash
cd ..

src_stage_prefix=$1
if [ "${src_stage_prefix}" = "" ]; then
    echo "Set arg1 that is copy source stage prefix (ex.StageDebug)"
    exit 1
fi

dest_stage_prefix=$2
if [ "${dest_stage_prefix}" = "" ]; then
    echo "Set arg2 that is create stage prefix (ex.Stage01)"
    exit 1
fi

stage_controller_dir=src/jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController
if [ ! -e ${stage_controller_dir} ]; then
    echo "StageController is not found. stage_controller_dir=${stage_controller_dir}"
    exit 1
fi

if [ ! -d ${stage_controller_dir} ]; then
    echo "StageController is not dir. stage_controller_dir=${stage_controller_dir}"
    exit 1
fi
src_stage_prefix=StageDebug
dest_stage_prefix=Stage01
echo "${src_stage_prefix} -> ${dest_stage_prefix}"

cd ${stage_controller_dir}
cp ${src_stage_prefix}.h ${dest_stage_prefix}.h
cp ${src_stage_prefix}.cpp ${dest_stage_prefix}.cpp
cp -r ${src_stage_prefix} ${dest_stage_prefix}

rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*/*/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*/*/*/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*/*/*/*/*
rename ${src_stage_prefix} ${dest_stage_prefix} ${dest_stage_prefix}/*/*/*/*/*/*/*

find . -type f -name "${dest_stage_prefix}*.*" -print0 | xargs -0 sed -i "s/${src_stage_prefix}/${dest_stage_prefix}/g"
SRC_STAGE_PREFIX=`echo ${src_stage_prefix} | tr a-z A-Z`
DEST_STAGE_PREFIX=`echo ${dest_stage_prefix} | tr a-z A-Z`
find . -type f -name "${dest_stage_prefix}*.*" -print0 | xargs -0 sed -i "s/${SRC_STAGE_PREFIX}/${DEST_STAGE_PREFIX}/g"

