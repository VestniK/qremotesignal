cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  devicemanagertests.cpp
)

qt4_generate_moc(devicemanagertests.cpp devicemanagertests.moc)

add_executable(TestDeviceManager ${testSRC} devicemanagertests.moc)
target_link_libraries(TestDeviceManager QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestDeviceManager)
