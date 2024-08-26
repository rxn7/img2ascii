#!/bin/sh

cmake --build build/debug

if [ $? -ne 0 ]; then
	exit
fi

build/debug/img2ascii $@
