#/usr/bin/env bash
# generate
path=$PWD
if [[ -z "$@" ]]
then
  echo "Please give an option!" >&2
  exit
fi

case ${1} in
  "exe")
    cp "$path"/CMakeLists-exe.txt "$path"/CMakeLists.txt
    ;;
  "lib" )
    cp "$path"/CMakeLists-lib.txt "$path"/CMakeLists.txt
    ;;
  *)
    echo "Wrong Parameter!" >&2
    exit
    ;;
esac

if [[ -d "$path"/output ]]
then
  rm -r "$path"/output
fi
cmake -S . -B output -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -Wdev -Wdeprecated
if [ -f "$path"/output/compile_commands.json ]
then
  cp "$path"/output/compile_commands.json "$path"/
else
  echo "Generate compile_commands.json failed!" >&2
fi
