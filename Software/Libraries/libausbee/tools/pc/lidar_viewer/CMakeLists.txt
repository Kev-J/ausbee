cmake_minimum_required(VERSION 2.6)

project(ausbee-lidar-viewer)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/examples/${CMAKE_BUILD_TYPE})

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/include)

#Moc generation
file(
    GLOB_RECURSE
    header_files
    src/*.h
)

QT4_WRAP_CPP(moc_files ${header_files})

file(
    GLOB_RECURSE
    source_files
    src/*
)

add_executable(
    ausbee-lidar-viewer
    ${moc_files}
    ${source_files}
)

target_link_libraries (
    ausbee-lidar-viewer
    ausbee-lidar
    ${QT_LIBRARIES}
)
