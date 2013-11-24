cmake_minimum_required(VERSION 2.6)

project(libausbee-examples)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/include)

##############
# lidar-viewer

#Moc generation
file(
	GLOB_RECURSE
        lidar_viewer_header_files
	tools/pc/lidar_viewer/src/*.h
)

QT4_WRAP_CPP(lidar_viewer_moc_files ${lidar_viewer_header_files})

file(
    GLOB_RECURSE
    ausbee_source_files
    src/*
)

file(
    GLOB_RECURSE
    ausbee_lidar_source_files
    src/lidar/*
)

file(
    GLOB_RECURSE
    lidar_viewer_source_files
    tools/pc/lidar_viewer/src/*
)

add_executable(
    ausbee-lidar-viewer
    ${lidar_viewer_moc_files}
    ${ausbee_lidar_source_files}
    ${lidar_viewer_source_files}
)

target_link_libraries (
    ausbee-lidar-viewer
    ${QT_LIBRARIES}
)
