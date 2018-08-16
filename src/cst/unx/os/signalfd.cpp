#include <cst/unx/os/signalfd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Signalfd(int fd, const sigset_t* mask, int flags, std::error_code* ec)
{
    int sfd = ::signalfd(fd, mask, flags);
    if (sfd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::signalfd()");
    }
    return sfd;
}

}
}
}
