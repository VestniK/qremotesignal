set(testSRC
  devicemanagertests.cpp
)

add_executable(TestDeviceManager ${testSRC})
target_link_libraries(TestDeviceManager QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestDeviceManager)
