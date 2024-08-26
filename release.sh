#!/bin/sh

cmake --build build/release

if [ $? -ne 0 ]; then
	exit
fi

build/release/img2ascii $@
