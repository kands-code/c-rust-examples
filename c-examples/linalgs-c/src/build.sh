#/usr/bin/env bash
# build
path=$PWD

function prog_exist {
  local ret="0"
  command -v "$1" > /dev/null || ret="1"
  echo ${ret}
}

if [ $# -eq 0 ]
then
  if [[ (-d "$path"/../output) && (-f "$path"/CMakeLists.txt) ]]
  then
    echo "Start Build"
    cmake --build ../output
    rm "$path"/CMakeLists.txt
  else
    # default build a lib
    "$path"/configure.sh lib linux
    "$path"/build.sh
  fi
else
  case "$1" in
    "clean")
      rm -r ../output
      rm compile_commands.json
      if [ -d .cache ]
      then
        rm -r .cache
      fi
      ;;
    *)
      echo "Wrong subcommand!" >&2
      echo "command: clean" >&2
      exit
      ;;
  esac
fi
