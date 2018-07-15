#ifndef _CST_UNX_OS_STAT_H
#define _CST_UNX_OS_STAT_H

#include <sys/stat.h>
#include <system_error>

namespace cst {
namespace unx {

int Fstat(int fd, struct stat* st, std::error_code* ec) noexcept;
int Fstat(int fd, struct stat* st);

}
}

#endif