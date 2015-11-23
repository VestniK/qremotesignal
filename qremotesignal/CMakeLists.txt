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
#   jsonserializer.cpp
)

add_library(QRemoteSignal ${SRC})
target_link_libraries(QRemoteSignal Qt5::Core)
target_include_directories(QRemoteSignal PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
set_target_properties(QRemoteSignal PROPERTIES
  VERSION   "${QRS_MAJOR_VERSION}.${QRS_MINOR_VERSION}"
  SOVERSION "${QRS_MAJOR_VERSION}"
  OUTPUT_NAME QRemoteSignal${QRS_MAJOR_VERSION}
)

install(TARGETS QRemoteSignal EXPORT ${QRS_CMAKE_PACKAGE}
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
  INCLUDES DESTINATION "${INCLUDE_INSTALL_DIR}"
)
install(FILES
  QRemoteSignal
  absservice.h
  baseconverters.h
  servicesmanager.h
  baseexception.h
  message.h
  absmessageserializer.h
  serializationexceptions.h
  qrsexport.h
  globalserializer.h
  qdatastreamserializer.h
  templateconverters.h
DESTINATION "${INCLUDE_INSTALL_DIR}" COMPONENT Devel
)
