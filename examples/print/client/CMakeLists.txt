set(client_SRC
    client.cpp
)
set(services
    ../services/print.xml
)

qrs_wrap_client(clients_SRC ${services})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(printClient ${client_SRC} ${clients_SRC})
target_link_libraries(printClient ${QT_LIBRARIES} ${QRemoteSignal_LIBRARY})
