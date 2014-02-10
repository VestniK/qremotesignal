cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  converterstests.cpp
)

add_executable(TestConverters ${testSRC})
qt5_use_modules(TestConverters Core Test)
target_link_libraries(TestConverters QRemoteSignal)

qrs_qtest(TestConverters)
