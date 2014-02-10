cmake_minimum_required(VERSION 2.6.3)

# Defining simplified add test macro
set(QRS_QTEST_REPORTS_DIR "${CMAKE_BINARY_DIR}/reports")
macro(qrs_qtest executableTarget)
  file(MAKE_DIRECTORY ${QRS_QTEST_REPORTS_DIR})
  add_test(
    NAME ${executableTarget}
    COMMAND ${executableTarget} -xml -o ${QRS_QTEST_REPORTS_DIR}/${executableTarget}.xml
  )
endmacro(qrs_qtest)

# Creating fake configuration to use with tests
set(ABS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/qremotesignal")
set(ABS_LIB_DIR "${CMAKE_BINARY_DIR}/qremotesignal")

get_target_property(LIB_NAME QRemoteSignal LOCATION)
get_filename_component(LIB_NAME  ${LIB_NAME} NAME)

get_target_property(ABS_QRSC_PATH qrsc LOCATION)

configure_file("${CMAKE_SOURCE_DIR}/tools/QRemoteSignalConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignalConfig.cmake" @ONLY
)
include("${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignalConfig.cmake")

# Setting up libraries
set(QT_DONT_USE_QTGUI True)
set(QT_USE_QTTEST True)
if (QT4_BUILD)
  include(${QT_USE_FILE})
  link_directories(${QJSON_LIBRARY_DIRS})
endif(QT4_BUILD)
include_directories(${QRemoteSignal_INCLUDE_DIR})

set(EXAMPLE_SERVICE "${CMAKE_CURRENT_SOURCE_DIR}/example.xml")

# Iterating through the test subdirectories
add_subdirectory(converters)
add_subdirectory(autoconnect)
# add_subdirectory(customtypes)
# add_subdirectory(devicemanager)
# add_subdirectory(errors)
# add_subdirectory(remotesignals)
# add_subdirectory(serializers)
# add_subdirectory(servicesmanager)
