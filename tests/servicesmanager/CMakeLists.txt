cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  servicesmanagertests.cpp
)

qt4_generate_moc(servicesmanagertests.cpp servicesmanagertests.moc)
qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})
qrs_wrap_client(CLIENT_SRC ${EXAMPLE_SERVICE})

add_executable(TestServicesManager ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC} servicesmanagertests.moc)
target_link_libraries(TestServicesManager QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestServicesManager)
