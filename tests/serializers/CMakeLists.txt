cmake_minimum_required(VERSION 2.6.3)

include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(commonSRC
  serializerstestsuit.cpp
  messagetesttools.cpp
)
set(MOC_HDRS
  serializerstestsuit.h
)

qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})

add_executable(TestJsonSerializer "json.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestJsonSerializer QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestJsonSerializer)

add_executable(TestQDataStreamSerializer "qdatastream.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer)

add_executable(TestQDataStreamSerializer_3.3 "qdatastream_3.3.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_3.3 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_3.3)

add_executable(TestQDataStreamSerializer_4.0 "qdatastream_4.0.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_4.0 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_4.0)

add_executable(TestQDataStreamSerializer_4.2 "qdatastream_4.2.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_4.2 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_4.2)

add_executable(TestQDataStreamSerializer_4.3 "qdatastream_4.3.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_4.3 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_4.3)

add_executable(TestQDataStreamSerializer_4.4 "qdatastream_4.4.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_4.4 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_4.4)

add_executable(TestQDataStreamSerializer_4.5 "qdatastream_4.5.cpp" ${commonSRC} ${MOC_SRC})
target_link_libraries(TestQDataStreamSerializer_4.5 QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
qrs_qtest(TestQDataStreamSerializer_4.5)
