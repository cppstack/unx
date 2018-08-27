#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/SslSocket.h>
#include <thread>
#include <chrono>
#include <atomic>

namespace unx = cst::unx;

const uint16_t Port_ = 12345;

const char Msg_[] = "hello";
const std::size_t Msg_size_ = sizeof(Msg_);

std::atomic_bool Ready_{false};

void Client_func_()
{
    using namespace std::chrono_literals;

    while (!Ready_)
        std::this_thread::sleep_for(1ms);

    unx::Socket sock(AF_INET, SOCK_STREAM, 0);
    sock.connect("localhost", Port_);

    sock.write(Msg_, Msg_size_);
    sock.close();
}

TEST_CASE("socket", "[Socket]")
{
    char buf[Msg_size_];

    std::thread client_thread(Client_func_);

    unx::Socket serv_sock = unx::Socket::Tcp_bind(unx::InetAddress("::", Port_));
    serv_sock.listen(5);

    Ready_ = true;
    unx::Socket peer;
    serv_sock.accept(&peer);
    peer.read(buf, sizeof(buf));
    peer.close();

    REQUIRE(std::strcmp(buf, Msg_) == 0);

    client_thread.join();
}

TEST_CASE("ssl", "[SslSocket]")
{
    char msg[] = "GET / HTTP/1.1\r\nHost: github.com\r\n\r\n";
    char buf[1024] = "";

    unx::SslSocket sock(unx::Socket::Tcp_connect("github.com", 443));
    REQUIRE(sock.verify_certificate());
    sock.write(msg, sizeof(msg));
    sock.read(buf, sizeof(buf));
    sock.close();
    REQUIRE(std::strncmp(buf, "HTTP/1.1 200 OK", 15) == 0);
}
