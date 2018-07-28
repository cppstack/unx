#ifndef _CST_UNX_OS_MMAN_H
#define _CST_UNX_OS_MMAN_H

#include <sys/mman.h>
#include <system_error>

namespace cst {
namespace unx {

void* Mmap(void* addr, size_t len, int prot, int flags,
           int fd, off_t offset, std::error_code* ec = nullptr);

#ifdef __linux__
void* Mremap(void* old_addr, size_t old_size, size_t new_size, int flags,
             void* new_addr = nullptr, std::error_code* ec = nullptr);
#endif

int Mprotect(void* addr, size_t len, int prot, std::error_code* ec = nullptr);

int Msync(void* addr, size_t len, int flags, std::error_code* ec = nullptr);

int Madvise(void* addr, size_t len, int advice, std::error_code* ec = nullptr);

int Munmap(void* addr, size_t len, std::error_code* ec = nullptr);

}
}

#endif
