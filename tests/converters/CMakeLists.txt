cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  converterstests.cpp
)

if(QT4_BUILD)
  qt4_generate_moc(converterstests.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/converterstests.moc"
  )
  set(MOC_SRC converterstests.moc)
endif(QT4_BUILD)

add_executable(TestConverters ${testSRC} ${MOC_SRC})
if(QT4_BUILD)
  target_link_libraries(TestConverters QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
else(QT4_BUILD)
  qt5_use_modules(TestConverters Core Test)
  target_link_libraries(TestConverters QRemoteSignal)
endif(QT4_BUILD)

qrs_qtest(TestConverters)
