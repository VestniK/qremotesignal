cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  autoconnecttests.cpp
)

qrs_wrap_service(SERVICE_SRC autoconnect.xml)
qrs_wrap_client(CLIENT_SRC autoconnect.xml)

add_executable(TestAutoconnect ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
qt5_use_modules(TestAutoconnect Core Test)
target_link_libraries(TestAutoconnect QRemoteSignal)

qrs_qtest(TestAutoconnect)
