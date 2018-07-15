#include <cst/unx/os/fcntl.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

int Open(const char* path, int flags, mode_t mode, std::error_code* ec) noexcept
{
    int fd = ::open(path, flags, mode);
    if (fd == -1 && ec)
        *ec = Make_os_error_code(errno);
    return fd;
}

int Open(const char* path, int flags, mode_t mode)
{
    int fd = ::open(path, flags, mode);
    if (fd == -1)
        Throw_os_error(errno, "::open()");
    return fd;
}

}
}
