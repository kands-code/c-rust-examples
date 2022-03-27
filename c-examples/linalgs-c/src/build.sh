#/usr/bin/env bash
# build
if [ -d output ]
then
  cd output
  make
else
  ./configure.sh
  ./build.sh
fi
