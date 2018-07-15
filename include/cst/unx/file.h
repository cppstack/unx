#ifndef _CST_UNX_FILE_H
#define _CST_UNX_FILE_H

#include <cst/unx/file_descriptor.h>
#include <cst/unx/os/unistd.h>
#include <cst/unx/os/fcntl.h>
#include <cst/unx/os/stat.h>
#include <cstring>

namespace cst {
namespace unx {

class File {
public:
    File() = default;

    File(int fd, const std::string& path)
        : fd_(fd, false), path_(path)
    { }

    File(const std::string& path, int flags, mode_t mode = 0644)
        : path_(path)
    {
        fd_.reset(Open(path.c_str(), flags, mode));
    }

    File(const File&) = delete;
    File(File&&) = default;

    File& operator=(const File&) = delete;
    File& operator=(File&&) = default;

    int fd() const noexcept
    {
        return fd_;
    }

    std::string path() const noexcept
    {
        return path_;
    }

    int truncate(off_t len)
    {
        return Ftruncate(fd_, len);
    }

    off_t seek(off_t off, int whence)
    {
        return Lseek(fd_, off, whence);
    }

    ssize_t read(void* buf, size_t len)
    {
        return Read(fd_, buf, len);
    }

    ssize_t write(const void* buf, size_t len)
    {
        return Write(fd_, buf, len);
    }

    ssize_t writes(const char* str)
    {
        return write(str, std::strlen(str));
    }

    size_t size() const
    {
        struct stat st;
        Fstat(fd_, &st);
        return st.st_size;
    }

    void close()
    {
        fd_.close();
    }

private:
    FileDescriptor fd_;
    std::string path_;
};

extern File Stdin;
extern File Stdout;
extern File Stderr;

}
}

#endif
