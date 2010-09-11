cmake_minimum_required(VERSION 2.6.3)

find_package(Doxygen)
find_program(HELP2MAN "help2man")

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in Doxyfile @ONLY)
  add_custom_target(apidoc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  )
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION "share/doc/${PROJECT_NAME}"
    USE_SOURCE_PERMISSIONS
  )
endif(DOXYGEN_FOUND)

if(NOT ${HELP2MAN} STREQUAL "HELP2MAN-NOTFOUND")
  message("-- Found help2man: ${HELP2MAN}")
endif()
