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
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ru)
  add_custom_target(man ALL
    COMMAND ${HELP2MAN} -N -o ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_NAME:qrsc>.1 $<TARGET_FILE:qrsc>
    COMMAND ${HELP2MAN} -L ru_RU.UTF-8 -N -o ${CMAKE_CURRENT_BINARY_DIR}/ru/$<TARGET_FILE_NAME:qrsc>.1 $<TARGET_FILE:qrsc>
    DEPENDS qrsc
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_NAME:qrsc>.1
    DESTINATION "share/man/man1"
  )
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ru/$<TARGET_FILE_NAME:qrsc>.1
    DESTINATION "share/man/ru/man1"
  )
endif(EXISTS ${HELP2MAN} AND QRS_DOCS)
