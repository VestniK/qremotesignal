cmake_minimum_required(VERSION 2.8.0)
project(QRemoteSignal)
set(QRS_MAJOR_VERSION 1)
set(QRS_MINOR_VERSION 3)
set(QRS_PATCH_VERSION 0)
set(QRS_TWEAK_VERSION "")

set(QRS_VERSION_STRING "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}.${QRS_PATCH_VERSION}${QRS_TWEAK_VERSION}")

option(QT4_BUILD "Force building with Qt4 even if Qt5 is found")
IF (NOT QT4_BUILD)
  FIND_PACKAGE( Qt5Core QUIET )
ELSE()
	find_package(Qt4 4.5.0 REQUIRED)
ENDIF()

IF (Qt5Core_FOUND)
  MESSAGE ("Qt5 found")

  INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
  ADD_DEFINITIONS(${Qt5Core_DEFINITIONS})

  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)

  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
ELSE()
  MESSAGE ("Qt5 not found, searching for Qt4")
  # Find Qt4
  FIND_PACKAGE( Qt4 REQUIRED )

  # Include the cmake file needed to use qt4
  INCLUDE( ${QT_USE_FILE} )

ENDIF()

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
