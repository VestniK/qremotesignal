cmake_minimum_required(VERSION 3.0.0)
project(QRemoteSignal2)
set(QRS_MAJOR_VERSION 2)
set(QRS_MINOR_VERSION 0)
set(QRS_PATCH_VERSION 0)
set(QRS_TWEAK_VERSION "")
set(QRS_CMAKE_PACKAGE QRS)

set(QRS_VERSION_STRING "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}.${QRS_PATCH_VERSION}${QRS_TWEAK_VERSION}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Configurable values
set(BUILD_SHARED_LIBS True CACHE BOOL "Specify to build shared or static library.")
set(QRS_DOCS True CACHE BOOL "Set to true if documentation should be generated (API-docs and man page).")
set(LIB_SUFFIX "" CACHE STRING "Define the suffix of the library directory name (32/64)." )
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}" CACHE PATH "Libraries installation directory.")
set(BIN_INSTALL_DIR "bin" CACHE PATH "Binary executebles installation directory.")
set(INCLUDE_INSTALL_DIR "include/${PROJECT_NAME}" CACHE PATH "Public header installation directory.")

# Check for libs
find_package(Qt5Core REQUIRED)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR On)

add_subdirectory(qremotesignal)
add_subdirectory(qrsc)
add_subdirectory(tools)
add_subdirectory(doc)

enable_testing()
add_subdirectory(tests)

install(EXPORT ${QRS_CMAKE_PACKAGE} NAMESPACE ${QRS_CMAKE_PACKAGE}:: DESTINATION ${LIB_INSTALL_DIR}/cmake/${QRS_CMAKE_PACKAGE})
