#/usr/bin/env bash
# generate
if [ -d output ]
then
  rm -r output
fi
cmake -S . -B output -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
if [ -f output/compile_commands.json ]
then
  cp output/compile_commands.json ./
else
  echo "Generate compile_commands.json failed!" >&2
fi
