include_directories(.)

set(testSRC
  customtypestests.cpp
  customconverters.cpp
)

qrs_wrap_service(SERVICE_SRC customtype.xml)
qrs_wrap_client(CLIENT_SRC customtype.xml)

add_executable(TestCustomTypes ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
target_link_libraries(TestCustomTypes QRemoteSignal Qt5::Core Qt5::Test)

qrs_qtest(TestCustomTypes)
