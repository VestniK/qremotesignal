cmake_minimum_required(VERSION 2.6.3)

set(QT_DONT_USE_QTGUI True)
set(QT_USE_QTXMLPATTERNS True)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SRC
  qrsc.cpp
  qtextserializer.cpp
  interfacedocument.cpp
  interfacecompiler.cpp
  argvparser.cpp
)
set(MOC_HDRS
  argvparser.h
  interfacedocument.h
)
set(QRC
  templates.qrc
)

qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
qt4_add_resources(QRC_SRC ${QRC})
configure_file(config.h.in config.h ESCAPE_QUOTES)

add_executable(qrsc ${SRC} ${MOC_SRC} ${QRC})
target_link_libraries(qrsc ${QT_LIBRARIES})
