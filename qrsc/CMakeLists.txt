cmake_minimum_required(VERSION 2.8.0)

#set(QT_DONT_USE_QTGUI True)
  SET( QT_DONT_USE_QTGUI    TRUE )
#set(QT_USE_QTXMLPATTERNS True)
  SET( QT_USE_QTXMLPATTERNS TRUE )

#include(${QT_USE_FILE})

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

IF (NOT Qt5Core_FOUND)
qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
qt4_add_resources(QRC_SRC ${QRC})
qt4_add_translation(QM ${TS})
ELSE()
find_package(Qt5LinguistTools REQUIRED)
qt5_add_translation(QM ${TS})
ENDIF()

configure_file(config.h.in config.h ESCAPE_QUOTES)
add_definitions(${CMAKE_CXX_COMPILE_OPTIONS_PIC})
add_executable(qrsc ${SRC} ${MOC_SRC} ${QRC_SRC} ${QM})
IF (Qt5Core_FOUND)
qt5_use_modules(qrsc XmlPatterns)
ELSE()
target_link_libraries(qrsc ${QT_LIBRARIES})
ENDIF()
add_custom_command(TARGET qrsc POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/share/i18n
  COMMAND ${CMAKE_COMMAND} -E copy ${QM} ${CMAKE_BINARY_DIR}/share/i18n/
)

install(TARGETS qrsc
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
)
install(FILES ${QM}
  DESTINATION "share/i18n"
)
