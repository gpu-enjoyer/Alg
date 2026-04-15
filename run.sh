#!/bin/bash
set -eu

ORIG_DIR="$(pwd)"
PROJ_DIR="$(cd "$(dirname "$0")" && pwd)"

kill() {
    echo "ERROR: $*" >&2
    rm -rf .build
    cd "$ORIG_DIR"
    exit 1
}

success() {
    rm -rf .build
    cd "$ORIG_DIR"
    echo "$(basename "$0") DONE"
    exit 0
}

[[ $# -lt 1 ]] && kill "usage: run.sh \"dir_with_alg.cpp\""
EXE_DIR="$PROJ_DIR/$1"

[[ ! -d "$EXE_DIR" ]] && kill "$EXE_DIR directory does not exist"
cd "$EXE_DIR"

[[ ! -d ".build" ]] && mkdir ".build"

g++ -std=c++20 alg.cpp \
    -o .build/alg || kill "$PROJ_DIR/alg.cpp not compiled"

.build/alg || kill "$PROJ_DIR/.build/alg bad execution"

success
