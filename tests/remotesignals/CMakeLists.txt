cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  remotesignaltests.cpp
)

qt4_generate_moc(remotesignaltests.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/remotesignaltests.moc"
)
qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})
qrs_wrap_client(CLIENT_SRC ${EXAMPLE_SERVICE})

add_executable(TestRemoteSignals ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC} remotesignaltests.moc)
target_link_libraries(TestRemoteSignals QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestRemoteSignals)
