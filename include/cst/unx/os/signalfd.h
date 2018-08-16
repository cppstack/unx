#ifndef _CST_UNX_OS_SIGNALFD_H
#define _CST_UNX_OS_SIGNALFD_H

#include <sys/signalfd.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

int Signalfd(int fd, const sigset_t* mask, int flags, std::error_code* ec = nullptr);

}
}
}

#endif
