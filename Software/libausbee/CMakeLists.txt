cmake_minimum_required(VERSION 2.6)

# Project configuration

project(libausbee)

set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

# AUSBEE-Lidar library

include_directories(include/AUSBEE)

file(
    GLOB_RECURSE
    lidar_source_files
    src/lidar/*
    src/lidar/include/*
)

add_library(
    ausbee-lidar
    SHARED
    ${lidar_source_files}
)

# AUSBEE Examples

add_subdirectory(examples/pc/lidar_viewer)

# Documentation

find_package(Doxygen)
if(DOXYGEN_FOUND)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile @ONLY)

    add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
    COMMENT "Generating API documentation with Doxygen" VERBATIM)

endif(DOXYGEN_FOUND)
