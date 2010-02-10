set(server_SRC
    main.cpp
    server.cpp
    connection.cpp
)
set(server_MOC_HEADERS
    server.h
    connection.h
)
set(services
    ../services/hello.xml
)

qrs_wrap_service(services_SRC ${services})
qt4_wrap_cpp(server_MOC ${server_MOC_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(helloServer ${server_SRC} ${server_MOC} ${services_SRC})
target_link_libraries(helloServer ${QT_LIBRARIES} ${QRemoteSignal_LIBRARY})
