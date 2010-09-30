cmake_minimum_required(VERSION 2.6.3)

find_package(Doxygen)
find_program(HELP2MAN "help2man")

if(DOXYGEN_FOUND AND QRS_DOCS)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(apidoc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  )
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION "share/doc/${PROJECT_NAME}"
    USE_SOURCE_PERMISSIONS
  )
endif(DOXYGEN_FOUND AND QRS_DOCS)

if(EXISTS ${HELP2MAN} AND QRS_DOCS)
  message("-- Found help2man: ${HELP2MAN}")
  add_custom_target(qrsc.1 ALL
    COMMAND ${HELP2MAN} -N -o qrsc.1 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qrsc
    DEPENDS qrsc
  )
  add_custom_target(qrsc.1.ru ALL
    COMMAND ${HELP2MAN} -L ru_RU.UTF-8 -N -o qrsc.1.ru ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qrsc
    DEPENDS qrsc
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qrsc.1
    DESTINATION "share/man/man1"
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qrsc.1.ru
    DESTINATION "share/man/ru/man1"
    RENAME qrsc.1
  )
endif(EXISTS ${HELP2MAN} AND QRS_DOCS)
