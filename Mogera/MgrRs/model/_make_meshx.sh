#!/bin/bash

$(cd $(dirname $0))


for xfile_path in `find ../xfile -type f -name "_chk*"`; do
  #echo "xfile_path=${xfile_path}"
  xfile=`basename ${xfile_path}`
  echo "basename=${xfile}"
  file_name=`basename ${xfile} .x`
  file_name=`basename ${file_name} .X`
  #echo "file_name=${file_name}"
  
  cp _TTTTTTT.meshx ${file_name}.meshx
  sed -i -e "s/TTTTTTT/${file_name}/g" ${file_name}.meshx

done
