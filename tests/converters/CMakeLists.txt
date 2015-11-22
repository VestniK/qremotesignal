set(testSRC
  converterstests.cpp
)

add_executable(TestConverters ${testSRC})
target_link_libraries(TestConverters QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestConverters)
