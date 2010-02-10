set(client_SRC
    main.cpp
    client.cpp
)
set(client_MOC_HEADERS
    client.h
)
set(services
    ../services/hello.xml
)

qrs_wrap_client(clients_SRC ${services})
qt4_wrap_cpp(client_MOC ${client_MOC_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(helloClient ${client_SRC} ${client_MOC} ${clients_SRC})
target_link_libraries(helloClient ${QT_LIBRARIES} ${QRemoteSignal_LIBRARY})
