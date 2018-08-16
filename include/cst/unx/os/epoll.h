#ifndef _CST_UNX_OS_EPOLL_H
#define _CST_UNX_OS_EPOLL_H

#include <sys/epoll.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

int Epoll_create1(int flags, std::error_code* ec = nullptr);

int Epoll_ctl(int epfd, int op, int fd, epoll_event* event,
              std::error_code* ec = nullptr);

int Epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout,
               std::error_code* ec = nullptr);

}
}
}

#endif
