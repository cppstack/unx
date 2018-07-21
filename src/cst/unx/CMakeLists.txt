set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(OpenSSL REQUIRED)

add_library(cst_unx
            file.cpp
            file_descriptor.cpp
            mutex.cpp
            thread.cpp
            os/fcntl.cpp
            os/inet.cpp
            os/pthread.cpp
            os/signal.cpp
            os/socket.cpp
            os/stat.cpp
            os/unistd.cpp
            os/wait.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)

target_compile_options(cst_unx PRIVATE -Wall -Wextra -Wpointer-arith)

target_include_directories(cst_unx PUBLIC  ${PROJECT_SOURCE_DIR}/include
                                           ${CMAKE_CURRENT_BINARY_DIR}
                                   PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cst_unx PRIVATE Threads::Threads ${OPENSSL_LIBRARIES})

install(TARGETS cst_unx DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/cst/unx/ DESTINATION include/cst/unx)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h DESTINATION include/cst/unx)
