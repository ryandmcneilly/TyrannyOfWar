#!/bin/bash
set -e

INCLUDE="-I/opt/raylib/src -I./incl/"
LIBS="-L/opt/raylib/src"
CFLAGS="-Wall -Wpedantic -Wextra"
LDFLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"
DEBUGGING="-g"

gcc ./src/*.c -o main -I./incl/ $INCLUDE $LIBS $CFLAGS $LDFLAGS $DEBUGGING
if [ "$1" == "debug" ]; then
    gdb ./main
elif [ "$1" != "compile" ]; then
    ./main
fi
