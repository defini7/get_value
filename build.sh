#!/bin/bash

if [ ! -d "bin" ]; then
    mkdir bin
fi

gcc get_value.c main.c -o bin/out.exe -std=c11
