set(client_SRC
    main.cpp
    client.cpp
)
set(services
    ../services/hello.xml
)

qrs_wrap_client(clients_SRC ${services})

add_executable(helloClient ${client_SRC} ${clients_SRC})
qt5_use_modules(helloClient Core Network)
target_link_libraries(helloClient ${QRemoteSignal_LIBRARY})
