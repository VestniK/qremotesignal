set(testSRC
  errortests.cpp
)

qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})

add_executable(TestErrors ${testSRC} ${SERVICE_SRC})
target_link_libraries(TestErrors QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestErrors)
