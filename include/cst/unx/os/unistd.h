#ifndef _CST_UNX_OS_UNISTD_H
#define _CST_UNX_OS_UNISTD_H

#include <unistd.h>
#include <system_error>

namespace cst {
namespace unx {

int Ftruncate(int fd, off_t len, std::error_code* ec) noexcept;
int Ftruncate(int fd, off_t len);

off_t Lseek(int fd, off_t off, int whence, std::error_code* ec) noexcept;
off_t Lseek(int fd, off_t off, int whence);

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec) noexcept;
ssize_t Read(int fd, void* buf, size_t len);

ssize_t Readn(int fd, void* buf, size_t len, std::error_code* ec) noexcept;
ssize_t Readn(int fd, void* buf, size_t len);

ssize_t Write(int fd, const void* buf, size_t len, std::error_code* ec) noexcept;
ssize_t Write(int fd, const void* buf, size_t len);

ssize_t Writen(int fd, const void* buf, size_t len, std::error_code* ec) noexcept;
ssize_t Writen(int fd, const void* buf, size_t len);

int Close(int fd, std::error_code* ec) noexcept;
int Close(int fd);

}
}

#endif
