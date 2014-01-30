cmake_minimum_required(VERSION 2.6.3)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(testSRC
  autoconnecttests.cpp
)

if(QT4_BUILD)
  qt4_generate_moc(autoconnecttests.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/autoconnecttests.moc"
  )
  set(MOC_SRC autoconnecttests.moc)
endif(QT4_BUILD)
qrs_wrap_service(SERVICE_SRC autoconnect.xml)
qrs_wrap_client(CLIENT_SRC autoconnect.xml)

add_executable(TestAutoconnect ${testSRC} ${SERVICE_SRC} ${CLIENT_SRC}  ${MOC_SRC})
if(QT4_BUILD)
  target_link_libraries(TestAutoconnect QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
else(QT4_BUILD)
  qt5_use_modules(TestAutoconnect Core Test)
  target_link_libraries(TestAutoconnect QRemoteSignal)
endif(QT4_BUILD)

qrs_qtest(TestAutoconnect)
