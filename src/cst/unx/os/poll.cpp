#include <cst/unx/os/poll.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Poll(pollfd* fds, nfds_t nfds, int timeout, std::error_code* ec)
{
    int nr = ::poll(fds, nfds, timeout);
    if (nr == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::poll()");
    }
    return nr;
}

}
}
}
