cmake_minimum_required(VERSION 2.6.3)

include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  customtypestests.cpp
  customconverters.cpp
)

qt4_generate_moc(customtypestests.cpp customtypestests.moc)
qrs_wrap_service(SERVICE_SRC customtype.xml)
qrs_wrap_client(CLIENT_SRC customtype.xml)

add_executable(TestCustomTypes ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC} customtypestests.moc)
target_link_libraries(TestCustomTypes QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestCustomTypes)
