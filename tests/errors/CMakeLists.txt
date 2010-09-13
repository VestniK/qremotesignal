cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  errortests.cpp
)

qt4_generate_moc(errortests.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/errortests.moc"
)
qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})

add_executable(TestErrors ${testSRC} ${SERVICE_SRC} errortests.moc)
target_link_libraries(TestErrors QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestErrors)
