cmake_minimum_required(VERSION 2.8.0)

include_directories(.)

set(commonSRC
  serializerstestsuit.cpp
  messagetesttools.cpp
)

add_executable(TestJsonSerializer "json.cpp" ${commonSRC})
qt5_use_modules(TestJsonSerializer Core Test)
target_link_libraries(TestJsonSerializer QRemoteSignal)
qrs_qtest(TestJsonSerializer)

add_executable(TestQDataStreamSerializer "qdatastream.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer Core Test)
target_link_libraries(TestQDataStreamSerializer QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer)

add_executable(TestQDataStreamSerializer_3.3 "qdatastream_3.3.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_3.3 Core Test)
target_link_libraries(TestQDataStreamSerializer_3.3 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_3.3)

add_executable(TestQDataStreamSerializer_4.0 "qdatastream_4.0.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_4.0 Core Test)
target_link_libraries(TestQDataStreamSerializer_4.0 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_4.0)

add_executable(TestQDataStreamSerializer_4.2 "qdatastream_4.2.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_4.2 Core Test)
target_link_libraries(TestQDataStreamSerializer_4.2 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_4.2)

add_executable(TestQDataStreamSerializer_4.3 "qdatastream_4.3.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_4.3 Core Test)
target_link_libraries(TestQDataStreamSerializer_4.3 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_4.3)

add_executable(TestQDataStreamSerializer_4.4 "qdatastream_4.4.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_4.4 Core Test)
target_link_libraries(TestQDataStreamSerializer_4.4 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_4.4)

add_executable(TestQDataStreamSerializer_4.5 "qdatastream_4.5.cpp" ${commonSRC})
qt5_use_modules(TestQDataStreamSerializer_4.5 Core Test)
target_link_libraries(TestQDataStreamSerializer_4.5 QRemoteSignal)
qrs_qtest(TestQDataStreamSerializer_4.5)
