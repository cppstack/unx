#ifndef _CST_UNX_OS_UNISTD_H
#define _CST_UNX_OS_UNISTD_H

#include <unistd.h>
#include <system_error>

namespace cst {
namespace unx {

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec) noexcept;
ssize_t Read(int fd, void* buf, size_t len);

}
}

#endif
