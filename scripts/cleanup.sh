#!/bin/zsh

# First clean up Conan

rm conan.lock
rm conanbuildinfo.*
rm conaninfo.txt
rm graph_info.json

# Next clean up CMake
rm cmake_install.cmake
rm -rf CMakeFiles
rm CMakeCache.txt
rm Makefile
