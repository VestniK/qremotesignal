set(client_SRC
    client.cpp
)
set(services
    ../services/print.xml
)

qrs_wrap_client(clients_SRC ${services})

add_executable(printClient ${client_SRC} ${clients_SRC})
qt5_use_modules(printClient Core Network)
target_link_libraries(printClient ${QRemoteSignal_LIBRARY})
