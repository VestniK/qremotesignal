cmake_minimum_required(VERSION 2.6.3)

set(QRS_QTEST_REPORTS_DIR "${CMAKE_BINARY_DIR}/reports")
macro(qrs_qtest executableTarget)
  file(MAKE_DIRECTORY ${QRS_QTEST_REPORTS_DIR})
  add_test(
    NAME ${executableTarget}
    COMMAND ${executableTarget} -xml -o ${QRS_QTEST_REPORTS_DIR}/${executableTarget}.xml
  )
endmacro(qrs_qtest)

set(ABS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/qremotesignal")
set(ABS_LIB_DIR "${CMAKE_BINARY_DIR}/qremotesignal")
get_target_property(ABS_QRSC_PATH qrsc LOCATION)
configure_file("${CMAKE_SOURCE_DIR}/tools/QRemoteSignalConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignalConfig.cmake" @ONLY)
include("${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignalConfig.cmake")

set(QT_DONT_USE_QTGUI True)
set(QT_USE_QTTEST True)
include(${QT_USE_FILE})

include_directories(${QRemoteSignal_INCLUDE_DIR})
link_directories(${QJSON_LIBRARY_DIRS})

add_subdirectory(converters)
