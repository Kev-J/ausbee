cmake_minimum_required(VERSION 2.6)

project(ausbee-lidar-viewer)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

file(
    GLOB_RECURSE
    header_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

QT4_WRAP_CPP(moc_files ${header_files})

file(
    GLOB_RECURSE
    source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(
    ausbee-lidar-viewer
    ${moc_files}
    ${source_files}
)

target_link_libraries (
    ausbee-lidar-viewer
    ausbee_lidar
    ${QT_LIBRARIES}
)
