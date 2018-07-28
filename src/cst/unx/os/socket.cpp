#include <cst/unx/os/socket.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

int Socket(int domain, int type, int protocol, std::error_code* ec)
{
    int fd = ::socket(domain, type, protocol);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::socket()");
    }
    return fd;
}

int Connect(int sockfd, const sockaddr* addr, socklen_t addrlen, std::error_code* ec)
{
    int rc = ::connect(sockfd, addr, addrlen);
    if (rc == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::connect()");
    }
    return rc;
}

int Bind(int sockfd, const sockaddr* addr, socklen_t addrlen, std::error_code* ec)
{
    int rc = ::bind(sockfd, addr, addrlen);
    if (rc == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::bind()");
    }
    return rc;
}

int Listen(int sockfd, int backlog, std::error_code* ec)
{
    int rc = ::listen(sockfd, backlog);
    if (rc == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::listen()");
    }
    return rc;
}

int Accept(int sockfd, sockaddr* addr, socklen_t* addrlen, std::error_code* ec)
{
    int connfd = ::accept(sockfd, addr, addrlen);
    if (connfd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::accept()");
    }
    return connfd;
}

int Accept4(int sockfd, sockaddr* addr, socklen_t* addrlen, int flags, std::error_code* ec)
{
    int connfd = ::accept4(sockfd, addr, addrlen, flags);
    if (connfd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::accept4()");
    }
    return connfd;
}

ssize_t Recv(int sockfd, void* buf, size_t len, int flags, std::error_code* ec)
{
    ssize_t n = ::recv(sockfd, buf, len, flags);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::recv()");
    }
    return n;
}

ssize_t Recvn(int sockfd, void* buf, size_t len, int flags, std::error_code* ec)
{
    size_t nrecv = 0;

    while (nrecv < len) {
        ssize_t n = ::recv(sockfd, (char*) buf + nrecv, len - nrecv, flags);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::recv()");

            return -1;
        }

        if (n == 0)
            break;

        nrecv += n;
    }

    return nrecv;
}

ssize_t Send(int sockfd, const void* buf, size_t len, int flags, std::error_code* ec)
{
    ssize_t n = ::send(sockfd, buf, len, flags);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::send()");
    }
    return n;
}

ssize_t Sendn(int sockfd, const void* buf, size_t len, int flags, std::error_code* ec)
{
    size_t nsent = 0;

    while (nsent < len) {
        ssize_t n = ::send(sockfd, (const char*) buf + nsent, len - nsent, flags);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::send()");

            return -1;
        }

        if (n == 0)
            break;

        nsent += n;
    }

    return nsent;
}

int Getsockopt(int sockfd, int level, int opt, void* val, socklen_t* len, std::error_code* ec)
{
    int rc = ::getsockopt(sockfd, level, opt, val, len);
    if (rc == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::getsockopt()");
    }
    return rc;
}

int Setsockopt(int sockfd, int level, int opt, const void* val, socklen_t len, std::error_code* ec)
{
    int rc = ::setsockopt(sockfd, level, opt, val, len);
    if (rc == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::setsockopt()");
    }
    return rc;
}

}
}
