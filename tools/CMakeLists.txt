cmake_minimum_required(VERSION 3.0.0)

configure_file(PackageConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${QRS_CMAKE_PACKAGE}Config.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${QRS_CMAKE_PACKAGE}Config.cmake
  DESTINATION "${LIB_INSTALL_DIR}/cmake/${QRS_CMAKE_PACKAGE}"
  COMPONENT Devel
)
install(FILES QRemoteSignalCompiler.cmake
  DESTINATION "${LIB_INSTALL_DIR}/cmake/${QRS_CMAKE_PACKAGE}"
  COMPONENT Devel
)

# TODO: Restore QMake and pkg-config support
# configurable parameters
# if(WIN32)
#   set(INSTALL_QMAKE_FEATURE_TO_QTDIR True CACHE BOOL "Specify if qmake custom feature file should be installed into the Qt4 installation dir.")
# else(WIN32)
#   set(INSTALL_QMAKE_FEATURE_TO_QTDIR False CACHE BOOL "Specify if qmake custom feature file should be installed into the Qt4 installation dir.")
# endif(WIN32)
#
# if(INSTALL_QMAKE_FEATURE_TO_QTDIR)
#   set(QMAKE_FEATURE_INSTALL_DIR "${QT_MKSPECS_DIR}/features") # TODO: test and fix
# else(INSTALL_QMAKE_FEATURE_TO_QTDIR)
#   set(QMAKE_FEATURE_INSTALL_DIR "share/qt5/mkspecs/features")
# endif(INSTALL_QMAKE_FEATURE_TO_QTDIR)
#
#configure_file(QRemoteSignal.pc.in ${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignal${QRS_MAJOR_VERSION}.pc @ONLY)
#configure_file(qremotesignal.prf.in ${CMAKE_CURRENT_BINARY_DIR}/qremotesignal${QRS_MAJOR_VERSION}.prf @ONLY)
#
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QRemoteSignal${QRS_MAJOR_VERSION}.pc
#   DESTINATION "${LIB_INSTALL_DIR}/pkgconfig"
#   COMPONENT Devel
# )
# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qremotesignal${QRS_MAJOR_VERSION}.prf
#   DESTINATION ${QMAKE_FEATURE_INSTALL_DIR}
#   COMPONENT Devel
# )
