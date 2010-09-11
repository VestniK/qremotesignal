cmake_minimum_required(VERSION 2.6.3)

# configurable parameters
if(WIN32)
  set(INSTALL_QMAKE_FEATURE_TO_QTDIR True CACHE BOOL "Specify if qmake custom feature file should be installed into the Qt4 installation dir.")
else(WIN32)
  set(INSTALL_QMAKE_FEATURE_TO_QTDIR False CACHE BOOL "Specify if qmake custom feature file should be installed into the Qt4 installation dir.")
endif(WIN32)

if(NOT IS_ABSOLUTE ${INCLUDE_INSTALL_DIR})
  set(ABS_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${INCLUDE_INSTALL_DIR}")
endif(NOT IS_ABSOLUTE ${INCLUDE_INSTALL_DIR_})

if(NOT IS_ABSOLUTE ${LIB_INSTALL_DIR})
  set(ABS_LIB_DIR "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
endif(NOT IS_ABSOLUTE ${LIB_INSTALL_DIR})

if(NOT IS_ABSOLUTE ${BIN_INSTALL_DIR})
  set(ABS_QRSC_PATH "${CMAKE_INSTALL_PREFIX}/${BIN_INSTALL_DIR}/qrsc")
else(NOT IS_ABSOLUTE ${BIN_INSTALL_DIR})
  set(ABS_QRSC_PATH "${BIN_INSTALL_DIR}/qrsc")
endif(NOT IS_ABSOLUTE ${BIN_INSTALL_DIR})

if(${INSTALL_QMAKE_FEATURE_TO_QTDIR})
  set(QMAKE_FEATURE_INSTALL_DIR "${QT_MKSPECS_DIR}/features")
else(${INSTALL_QMAKE_FEATURE_TO_QTDIR})
  set(QMAKE_FEATURE_INSTALL_DIR "share/qt4/mkspecs/features")
endif(${INSTALL_QMAKE_FEATURE_TO_QTDIR})

configure_file(QRemoteSignalConfig.cmake.in QRemoteSignalConfig.cmake @ONLY)
configure_file(QRemoteSignal.pc.in QRemoteSignal.pc @ONLY)
configure_file(qremotesignal.prf.in qremotesignal.prf @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignalConfig.cmake
  DESTINATION "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
  COMPONENT Devel
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignal.pc
  DESTINATION "${LIB_INSTALL_DIR}/pkgconfig"
  COMPONENT Devel
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qremotesignal.prf
  DESTINATION ${QMAKE_FEATURE_INSTALL_DIR}
  COMPONENT Devel
)
