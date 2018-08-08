#ifndef _CST_UNX_OS_SOCKET_H
#define _CST_UNX_OS_SOCKET_H

#include <sys/socket.h>
#include <system_error>
#include <cst/unx/os/types.h>

namespace cst {
namespace unx {
namespace os {

using socklen_t = ::socklen_t;
using sockaddr = struct sockaddr;

int Socket(int domain, int type, int protocol, std::error_code* ec = nullptr);

int Connect(int sockfd, const sockaddr* addr, socklen_t addrlen, std::error_code* ec = nullptr);

int Bind(int sockfd, const sockaddr* addr, socklen_t addrlen, std::error_code* ec = nullptr);

int Listen(int sockfd, int backlog, std::error_code* ec = nullptr);

int Accept(int sockfd, sockaddr* addr, socklen_t* addrlen, std::error_code* ec = nullptr);
int Accept4(int sockfd, sockaddr* addr, socklen_t* addrlen, int flags, std::error_code* ec = nullptr);

ssize_t Recv(int sockfd, void* buf, size_t len, int flags, std::error_code* ec = nullptr);
ssize_t Recvn(int sockfd, void* buf, size_t len, int flags, std::error_code* ec = nullptr);

ssize_t Send(int sockfd, const void* buf, size_t len, int flags, std::error_code* ec = nullptr);
ssize_t Sendn(int sockfd, const void* buf, size_t len, int flags, std::error_code* ec = nullptr);

int Getsockopt(int sockfd, int level, int opt, void* val, socklen_t* len, std::error_code* ec = nullptr);
int Setsockopt(int sockfd, int level, int opt, const void* val, socklen_t len, std::error_code* ec = nullptr);

int Shutdown(int sockfd, int how, std::error_code* ec = nullptr);

}
}
}

#endif
