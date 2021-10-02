#include <cst/unx/os/socket.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

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

}
}
}
