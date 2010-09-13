cmake_minimum_required(VERSION 2.8.0)
project(QRemoteSignal)
set(QRS_MAJOR_VERSION 1)
set(QRS_MINOR_VERSION 2)
set(QRS_PATCH_VERSION 0)
set(QRS_TWEAK_VERSION ".git")

set(QRS_VERSION_STRING "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}.${QRS_PATCH_VERSION}${QRS_TWEAK_VERSION}")

find_package(Qt4 4.5.0 REQUIRED)
find_package(QJSON 0.6.3 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Configurable values
set(BUILD_SHARED_LIBS True CACHE BOOL "Specify to build shared or static library.")
set(QRS_DOCS True CACHE BOOL "Set to true if documentation should be generated (API-docs and man page).")
set(QRS_TEST False CACHE BOOL "Specifies if tests should be compiled and executed or not")
set(LIB_SUFFIX "" CACHE STRING "Define the suffix of the library directory name (32/64)." )
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}" CACHE PATH "Libraries installation directory.")
set(BIN_INSTALL_DIR "bin" CACHE PATH "Binary executebles installation directory.")
set(INCLUDE_INSTALL_DIR "include/${PROJECT_NAME}" CACHE PATH "Public header installation directory.")

add_subdirectory(qremotesignal)
add_subdirectory(qrsc)
add_subdirectory(tools)
add_subdirectory(doc)
if(QRS_TEST)
  enable_testing()
  add_subdirectory(tests)
endif(QRS_TEST)
