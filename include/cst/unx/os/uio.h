#ifndef _CST_UNX_OS_UIO_H
#define _CST_UNX_OS_UIO_H

#include <sys/uio.h>
#include <system_error>
#include <cst/unx/os/types.h>

namespace cst {
namespace unx {
namespace os {

using iovec = struct iovec;

ssize_t Readv(int fd, const iovec* iov, int iovcnt, std::error_code* ec = nullptr);
ssize_t Writev(int fd, const iovec* iov, int iovcnt, std::error_code* ec = nullptr);

}
}
}

#endif
