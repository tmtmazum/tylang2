#!/bin/bash
rm -rf build
mkdir build
cd build
cmake -Werror=dev -Werror=deprecated -G "Unix Makefiles" ../src/
