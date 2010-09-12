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
set(TS
  qrsc-ru.ts
)

qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
qt4_add_resources(QRC_SRC ${QRC})
qt4_add_translation(QM ${TS})
configure_file(config.h.in config.h ESCAPE_QUOTES)

add_executable(qrsc ${SRC} ${MOC_SRC} ${QRC} ${QM})
target_link_libraries(qrsc ${QT_LIBRARIES})

install(TARGETS qrsc
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
)
install(FILES ${QM}
  DESTINATION "share/i18n"
)
