#ifndef _CST_UNX_OS_POLL_H
#define _CST_UNX_OS_POLL_H

#include <poll.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

int Poll(pollfd* fds, nfds_t nfds, int timeout, std::error_code* ec = nullptr);

}
}
}

#endif
