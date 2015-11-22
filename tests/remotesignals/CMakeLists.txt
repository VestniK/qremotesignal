set(testSRC
  remotesignaltests.cpp
)

qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})
qrs_wrap_client(CLIENT_SRC ${EXAMPLE_SERVICE})

add_executable(TestRemoteSignals ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
target_link_libraries(TestRemoteSignals QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestRemoteSignals)
