set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(OpenSSL REQUIRED)

set(SRCS    file.cpp
            file_descriptor.cpp
            inet_address.cpp
            mutex.cpp
            socket.cpp
            sslsocket.cpp
            ssl.cpp
            sslctx.cpp
            thread.cpp
            error/ssl_error.cpp
            os/fcntl.cpp
            os/inet.cpp
            os/mman.cpp
            os/openssl.cpp
            os/pthread.cpp
            os/poll.cpp
            os/sendfile.cpp
            os/signal.cpp
            os/socket.cpp
            os/stat.cpp
            os/time.cpp
            os/uio.cpp
            os/unistd.cpp
            os/wait.cpp
)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND SRCS os/epoll.cpp
                     os/eventfd.cpp
                     os/signalfd.cpp
    )
endif()

add_library(cst_unx ${SRCS})

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
