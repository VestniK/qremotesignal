cmake_minimum_required(VERSION 2.6.3)

set(QT_DONT_USE_QTGUI True)
include(${QT_USE_FILE})

if(${BUILD_SHARED_LIBS})
  add_definitions("-DQRS_SHARED")
endif(${BUILD_SHARED_LIBS})

set(SRC
  baseconverters.cpp
  servicesmanager.cpp
  jsonserializer.cpp
  message.cpp
  qdatastreamserializer.cpp
  devicemanager.cpp
  absservice.cpp
)
set(MOC_HDRS
  devicemanager.h
  servicesmanager.h
)

qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})

add_library(QRemoteSignal ${SRC} ${MOC_SRC})
target_link_libraries(QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARY})
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
