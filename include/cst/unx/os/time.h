#ifndef _CST_UNX_OS_TIME_H
#define _CST_UNX_OS_TIME_H

#ifdef __linux__
#include <sys/timerfd.h>
#endif
#include <system_error>

namespace cst {
namespace unx {
namespace os {

#ifdef __linux__
int Timerfd_create(int clockid, int flags, std::error_code* ec = nullptr);

int Timerfd_settime(int fd, int flags,
                    const itimerspec* new_value, itimerspec* old_value,
                    std::error_code* ec = nullptr);
#endif

}
}
}

#endif
