include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  servicesmanagertests.cpp
)

qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})
qrs_wrap_client(CLIENT_SRC ${EXAMPLE_SERVICE})

add_executable(TestServicesManager ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
target_link_libraries(TestServicesManager QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestServicesManager)
