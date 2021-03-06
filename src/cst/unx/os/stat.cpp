#include <cst/unx/os/stat.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Stat(const char* path, struct stat* st, std::error_code* ec)
{
    int r = ::stat(path, st);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::stat()");
    }
    return r;
}

int Fstat(int fd, struct stat* st, std::error_code* ec)
{
    int r = ::fstat(fd, st);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::fstat()");
    }
    return r;
}

}
}
}
