cmake_minimum_required(VERSION 3.1)

project(csg_cpp_command)

set(CMAKE_BUILD_TYPE Release)

if(UNIX)
  add_definitions("-std=c++11 -Wall")
elseif(MSVC)
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

# Eigen.
include_directories(lib/eigen-3.3.4)
# gco.
include_directories(lib/gco-v3.0)
add_subdirectory(lib/gco-v3.0)
# CGAL.
find_package(CGAL QUIET)
if(CGAL_FOUND)
  include(${CGAL_USE_FILE})
  # CGAL include folder.
  set(CGAL_INCLUDE_DIR "${CGAL_DIR}/include")
  include_directories(${CGAL_INCLUDE_DIR})
endif()

set(SRC_DIR "src/")
include_directories(${SRC_DIR})
file(GLOB_RECURSE CPP_HEADERS ${SRC_DIR}*.h)
file(GLOB_RECURSE CPP_FILES ${SRC_DIR}*.cpp)
add_executable(csg_cpp_command ${CPP_FILES} ${CPP_HEADERS})
target_link_libraries(csg_cpp_command gco)
