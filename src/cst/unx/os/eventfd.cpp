#include <cst/unx/os/eventfd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Eventfd(unsigned int initval, int flags, std::error_code* ec)
{
    int fd = ::eventfd(initval, flags);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::eventfd()");
    }
    return fd;
}

}
}
}
