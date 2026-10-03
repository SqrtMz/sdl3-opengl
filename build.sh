#! /usr/bin/env bash

cmake build --preset debug

if (( $? == 0 ))
then
	cmake --build build
fi

if (( $? == 0 ))
then
	mangohud build/sdl3-opengl
fi