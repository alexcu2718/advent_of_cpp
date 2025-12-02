#! /usr/bin/env bash
set -e

rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)

cd ..
ln -sf build/compile_commands.json .

clang-tidy -p . -checks='performance-*' ./src/*.cpp