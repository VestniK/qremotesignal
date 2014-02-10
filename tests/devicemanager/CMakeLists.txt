cmake_minimum_required(VERSION 2.8.0)

set(testSRC
  devicemanagertests.cpp
)

add_executable(TestDeviceManager ${testSRC})
qt5_use_modules(TestDeviceManager Core Test)
target_link_libraries(TestDeviceManager QRemoteSignal)

qrs_qtest(TestDeviceManager)
