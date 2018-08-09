#include <cst/unx/file_descriptor.h>
#include <cst/unx/os/unistd.h>  // Close()

namespace cst {
namespace unx {

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& that)
{
    if (this != &that) {
        if (cldt_)
            close();

        fd_   = std::exchange(that.fd_, -1);
        cldt_ = std::exchange(that.cldt_, false);
    }

    return *this;
}

void FileDescriptor::reset(int fd, bool cldt)
{
    if (cldt_)
        close();

    fd_   = fd;
    cldt_ = cldt;
}

void FileDescriptor::close()
{
    os::Close(fd_);
    cldt_ = false;
}

}
}
