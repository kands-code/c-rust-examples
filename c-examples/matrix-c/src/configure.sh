#/usr/bin/env bash
# generate
path=$PWD
if [[ -z "$@" ]]
then
  echo "Please give an option!" >&2
  exit
elif [[ $# != 1 ]]
then
  echo "usage: ./configure.sh [platform]"
  echo "platform: win or linux"
  exit
fi

case "$1" in
  "win")
    gen="MinGW Makefiles"
    ;;
  "linux")
    gen="Unix Makefiles"
    ;;
  *)
    echo "Wrong Platform!" >&2
    exit
    ;;
esac

if [[ -d "$path"/../output ]]
then
  rm -r "$path"/../output
fi
cmake -S . -B ../output -DCMAKE_BUILD_TYPE=Debug \
                        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
                        -Wdev -Wdeprecated \
                        -G "$gen"
if [ -f "$path"/../output/compile_commands.json ]
then
  cp "$path"/../output/compile_commands.json "$path"/
else
  echo "Generate compile_commands.json failed!" >&2
fi
