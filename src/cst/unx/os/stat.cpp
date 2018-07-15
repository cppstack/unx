#include <cst/unx/os/stat.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

int Fstat(int fd, struct stat* st, std::error_code* ec) noexcept
{
    int r = ::fstat(fd, st);
    if (r == -1 && ec)
        *ec = Make_os_error_code(errno);
    return r;
}

int Fstat(int fd, struct stat* st)
{
    int r = ::fstat(fd, st);
    if (r == -1)
        Throw_os_error(errno, "::fstat()");
    return r;
}

}
}
