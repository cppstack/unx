#include <cst/unx/os/sendfile.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

#ifdef __linux__
ssize_t Sendfile(int out_fd, int in_fd, off_t* offset, size_t len, std::error_code* ec)
{
    ssize_t n = ::sendfile(out_fd, in_fd, offset, len);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sendfile()");
    }
    return n;
}
#endif

}
}
}
