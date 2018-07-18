#ifndef _CST_UNX_OS_UNISTD_H
#define _CST_UNX_OS_UNISTD_H

#include <unistd.h>
#include <system_error>

namespace cst {
namespace unx {

int Truncate(const char* path, off_t len, std::error_code* ec = nullptr);
int Ftruncate(int fd, off_t len, std::error_code* ec = nullptr);

off_t Lseek(int fd, off_t off, int whence, std::error_code* ec = nullptr);

ssize_t Read(int fd, void* buf, size_t len, std::error_code* ec = nullptr);
ssize_t Readn(int fd, void* buf, size_t len, std::error_code* ec = nullptr);

ssize_t Write(int fd, const void* buf, size_t len, std::error_code* ec = nullptr);
ssize_t Writen(int fd, const void* buf, size_t len, std::error_code* ec = nullptr);

int Close(int fd, std::error_code* ec = nullptr);

int Dup(int oldfd, std::error_code* ec = nullptr);
int Dup2(int oldfd, int newfd, std::error_code* ec = nullptr);
int Dup3(int oldfd, int newfd, int flags, std::error_code* ec = nullptr);

pid_t Fork(std::error_code* ec = nullptr);

}
}

#endif
