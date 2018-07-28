#ifndef _CST_UNX_OS_INET_H
#define _CST_UNX_OS_INET_H

#include <arpa/inet.h>
#include <netdb.h>
#include <system_error>

namespace cst {
namespace unx {

using socklen_t = ::socklen_t;
using addrinfo = struct addrinfo;

int Inet_pton(int af, const char* src, void* dst, std::error_code* ec = nullptr);
const char* Inet_ntop(int af, const void* src, char* dst, socklen_t size, std::error_code* ec = nullptr);

int Getaddrinfo(const char* node, const char* service, const addrinfo* hints,
                addrinfo** res, std::error_code* ec = nullptr);

}
}

#endif
