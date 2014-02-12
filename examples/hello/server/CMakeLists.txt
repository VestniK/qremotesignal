set(server_SRC
    main.cpp
    server.cpp
    connection.cpp
)
set(services
    ../services/hello.xml
)

qrs_wrap_service(services_SRC ${services})

add_executable(helloServer ${server_SRC} ${services_SRC})
qt5_use_modules(helloServer Core Network)
target_link_libraries(helloServer ${QRemoteSignal_LIBRARY})
