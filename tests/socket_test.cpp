#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/socket.h>
#include <thread>
#include <chrono>
#include <atomic>

namespace unx = cst::unx;

const uint16_t port = 12345;

const char msg[] = "hello";
const std::size_t msg_size = sizeof(msg);

std::atomic_bool ready{false};

void client_func()
{
    using namespace std::chrono_literals;

    while (!ready)
        std::this_thread::sleep_for(1ms);

    unx::Socket sock(AF_INET, SOCK_STREAM, 0);
    sock.connect("localhost", port);

    sock.send(msg, msg_size);
    sock.close();
}

TEST_CASE("socket", "[Socket]")
{
    char buf[msg_size];

    std::thread client_thread(client_func);

    unx::Socket serv_sock = unx::Socket::tcp_bind(unx::InetAddress("::", port));
    serv_sock.listen(5);

    ready = true;
    unx::Socket peer;
    serv_sock.accept(&peer);
    peer.recv(buf, sizeof(buf));
    peer.close();

    REQUIRE(std::strcmp(buf, msg) == 0);

    client_thread.join();
}
