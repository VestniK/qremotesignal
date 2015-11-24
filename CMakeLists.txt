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
option(BUILD_SHARED_LIBS "Specify to build shared or static library." ON)
option(QRS_DOCS "Set to true if documentation should be generated (API-docs and man page)." ON)
option(LIB_SUFFIX "Define the suffix of the library directory name (32/64)." "")
option(LIB_INSTALL_DIR "Libraries installation directory." "lib${LIB_SUFFIX}")
option(BIN_INSTALL_DIR "Binary executebles installation directory." "bin")
option(INCLUDE_INSTALL_DIR "Public header installation directory." "include/${PROJECT_NAME}")
option(QJSON_SERIALIZER "Build QJson serializer (kkeps protocol compatibility with 1.x versions)" ON)

add_definitions(-Wall -Werror -std=c++11)

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
