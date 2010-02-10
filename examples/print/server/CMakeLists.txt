set(server_SRC
    main.cpp
    server.cpp
)
set(server_MOC_HEADERS
    server.h
)
set(services
    ../services/print.xml
)

qrs_wrap_service(services_SRC ${services})
qt4_wrap_cpp(server_MOC ${server_MOC_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(printServer ${server_SRC} ${server_MOC} ${services_SRC})
target_link_libraries(printServer ${QT_LIBRARIES} ${QRemoteSignal_LIBRARY})
