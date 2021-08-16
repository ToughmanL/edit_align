
cmake_minimum_required(VERSION 3.11.0)
project(EditDistance)
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall")
aux_source_directory(. DIRSRCS)
include_directories(./)
# add_library(edit SHARED edit-distance.cc)
add_executable(edit edit-distance.cc)