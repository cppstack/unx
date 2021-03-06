#include <cst/unx/Socket.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

Socket Socket::Tcp_bind(const InetAddress& addr, int flags)
{
    const int on = 1;
    Socket sock(addr.family(), SOCK_STREAM | flags, 0);
    sock.set_opt(SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    sock.bind(addr.addr(), addr.len());
    return sock;
}

Socket Socket::Tcp_bind(const std::string& host, const std::string& serv,
                        int flags)
{
    addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

    const int on = 1;

    AddrinfoPtr_ res = Getaddrinfo_(host, serv, hints);

    for (const addrinfo* rp = res.get(); rp != nullptr; rp = rp->ai_next) {
        try {
            Socket sock(rp->ai_family, rp->ai_socktype | flags, rp->ai_protocol);
            sock.set_opt(SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
            sock.bind(rp->ai_addr, rp->ai_addrlen);
            return sock;
        } catch (const std::system_error&) { }
    }

    Throw_os_error(EINVAL, "tcp_bind()");
}

Socket Socket::Tcp_bind(const std::string& host, uint16_t port, int flags)
{
    try {
        return Tcp_bind(InetAddress(host, port), flags);
    } catch (const InetAddressError&) { }

    return Tcp_bind(host, std::to_string(port), flags);
}

Socket Socket::Tcp_connect(const InetAddress& addr, int flags)
{
    Socket sock(addr.family(), SOCK_STREAM | flags, 0);
    sock.connect(addr.addr(), addr.len());
    return sock;
}

Socket Socket::Tcp_connect(const std::string& host, const std::string& serv,
                           int flags)
{
    addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    AddrinfoPtr_ res = Getaddrinfo_(host, serv, hints);

    for (const addrinfo* rp = res.get(); rp != nullptr; rp = rp->ai_next) {
        int fd = ::socket(rp->ai_family, rp->ai_socktype | flags,
                          rp->ai_protocol);
        if (fd == -1)
            continue;

        int rc = ::connect(fd, rp->ai_addr, rp->ai_addrlen);
        if (rc == 0 || errno == EINPROGRESS)
            return Socket(rp->ai_family, rp->ai_socktype | flags,
                          rp->ai_protocol, FileDescriptor(fd));

        ::close(fd);
    }

    Throw_os_error(ECONNREFUSED, "tcp_connect()");
}

Socket Socket::Tcp_connect(const std::string& host, uint16_t port, int flags)
{
    try {
        return Tcp_connect(InetAddress(host, port), flags);
    } catch (const InetAddressError&) { }

    return Tcp_connect(host, std::to_string(port), flags);
}

int Socket::connect(const std::string& host, uint16_t port)
{
    try {
        /* try if host is an ip address */
        return connect(InetAddress(host, port, family_));
    } catch (const InetAddressError&) { }

    addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family   = family_;
    hints.ai_socktype = type_;
    hints.ai_protocol = proto_;

    AddrinfoPtr_ res = Getaddrinfo_(host, std::to_string(port), hints);

    for (const addrinfo* rp = res.get(); rp != nullptr; rp = rp->ai_next) {
        int rc = ::connect(fd_, rp->ai_addr, rp->ai_addrlen);
        if (rc == 0 || errno == EINPROGRESS)
            return rc;

        fd_.reset(::socket(family_, type_, proto_));
    }

    Throw_os_error(ECONNREFUSED, "::connect()");
}

int Socket::accept(Socket* sock, InetAddress* address, int flags)
{
    sockaddr* addr = address ? address->addr() : nullptr;
    socklen_t* len = address ? address->len() : nullptr;

    int connfd = os::Accept4(fd_, addr, len, flags);

    if (sock != nullptr)
        *sock = Socket(family_, type_, proto_, FileDescriptor(connfd));

    return connfd;
}

ssize_t Socket::read_until(void* buf, size_t len, char delim)
{
    ssize_t n = peek(buf, len);
    if (n <= 0)
        return n;

    char* m = (char*) std::memchr(buf, delim, n);
    if (m != nullptr)
        n = m - (char*) buf + 1;

    return read(buf, n);
}

Socket::AddrinfoPtr_ Socket::Getaddrinfo_(const std::string& host,
                                          const std::string& serv,
                                          const addrinfo& hints)
{
    addrinfo* res = nullptr;

    const char* node = host.c_str();
    if (*node == '\0')
        node = nullptr;

    os::Getaddrinfo(node, serv.c_str(), &hints, &res);

    return AddrinfoPtr_(res, ::freeaddrinfo);
}

}
}
