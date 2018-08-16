#include <cst/unx/os/time.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

#ifdef __linux__

int Timerfd_create(int clockid, int flags, std::error_code* ec)
{
    int fd = ::timerfd_create(clockid, flags);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::timerfd_create()");
    }
    return fd;
}

int Timerfd_settime(int fd, int flags,
                    const itimerspec* new_value, itimerspec* old_value,
                    std::error_code* ec)
{
    int ret = ::timerfd_settime(fd, flags, new_value, old_value);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::timerfd_settime()");
    }
    return ret;
}

#endif

}
}
}
