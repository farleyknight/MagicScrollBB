cmake_minimum_required(VERSION 3.1)
project(PackageTest CXX)

FIND_PACKAGE(MagicScrollBB REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package("fmt")

add_executable(example example.cpp)

target_compile_features(example PUBLIC cxx_std_11)
target_include_directories(example PRIVATE ${CONAN_INCLUDE_DIRS})
target_link_libraries(example
  ${fmt_LIBS})

# CTest is a testing tool that can be used to test your project.
# enable_testing()
# add_test(NAME example
#          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#          COMMAND example)
