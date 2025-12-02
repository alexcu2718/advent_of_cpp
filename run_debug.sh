#! /usr/bin/env bash

cd "$(dirname "$0")" || exit

./build_debug.sh


result=$(find . -maxdepth 1 -type f -executable ! -name "*.sh" ! -iname "*.sh")

echo -e  "\n\n\n"
"./$result"
