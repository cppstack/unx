#include <cst/unx/os/unistd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

int Ftruncate(int fd, off_t len, std::error_code* ec) noexcept
{
    int r = ::ftruncate(fd, len);
    if (r == -1 && ec)
        *ec = Make_os_error_code(errno);
    return r;
}

int Ftruncate(int fd, off_t len)
{
    int r = ::ftruncate(fd, len);
    if (r == -1)
        Throw_os_error(errno, "::ftruncate()");
    return r;
}

off_t Lseek(int fd, off_t off, int whence, std::error_code* ec) noexcept
{
    off_t ofs = ::lseek(fd, off, whence);
    if (ofs == -1 && ec)
        *ec = Make_os_error_code(errno);
    return ofs;
}

off_t Lseek(int fd, off_t off, int whence)
{
    off_t ofs = ::lseek(fd, off, whence);
    if (ofs == -1)
        Throw_os_error(errno, "::lseek()");
    return ofs;
}

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec) noexcept
{
    ssize_t n = ::read(fd, buf, len);
    if (n == -1 && ec)
        *ec = Make_os_error_code(errno);
    return n;
}

ssize_t Read(int fd, void* buf, size_t len)
{
    ssize_t n = ::read(fd, buf, len);
    if (n == -1)
        Throw_os_error(errno, "::read()");
    return n;
}

ssize_t Readn(int fd, void* buf, size_t len, std::error_code* ec) noexcept
{
    size_t nread = 0;

    while (nread < len) {
        ssize_t n = ::read(fd, (char*) buf + nread, len - nread);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            return -1;
        }

        if (n == 0)
            break;

        nread += n;
    }

    return nread;
}

ssize_t Readn(int fd, void* buf, size_t len)
{
    std::error_code ec;
    ssize_t n = Readn(fd, buf, len, &ec);
    if (n == -1)
        throw std::system_error(ec, "::read()");
    return n;
}

ssize_t Write(int fd, const void* buf, size_t len, std::error_code* ec) noexcept
{
    ssize_t n = ::write(fd, buf, len);
    if (n == -1 && ec)
        *ec = Make_os_error_code(errno);
    return n;
}

ssize_t Write(int fd, const void* buf, size_t len)
{
    ssize_t n = ::write(fd, buf, len);
    if (n == -1)
        Throw_os_error(errno, "::write()");
    return n;
}

ssize_t Writen(int fd, const void* buf, size_t len, std::error_code* ec) noexcept
{
    size_t nwritten = 0;

    while (nwritten < len) {
        ssize_t n = ::write(fd, (const char*) buf + nwritten, len - nwritten);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            return -1;
        }

        if (n == 0)
            break;

        nwritten += n;
    }

    return nwritten;
}

ssize_t Writen(int fd, const void* buf, size_t len)
{
    std::error_code ec;
    ssize_t n = Writen(fd, buf, len, &ec);
    if (n == -1)
        throw std::system_error(ec, "::write()");
    return n;
}

int Close(int fd, std::error_code* ec) noexcept
{
    int r = ::close(fd);
    if (r == -1 && ec)
        *ec = Make_os_error_code(errno);
    return r;
}

int Close(int fd)
{
    int r = ::close(fd);
    if (r == -1)
        Throw_os_error(errno, "::close()");
    return r;
}

}
}
