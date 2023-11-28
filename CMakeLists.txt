########################################################################################################################
### CONVEX HULL APPLICATION
########################################################################################################################

cmake_minimum_required(VERSION 3.22)

########################################################################################################################
### PROJECT DESCRIPTION AND META INFO
########################################################################################################################

set(CONVEX_HULL_PROJECT_NAME           "convexHull")
set(CONVEX_HULL_PROJECT_DESCRIPTION    "Tool to create solutions for convex hull of size N")

########################################################################################################################
### DECLARE PROJECT
########################################################################################################################

project(${CONVEX_HULL_PROJECT_NAME})

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fopenmp")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

INCLUDE(FindPkgConfig)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(SDL2_LIBRARIES "/Library/Frameworks/SDL2.framework/SDL2")
    set(SDL2_INCLUDE_DIRS "/Library/Frameworks/SDL2.framework/Headers")
else()
    find_package(SDL2 REQUIRED)
endif()

set(CONVEX_HULL_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CONVEX_HULL_INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(CONVEX_HULL_TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(tests)
