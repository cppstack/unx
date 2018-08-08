#ifndef _CST_UNX_SOCKET_H
#define _CST_UNX_SOCKET_H

#include <memory>
#include <cst/unx/os/socket.h>
#include <cst/unx/inet_address.h>
#include <cst/unx/file_descriptor.h>

namespace cst {
namespace unx {

class Socket {
public:
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket() = default;

    Socket(int domain, int type, int proto)
        : family_(domain), type_(type), proto_(proto),
          fd_(os::Socket(family_, type_, proto_))
    { }

    Socket(int domain, int type, int proto, FileDescriptor&& fd)
        : family_(domain), type_(type), proto_(proto), fd_(std::move(fd))
    { }

    Socket(Socket&&) = default;
    Socket& operator=(Socket&&) = default;

    static Socket tcp_bind(const InetAddress& addr, int flags = 0);

    static Socket tcp_bind(const std::string& host, const std::string& serv,
                           int flags = 0);

    static Socket tcp_bind(const std::string& host, uint16_t port,
                           int flags = 0);

    static Socket tcp_connect(const InetAddress& addr, int flags = 0);

    static Socket tcp_connect(const std::string& host, const std::string& serv,
                              int flags = 0);

    static Socket tcp_connect(const std::string& host, uint16_t port,
                              int flags = 0);

    int fd() const noexcept
    { return fd_; }

    int connect(const std::string& host, uint16_t port);

    int connect(const InetAddress& address)
    {
        return os::Connect(fd_, address.addr(), address.len());
    }

    int connect(const sockaddr* addr, socklen_t len)
    {
        return os::Connect(fd_, addr, len);
    }

    int bind(const InetAddress& address)
    {
        return os::Bind(fd_, address.addr(), address.len());
    }

    int bind(const sockaddr* addr, socklen_t len)
    {
        return os::Bind(fd_, addr, len);
    }

    int listen(int backlog)
    {
        return os::Listen(fd_, backlog);
    }

    int accept(Socket* sock, InetAddress* address = nullptr, int flags = 0);

    ssize_t peek(void* buf, size_t len, int flags = 0)
    {
        return os::Recv(fd_, buf, len, MSG_PEEK | flags);
    }

    ssize_t recv(void* buf, size_t len, int flags = 0)
    {
        return os::Recv(fd_, buf, len, flags);
    }

    ssize_t recvn(void* buf, size_t len, int flags = 0)
    {
        return os::Recvn(fd_, buf, len, flags);
    }

    ssize_t recv_until(void* buf, size_t len, char delim, int flags = 0);

    ssize_t send(const void* buf, size_t len, int flags = 0)
    {
        return os::Send(fd_, buf, len, flags);
    }

    ssize_t sendn(const void* buf, size_t len, int flags = 0)
    {
        return os::Sendn(fd_, buf, len, flags);
    }

    ssize_t sends(const char* str, int flags = 0)
    {
        return os::Sendn(fd_, str, std::strlen(str), flags);
    }

    int get_opt(int level, int opt, void* val, socklen_t* len) const
    {
        return os::Getsockopt(fd_, level, opt, val, len);
    }

    int set_opt(int level, int opt, const void* val, socklen_t len)
    {
        return os::Setsockopt(fd_, level, opt, val, len);
    }

    void shutdown(int how)
    {
        os::Shutdown(fd_, how);
    }

    void close()
    {
        fd_.close();
    }

    int error() const
    {
        int err = -1;
        socklen_t len = sizeof err;
        os::Getsockopt(fd_, SOL_SOCKET, SO_ERROR, &err, &len);
        return err;
    }

private:
    using addrinfo_uptr = std::unique_ptr<addrinfo, decltype(::freeaddrinfo)*>;

    static addrinfo_uptr getaddrinfo(const std::string& host,
                                     const std::string& serv,
                                     const addrinfo& hints);

    int family_ = 0;
    int type_   = 0;
    int proto_  = 0;
    FileDescriptor fd_;
};

}
}

#endif
