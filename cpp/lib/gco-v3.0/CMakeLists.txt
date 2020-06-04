project(gco)
cmake_minimum_required(VERSION 3.1)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(lib_srcs
    GCoptimization.cpp
    GCoptimization.h
    LinkedBlockList.cpp
    LinkedBlockList.h
    block.h
    energy.h
    graph.h
    )

set(example_srcs
    example.cpp)

add_library(gco ${lib_srcs})
add_executable(example ${example_srcs})
target_link_libraries(example gco)
