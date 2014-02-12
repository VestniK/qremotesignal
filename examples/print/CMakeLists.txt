cmake_minimum_required(VERSION 2.8.0)
project(PrintExample)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(QRemoteSignal2 REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${QRemoteSignal_INCLUDE_DIR})
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR On)

add_subdirectory(server)
add_subdirectory(client)
