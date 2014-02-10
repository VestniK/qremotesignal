cmake_minimum_required(VERSION 2.8.0)

include_directories(.)

set(testSRC
  customtypestests.cpp
  customconverters.cpp
)

qrs_wrap_service(SERVICE_SRC customtype.xml)
qrs_wrap_client(CLIENT_SRC customtype.xml)

add_executable(TestCustomTypes ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC})
qt5_use_modules(TestCustomTypes Core Test)
target_link_libraries(TestCustomTypes QRemoteSignal)

qrs_qtest(TestCustomTypes)
