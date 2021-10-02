#include <cst/unx/os/unistd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

ssize_t Readn(int fd, void* buf, size_t len, std::error_code* ec)
{
    size_t nread = 0;

    while (nread < len) {
        ssize_t n = ::read(fd, (char*) buf + nread, len - nread);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::read()");

            return -1;
        }

        if (n == 0)
            break;

        nread += n;
    }

    return nread;
}

ssize_t Writen(int fd, const void* buf, size_t len, std::error_code* ec)
{
    size_t nwritten = 0;

    while (nwritten < len) {
        ssize_t n = ::write(fd, (const char*) buf + nwritten, len - nwritten);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::write()");

            return -1;
        }

        if (n == 0)
            break;

        nwritten += n;
    }

    return nwritten;
}

}
}
}
