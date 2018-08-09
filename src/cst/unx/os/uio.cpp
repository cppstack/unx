#include <cst/unx/os/uio.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

ssize_t Readv(int fd, const iovec* iov, int iovcnt, std::error_code* ec)
{
    ssize_t n = ::readv(fd, iov, iovcnt);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::readv()");
    }
    return n;
}

ssize_t Writev(int fd, const iovec* iov, int iovcnt, std::error_code* ec)
{
    ssize_t n = ::writev(fd, iov, iovcnt);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::writev()");
    }
    return n;
}

}
}
}
