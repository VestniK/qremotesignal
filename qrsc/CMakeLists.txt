cmake_minimum_required(VERSION 2.8.0)

set(QT_DONT_USE_QTGUI True)
set(QT_USE_QTXMLPATTERNS True)
if(QT4_BUILD)
  include(${QT_USE_FILE})
endif(QT4_BUILD)

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
  qrsc${QRS_MAJOR_VERSION}-ru.ts
)

if(QT4_BUILD)
  qt4_wrap_cpp(MOC_SRC ${MOC_HDRS})
  qt4_add_resources(QRC_SRC ${QRC})
  qt4_add_translation(QM ${TS})
else(QT4_BUILD)
  find_package(Qt5LinguistTools REQUIRED)
  qt5_add_translation(QM ${TS})
  qt5_add_resources(QRC_SRC ${QRC})
endif(QT4_BUILD)

configure_file(config.h.in config.h ESCAPE_QUOTES)
add_definitions(${CMAKE_CXX_COMPILE_OPTIONS_PIC})
add_executable(qrsc ${SRC} ${MOC_SRC} ${QRC_SRC} ${QM})
if(NOT QT4_BUILD)
  qt5_use_modules(qrsc XmlPatterns)
else(NOT QT4_BUILD)
  target_link_libraries(qrsc ${QT_LIBRARIES})
endif(NOT QT4_BUILD)
add_custom_command(TARGET qrsc POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/share/i18n
  COMMAND ${CMAKE_COMMAND} -E copy ${QM} ${CMAKE_BINARY_DIR}/share/i18n/
)
set_target_properties(qrsc PROPERTIES
  OUTPUT_NAME qrsc${QRS_MAJOR_VERSION}
)

install(TARGETS qrsc
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
)
install(FILES ${QM}
  DESTINATION "share/i18n"
)
