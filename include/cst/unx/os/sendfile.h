#ifndef _CST_UNX_OS_SENDFILE_H
#define _CST_UNX_OS_SENDFILE_H

#ifdef __linux__
#include <sys/sendfile.h>
#endif
#include <system_error>

namespace cst {
namespace unx {
namespace os {

#ifdef __linux__
ssize_t Sendfile(int out_fd, int in_fd, off_t* offset, size_t len,
                 std::error_code* ec = nullptr);
#endif

}
}
}

#endif
