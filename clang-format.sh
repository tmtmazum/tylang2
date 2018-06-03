#!/bin/bash
clang-format-6.0 -style=file -i `find src | egrep "*.cpp$|*.h$"`
