#ifndef _CST_UNX_SOCKET_H
#define _CST_UNX_SOCKET_H

#include <memory>
#include <cst/unx/os/unistd.h>
#include <cst/unx/os/socket.h>
#include <cst/unx/InetAddress.h>
#include <cst/unx/FileDescriptor.h>

namespace cst {
namespace unx {

class Socket {
    friend class SslSocket;
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

    static Socket Tcp_bind(const InetAddress& addr, int flags = 0);

    static Socket Tcp_bind(const std::string& host, const std::string& serv,
                           int flags = 0);

    static Socket Tcp_bind(const std::string& host, uint16_t port,
                           int flags = 0);

    static Socket Tcp_connect(const InetAddress& addr, int flags = 0);

    static Socket Tcp_connect(const std::string& host, const std::string& serv,
                              int flags = 0);

    static Socket Tcp_connect(const std::string& host, uint16_t port,
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

    virtual ssize_t peek(void* buf, size_t len)
    {
        return os::Recv(fd_, buf, len, MSG_PEEK);
    }

    virtual ssize_t read(void* buf, size_t len)
    {
        return os::Read(fd_, buf, len);
    }

    virtual ssize_t readn(void* buf, size_t len)
    {
        return os::Readn(fd_, buf, len);
    }

    ssize_t read_until(void* buf, size_t len, char delim);

    virtual ssize_t write(const void* buf, size_t len)
    {
        return os::Write(fd_, buf, len);
    }

    virtual ssize_t writen(const void* buf, size_t len)
    {
        return os::Writen(fd_, buf, len);
    }

    ssize_t writes(const char* str)
    {
        return writen(str, std::strlen(str));
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

    virtual void close()
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

    virtual ~Socket() =  default;

private:
    using AddrinfoPtr_ = std::unique_ptr<addrinfo, decltype(::freeaddrinfo)*>;

    static AddrinfoPtr_ Getaddrinfo_(const std::string& host,
                                     const std::string& serv,
                                     const addrinfo& hints);

protected:
    int family_ = 0;
    int type_   = 0;
    int proto_  = 0;
    FileDescriptor fd_;
};

}
}

#endif
