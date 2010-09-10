cmake_minimum_required(VERSION 2.6.3)
project(QRemoteSignal)
set(QRS_MAJOR_VERSION 1)
set(QRS_MINOR_VERSION 2)
set(QRS_PATCH_VERSION 0)
set(QRS_TWEAK_VERSION ".svn")

set(QRS_VERSION_STRING "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}.${QRS_PATCH_VERSION}${QRS_TWEAK_VERSION}")

find_package(Qt4 4.5.0 REQUIRED)
find_package(QJSON 0.6.3 REQUIRED)

include_directories(${QJSON_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Configurable values
set(BUILD_SHARED_LIBS True CACHE BOOL "Specify to build shared or static library.")
set(LIB_SUFFIX "" CACHE STRING "Define the suffix of the library directory name (32/64)." )
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}" CACHE PATH "Libraries installation directory.")
set(BIN_INSTALL_DIR "bin" CACHE PATH "Binary executebles installation directory.")
set(INCLUDE_INSTALL_DIR "include" CACHE PATH "Public header installation directory.")

add_subdirectory(qremotesignal)
add_subdirectory(qrsc)
