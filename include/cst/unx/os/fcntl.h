#ifndef _CST_UNX_OS_FCNTL_H
#define _CST_UNX_OS_FCNTL_H

#include <fcntl.h>
#include <system_error>

namespace cst {
namespace unx {

int Open(const char* path, int flags, mode_t mode, std::error_code* ec) noexcept;
int Open(const char* path, int flags, mode_t mode = 0644);

}
}

#endif
