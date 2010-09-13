cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  devicemanagertests.cpp
  "${CMAKE_SOURCE_DIR}/qremotesignal/devicemanager.cpp"
)
set(MOC_HDRS
  "${CMAKE_SOURCE_DIR}/qremotesignal/devicemanager.h"
)

qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
qt4_generate_moc(devicemanagertests.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/devicemanagertests.moc"
)

add_executable(TestDeviceManager ${testSRC} ${MOC_SRC} devicemanagertests.moc)
target_link_libraries(TestDeviceManager ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestDeviceManager)
