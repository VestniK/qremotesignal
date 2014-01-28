cmake_minimum_required(VERSION 2.8.0)
project(QRemoteSignal)
set(QRS_MAJOR_VERSION 1)
set(QRS_MINOR_VERSION 3)
set(QRS_PATCH_VERSION 0)
set(QRS_TWEAK_VERSION "")

set(QRS_VERSION_STRING "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}.${QRS_PATCH_VERSION}${QRS_TWEAK_VERSION}")

ELSE()
	find_package(Qt4 4.5.0 REQUIRED)
# Configurable values
set(QT4_BUILD False CACHE BOOL "Force building with Qt4 even if Qt5 is found")
set(BUILD_SHARED_LIBS True CACHE BOOL "Specify to build shared or static library.")
set(QRS_DOCS True CACHE BOOL "Set to true if documentation should be generated (API-docs and man page).")
set(QRS_TEST False CACHE BOOL "Specifies if tests should be compiled and executed or not")
set(LIB_SUFFIX "" CACHE STRING "Define the suffix of the library directory name (32/64)." )
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}" CACHE PATH "Libraries installation directory.")
set(BIN_INSTALL_DIR "bin" CACHE PATH "Binary executebles installation directory.")
set(INCLUDE_INSTALL_DIR "include/${PROJECT_NAME}" CACHE PATH "Public header installation directory.")

# Check for Qt
if(NOT QT4_BUILD)
  find_package(Qt5Core QUIET)
endif()

if(Qt5Core_FOUND)
  message(STATUS "Qt5 found")

  include_directories(${Qt5Core_INCLUDE_DIRS})
  add_definitions(${Qt5Core_DEFINITIONS})
  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
else(Qt5Core_FOUND)
  message(STATUS "Qt5 not found, searching for Qt4")
  find_package(Qt4 4.5.0 REQUIRED)
  set(QT4_BUILD True)
endif(Qt5Core_FOUND)
# Rest of the dependencies
find_package(QJSON 0.6.3 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR On)

add_subdirectory(qremotesignal)
add_subdirectory(qrsc)
add_subdirectory(tools)
add_subdirectory(doc)
if(QRS_TEST)
  enable_testing()
  add_subdirectory(tests)
endif(QRS_TEST)
