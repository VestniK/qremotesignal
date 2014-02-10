cmake_minimum_required(VERSION 2.6.3)

find_package(Doxygen)
find_program(HELP2MAN "help2man")

if(DOXYGEN_FOUND AND QRS_DOCS)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(apidoc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  )
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION "share/doc/${PROJECT_NAME}${QRS_MAJOR_VERSION}"
    USE_SOURCE_PERMISSIONS
  )
endif(DOXYGEN_FOUND AND QRS_DOCS)

if(EXISTS ${HELP2MAN} AND QRS_DOCS)
  message("-- Found help2man: ${HELP2MAN}")
  get_target_property(QRSC_EXE qrsc LOCATION)
  set(qrsc_MAN_NAME qrsc${QRS_MAJOR_VERSION}.1)
  add_custom_target(${qrsc_MAN_NAME} ALL
    COMMAND ${HELP2MAN} -N -o ${qrsc_MAN_NAME} ${QRSC_EXE}
    DEPENDS qrsc
  )
  add_custom_target(${qrsc_MAN_NAME}.ru ALL
    COMMAND ${HELP2MAN} -L ru_RU.UTF-8 -N -o ${qrsc_MAN_NAME}.ru ${QRSC_EXE}
    DEPENDS qrsc
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${qrsc_MAN_NAME}
    DESTINATION "share/man/man1"
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${qrsc_MAN_NAME}.ru
    DESTINATION "share/man/ru/man1"
    RENAME ${qrsc_MAN_NAME}
  )
endif(EXISTS ${HELP2MAN} AND QRS_DOCS)
