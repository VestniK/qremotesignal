cmake_minimum_required(VERSION 2.6.3)

set(QT_DONT_USE_QTGUI True)
if(QT4_BUILD)
  include(${QT_USE_FILE})
endif(QT4_BUILD)

include_directories(${QJSON_INCLUDE_DIR})
# needed to be able to include QJson headers like qjson/header.h
include_directories("${QJSON_INCLUDE_DIR}/..")
link_directories(${QJSON_LIBRARY_DIRS})

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
)

if(QT4_BUILD)
  # use QJson implemantation of JSON serializer in case of Qt4
  list(APPEND SRC qjsonserializer.cpp)
else(QT4_BUILD)
  list(APPEND SRC jsonserializer.cpp)
endif(QT4_BUILD)

set(MOC_HDRS
  devicemanager.h
  servicesmanager.h
)

if(QT4_BUILD)
  qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
endif(QT4_BUILD)

add_library(QRemoteSignal ${SRC} ${MOC_SRC})
if(NOT QT4_BUILD)
  qt5_use_modules(QRemoteSignal Core)
else(NOT QT4_BUILD)
  target_link_libraries(QRemoteSignal ${QT_LIBRARIES} ${QJSON_LIBRARIES})
endif(NOT QT4_BUILD)

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
