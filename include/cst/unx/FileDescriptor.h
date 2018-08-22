#ifndef _CST_UNX_FILE_DESCRIPTOR_H
#define _CST_UNX_FILE_DESCRIPTOR_H

#include <utility>
#include <unistd.h>

namespace cst {
namespace unx {

class FileDescriptor {
public:
    FileDescriptor() = default;

    explicit FileDescriptor(int fd, bool cldt = true) noexcept
        : fd_(fd), cldt_(cldt)
    { }

    FileDescriptor(const FileDescriptor&) = delete;

    FileDescriptor(FileDescriptor&& that) noexcept
        : fd_  (std::exchange(that.fd_, -1)),
          cldt_(std::exchange(that.cldt_, false))
    { }

    FileDescriptor& operator=(const FileDescriptor&) = delete;
    FileDescriptor& operator=(FileDescriptor&& that);

    operator int() const noexcept { return fd_; }

    void reset(int fd, bool cldt = true);

    void close();

    ~FileDescriptor()
    {
        if (cldt_)
            ::close(fd_);
    }

private:
    int  fd_   = -1;
    bool cldt_ = false;
};

}
}

#endif
