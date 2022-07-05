cur=$(pwd)

if [[ $# != 1 ]]
then
    cmake -B build \
          -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
          -G "Unix Makefiles" # linux plantform
          # -G "Ninja" # windows plantform
    if [[ -f "$cur/build/compile_commands.json" ]]
    then
        cp "$cur/build/compile_commands.json" ./
        cmake --build build
    else
        echo "Error in configuration!" >&2
    fi
else
    case "$1" in
        "clean")
            if [[ -d "$cur/.cache" ]]
            then
                rm "$cur/.cache" -r
            fi
            if [[ -d "$cur/build" ]]
            then
                rm "$cur/build" -r
            fi
            ;;
        *)
            echo "wrong command!" >&2
    esac
fi