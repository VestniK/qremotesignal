cmake_minimum_required(VERSION 2.8.0)

set(testSRC
  remotesignaltests.cpp
)

qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})
qrs_wrap_client(CLIENT_SRC ${EXAMPLE_SERVICE})

add_executable(TestRemoteSignals ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
qt5_use_modules(TestRemoteSignals Core Test)
target_link_libraries(TestRemoteSignals QRemoteSignal)

qrs_qtest(TestRemoteSignals)
