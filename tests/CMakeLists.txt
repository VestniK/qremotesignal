# Defining simplified add test macro
find_package(Qt5Test REQUIRED)
set(QRS_QTEST_REPORTS_DIR "${CMAKE_BINARY_DIR}/reports")
macro(qrs_qtest executableTarget)
  file(MAKE_DIRECTORY ${QRS_QTEST_REPORTS_DIR})
  add_test(
    NAME ${executableTarget}
    COMMAND ${executableTarget} -xml -o ${QRS_QTEST_REPORTS_DIR}/${executableTarget}.xml
  )
endmacro(qrs_qtest)

include(${CMAKE_SOURCE_DIR}/tools/QRemoteSignalCompiler.cmake)
include_directories(${CMAKE_SOURCE_DIR}/qremotesignal) # TODO: use target properties to do this
set(EXAMPLE_SERVICE "${CMAKE_CURRENT_SOURCE_DIR}/example.xml")

# Iterating through the test subdirectories
add_subdirectory(converters)
add_subdirectory(autoconnect)
add_subdirectory(customtypes)
add_subdirectory(devicemanager)
add_subdirectory(errors)
add_subdirectory(remotesignals)
add_subdirectory(serializers)
#add_subdirectory(servicesmanager)
