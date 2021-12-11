cmake_minimum_required(VERSION 3.1)
project(MagicScrollBB CXX)

set(MAGIC_SCROLL_BB_VERSION 0.2.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
