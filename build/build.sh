#!/bin/bash

if [ ! -d "bin" ]; then
    mkdir bin
fi

clang src/get_value.c examples/main.c -o bin/out
