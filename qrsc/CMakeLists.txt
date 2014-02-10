cmake_minimum_required(VERSION 2.8.0)

set(SRC
  qrsc.cpp
  qtextserializer.cpp
  interfacedocument.cpp
  interfacecompiler.cpp
  argvparser.cpp
)
set(QRC
  templates.qrc
)
set(TS
  qrsc${QRS_MAJOR_VERSION}-ru.ts
)

find_package(Qt5LinguistTools REQUIRED)
qt5_add_translation(QM ${TS})
qt5_add_resources(QRC_SRC ${QRC})

configure_file(config.h.in config.h ESCAPE_QUOTES)
add_definitions(${CMAKE_CXX_COMPILE_OPTIONS_PIC})
add_executable(qrsc ${SRC} ${QRC_SRC} ${QM})
qt5_use_modules(qrsc XmlPatterns)
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
