cmake_minimum_required(VERSION 2.6.3)

set(QT_DONT_USE_QTGUI True)
include(${QT_USE_FILE})

if(${BUILD_SHARED_LIBS} STREQUAL True)
  add_definitions("-DBUILD_QRS_SHARED_LIB")
endif(${BUILD_SHARED_LIBS} STREQUAL True)

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

#install(TARGETS QRemoteSignal)
#install(FILES 
#  QRemoteSignal
#  absservice.h
#  baseconverters.h
#  servicesmanager.h
#  baseexception.h
#  message.h
#  absmessageserializer.h
#  jsonserializer.h
#  serializationexceptions.h
#  qrsexport.h
#  globalserializer.h
#  qdatastreamserializer.h
#  templateconverters.h
#DESTINATION "include/qremotesignal" COMPONENT Devel
#)
