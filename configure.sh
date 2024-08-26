#!/bin/sh

COMMON_FLAGS="-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_C_COMPILER=/usr/bin/clang -GNinja ."

cmake -Bbuild/debug -DCMAKE_BUILD_TYPE=Debug $COMMON_FLAGS
cmake -Bbuild/release -DCMAKE_BUILD_TYPE=Release $COMMON_FLAGS
