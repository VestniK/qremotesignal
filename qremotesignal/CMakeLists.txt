cmake_minimum_required(VERSION 2.8.0)

if(BUILD_SHARED_LIBS)
  add_definitions("-DQRS_SHARED")
endif(BUILD_SHARED_LIBS)

set(SRC
  baseconverters.cpp
  servicesmanager.cpp
  message.cpp
  qdatastreamserializer.cpp
  devicemanager.cpp
  absservice.cpp
  jsonserializer.cpp
)

add_library(QRemoteSignal ${SRC})
qt5_use_modules(QRemoteSignal Core)
target_link_libraries(QRemoteSignal ${QJSON_LIBRARIES})
set_target_properties(QRemoteSignal PROPERTIES
  VERSION   "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}"
  SOVERSION "${QRS_MAJOR_VERSION}"
)

install(TARGETS QRemoteSignal
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)
install(FILES 
  QRemoteSignal
  absservice.h
  baseconverters.h
  servicesmanager.h
  baseexception.h
  message.h
  absmessageserializer.h
  jsonserializer.h
  serializationexceptions.h
  qrsexport.h
  globalserializer.h
  qdatastreamserializer.h
  templateconverters.h
DESTINATION "${INCLUDE_INSTALL_DIR}" COMPONENT Devel
)
