#include <cst/unx/os/fcntl.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Open(const char* path, int flags, std::error_code* ec)
{
    return Open(path, flags, 0644, ec);
}

int Open(const char* path, int flags, mode_t mode, std::error_code* ec)
{
    int fd = ::open(path, flags, mode);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::open()");
    }
    return fd;
}

}
}
}
