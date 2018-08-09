#ifndef _CST_UNX_OS_FCNTL_H
#define _CST_UNX_OS_FCNTL_H

#include <fcntl.h>
#include <system_error>
#include <cst/unx/os/types.h>

namespace cst {
namespace unx {
namespace os {

int Open(const char* path, int flags, std::error_code* ec = nullptr);
int Open(const char* path, int flags, mode_t mode, std::error_code* ec = nullptr);

}
}
}

#endif
