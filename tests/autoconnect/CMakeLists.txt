cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  autoconnecttests.cpp
)

qt4_generate_moc(autoconnecttests.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/autoconnecttests.moc"
)
qrs_wrap_service(SERVICE_SRC autoconnect.xml)
qrs_wrap_client(CLIENT_SRC autoconnect.xml)

add_executable(TestAutoconnect ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC} autoconnecttests.moc)
target_link_libraries(TestAutoconnect QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestAutoconnect)
