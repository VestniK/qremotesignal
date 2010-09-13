cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  converterstests.cpp
)

qt4_generate_moc(converterstests.cpp
  "${CMAKE_CURRENT_BINARY_DIR}/converterstests.moc"
)

add_executable(TestConverters ${testSRC} converterstests.moc)
target_link_libraries(TestConverters QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})

qrs_qtest(TestConverters)
