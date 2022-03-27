#/usr/bin/env bash
# build
path=$PWD
if [[ (-d "$path"/output) && (-f "$path"/CMakeLists.txt) ]]
then
  echo "Start Build"
  cd output
  make
  rm "$path"/CMakeLists.txt
else
  # default build a lib
  "$path"/configure.sh lib
  "$path"/build.sh
fi
