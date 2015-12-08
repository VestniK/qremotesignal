include_directories(.)

set(commonSRC
  serializerstestsuit.cpp
  messagetesttools.cpp
)

if (QJSON_SERIALIZER)
  add_executable(TestJsonSerializer "json.cpp" ${commonSRC})
  target_link_libraries(TestJsonSerializer QRemoteSignal Qt5::Core Qt5::Test)
  qrs_qtest(TestJsonSerializer)
endif(QJSON_SERIALIZER)

add_executable(TestQDataStreamSerializer "qdatastream.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer)

add_executable(TestQDataStreamSerializer_3.3 "qdatastream_3.3.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_3.3 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_3.3)

add_executable(TestQDataStreamSerializer_4.0 "qdatastream_4.0.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.0 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.0)

add_executable(TestQDataStreamSerializer_4.2 "qdatastream_4.2.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.2 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.2)

add_executable(TestQDataStreamSerializer_4.3 "qdatastream_4.3.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.3 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.3)

add_executable(TestQDataStreamSerializer_4.4 "qdatastream_4.4.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.4 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.4)

add_executable(TestQDataStreamSerializer_4.5 "qdatastream_4.5.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.5 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.5)

add_executable(TestQDataStreamSerializer_4.6 "qdatastream_4.6.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.6 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.6)

add_executable(TestQDataStreamSerializer_4.7 "qdatastream_4.7.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.7 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.7)

add_executable(TestQDataStreamSerializer_4.8 "qdatastream_4.8.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.8 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.8)

add_executable(TestQDataStreamSerializer_4.9 "qdatastream_4.9.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_4.9 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_4.9)

add_executable(TestQDataStreamSerializer_5.0 "qdatastream_5.0.cpp" ${commonSRC})
target_link_libraries(TestQDataStreamSerializer_5.0 QRemoteSignal Qt5::Core Qt5::Test)
qrs_qtest(TestQDataStreamSerializer_5.0)
