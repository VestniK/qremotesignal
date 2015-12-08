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

set(PUB_HDR
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
)

if (QJSON_SERIALIZER)
  find_package(QJSON-qt5 QUIET)
  if (NOT QJSON-qt5_FOUND)
    include(ExternalProject)
    ExternalProject_Add(QJson
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/QJson
      GIT_REPOSITORY git@github.com:flavio/qjson.git
      GIT_TAG master
      SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/QJson/repo
      BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/QJson/build
      CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS:bool=Off -DCMAKE_INSTALL_PREFIX:path=${CMAKE_CURRENT_BINARY_DIR}/QJson/install
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/QJson/install
    )
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/QJson/install)
  endif(NOT QJSON-qt5_FOUND)
  find_package(QJSON-qt5 REQUIRED)

  list(APPEND SRC jsonserializer.cpp)
  list(APPEND PUB_HDR jsonserializer.h)
endif (QJSON_SERIALIZER)

add_library(QRemoteSignal ${SRC})
target_link_libraries(QRemoteSignal Qt5::Core)
if (QJSON_SERIALIZER)
  target_link_libraries(QRemoteSignal qjson-qt5)
  target_compile_definitions(QRemoteSignal PUBLIC -DQJSON_SERIALIZER)
endif(QJSON_SERIALIZER)
target_include_directories(QRemoteSignal PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)
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
install(FILES ${PUB_HDR}
  DESTINATION "${INCLUDE_INSTALL_DIR}" COMPONENT Devel
)
