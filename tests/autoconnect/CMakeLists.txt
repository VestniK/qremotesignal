set(testSRC
  autoconnecttests.cpp
)

qrs_wrap_service(SERVICE_SRC autoconnect.xml)
qrs_wrap_client(CLIENT_SRC autoconnect.xml)

add_executable(TestAutoconnect ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
target_link_libraries(TestAutoconnect QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestAutoconnect)
