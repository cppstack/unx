#include <cst/unx/os/unistd.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Truncate(const char* path, off_t len, std::error_code* ec)
{
    int r = ::truncate(path, len);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::truncate()");
    }
    return r;
}

int Ftruncate(int fd, off_t len, std::error_code* ec)
{
    int r = ::ftruncate(fd, len);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::ftruncate()");
    }
    return r;
}

off_t Lseek(int fd, off_t off, int whence, std::error_code* ec)
{
    off_t ofs = ::lseek(fd, off, whence);
    if (ofs == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::lseek()");
    }
    return ofs;
}

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec)
{
    ssize_t n = ::read(fd, buf, len);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::read()");
    }
    return n;
}

ssize_t Readn(int fd, void* buf, size_t len, std::error_code* ec)
{
    size_t nread = 0;

    while (nread < len) {
        ssize_t n = ::read(fd, (char*) buf + nread, len - nread);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::read()");

            return -1;
        }

        if (n == 0)
            break;

        nread += n;
    }

    return nread;
}

ssize_t Write(int fd, const void* buf, size_t len, std::error_code* ec)
{
    ssize_t n = ::write(fd, buf, len);
    if (n == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::write()");
    }
    return n;
}

ssize_t Writen(int fd, const void* buf, size_t len, std::error_code* ec)
{
    size_t nwritten = 0;

    while (nwritten < len) {
        ssize_t n = ::write(fd, (const char*) buf + nwritten, len - nwritten);

        if (n == -1) {
            if (ec)
                *ec = Make_os_error_code(errno);
            else
                Throw_os_error(errno, "::write()");

            return -1;
        }

        if (n == 0)
            break;

        nwritten += n;
    }

    return nwritten;
}

int Close(int fd, std::error_code* ec)
{
    int r = ::close(fd);
    if (r == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::close()");
    }
    return r;
}

int Dup(int oldfd, std::error_code* ec)
{
    int newfd = ::dup(oldfd);
    if (newfd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::dup()");
    }
    return newfd;
}

int Dup2(int oldfd, int newfd, std::error_code* ec)
{
    int fd = ::dup2(oldfd, newfd);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::dup2()");
    }
    return fd;
}

int Dup3(int oldfd, int newfd, int flags, std::error_code* ec)
{
    int fd = ::dup3(oldfd, newfd, flags);
    if (fd == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::dup3()");
    }
    return fd;
}

pid_t Fork(std::error_code* ec)
{
    pid_t pid = ::fork();
    if (pid == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::fork()");
    }
    return pid;
}

}
}
}
