cmake_minimum_required(VERSION 2.6)

project(libausbee-examples)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

# AUSBEE lidar library
file(
    GLOB_RECURSE
    ausbee_lidar_source_files
    ${CMAKE_SOURCE_DIR}/src/lidar/*
)

add_library(ausbee_lidar STATIC ${ausbee_lidar_source_files})

###################
# Tools

# ausbee_lidar_viewer
add_subdirectory(${CMAKE_SOURCE_DIR}/tools/pc/lidar_viewer)
