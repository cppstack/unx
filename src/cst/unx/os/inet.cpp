#include <cst/unx/os/inet.h>
#include <cst/unx/error/os_error.h>
#include <cst/unx/error/gai_error.h>

namespace cst {
namespace unx {

int Inet_pton(int af, const char* src, void* dst, std::error_code* ec)
{
    int r = ::inet_pton(af, src, dst);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::inet_pton()");
    }
    return r;
}

const char* Inet_ntop(int af, const void* src, char* dst, socklen_t size, std::error_code* ec)
{
    const char* p = ::inet_ntop(af, src, dst, size);
    if (p == nullptr) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::inet_ntop()");
    }
    return p;
}

int Getaddrinfo(const char* node, const char* service, const addrinfo* hints,
                addrinfo** res, std::error_code* ec)
{
    int rc = ::getaddrinfo(node, service, hints, res);
    if (rc != 0) {
        if (ec)
            *ec = Make_gai_error_code(rc);
        else
            Throw_gai_error(rc, "::getaddrinfo()");
    }
    return rc;
}

}
}
