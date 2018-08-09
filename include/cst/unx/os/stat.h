#ifndef _CST_UNX_OS_STAT_H
#define _CST_UNX_OS_STAT_H

#include <sys/stat.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

using stat = struct stat;

int Stat(const char* path, stat* st, std::error_code* ec = nullptr);
int Fstat(int fd, stat* st, std::error_code* ec = nullptr);

}
}
}

#endif
