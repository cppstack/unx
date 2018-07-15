#include <cst/unx/os/unistd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec) noexcept
{
    ssize_t n = ::read(fd, buf, len);
    if (n == -1 && ec)
        *ec = Make_os_error_code(errno);
    return n;
}

ssize_t Read(int fd, void* buf, size_t len)
{
    ssize_t n = ::read(fd, buf, len);
    if (n == -1)
        Throw_os_error(errno, "::read()");
    return n;
}

}
}
