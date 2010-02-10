cmake_minimum_required(VERSION 2.6.3)
project(PrintExample)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(Qt4 4.5.0 COMPONENTS QtCore QtNetwork REQUIRED)
find_package(QRemoteSignal REQUIRED)
include(${QT_USE_FILE})

include_directories(${QRemoteSignal_INCLUDE_DIR})

add_subdirectory(server)
add_subdirectory(client)