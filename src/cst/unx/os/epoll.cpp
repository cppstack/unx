#include <cst/unx/os/epoll.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Epoll_create1(int flags, std::error_code* ec)
{
    int epfd = ::epoll_create1(flags);
    if (epfd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::epoll_create1()");
    }
    return epfd;
}

int Epoll_ctl(int epfd, int op, int fd, epoll_event* event, std::error_code* ec)
{
    int ret = ::epoll_ctl(epfd, op, fd, event);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::epoll_ctl()");
    }
    return ret;
}

int Epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout,
               std::error_code* ec)
{
    int nr = ::epoll_wait(epfd, events, maxevents, timeout);
    if (nr == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::epoll_wait()");
    }
    return nr;
}

}
}
}
