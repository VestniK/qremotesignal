cmake_minimum_required(VERSION 2.8.0)

set(testSRC
  errortests.cpp
)

qrs_wrap_service(SERVICE_SRC ${EXAMPLE_SERVICE})

add_executable(TestErrors ${testSRC} ${SERVICE_SRC})
qt5_use_modules(TestErrors Core Test)
target_link_libraries(TestErrors QRemoteSignal)

qrs_qtest(TestErrors)
