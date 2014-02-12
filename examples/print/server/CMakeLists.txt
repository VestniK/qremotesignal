set(server_SRC
    main.cpp
    server.cpp
)
set(services
    ../services/print.xml
)

qrs_wrap_service(services_SRC ${services})

add_executable(printServer ${server_SRC} ${services_SRC})
qt5_use_modules(printServer Core Network)
target_link_libraries(printServer ${QRemoteSignal_LIBRARY})
