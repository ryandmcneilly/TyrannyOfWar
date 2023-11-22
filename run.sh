#!/bin/bash
set -e

INCLUDE="-I/opt/raylib/src"
LIBS="-L/opt/raylib/src"
CFLAGS="-Wall -Wpedantic -Wextra"
LDFLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt"
gcc main.c -o main $INCLUDE $LIBS $CFLAGS $LDFLAGS
if [ "$1" != "compile" ]; then
    ./main
fi
