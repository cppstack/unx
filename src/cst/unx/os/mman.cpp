#include <cst/unx/os/mman.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

void* Mmap(void* addr, size_t len, int prot, int flags,
           int fd, off_t offset, std::error_code* ec)
{
    void* mm = ::mmap(addr, len, prot, flags, fd, offset);
    if (mm == MAP_FAILED) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::mmap()");
    }
    return mm;
}

#ifdef __linux__
void* Mremap(void* old_addr, size_t old_size, size_t new_size, int flags,
             void* new_addr, std::error_code* ec)
{
    void* mm = ::mremap(old_addr, old_size, new_size, flags, new_addr);
    if (mm == MAP_FAILED) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::mremap()");
    }
    return mm;
}
#endif

int Mprotect(void* addr, size_t len, int prot, std::error_code* ec)
{
    int ret = ::mprotect(addr, len, prot);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::mprotect()");
    }
    return ret;
}

int Msync(void* addr, size_t len, int flags, std::error_code* ec)
{
    int ret = ::msync(addr, len, flags);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::msync()");
    }
    return ret;
}

int Madvise(void* addr, size_t len, int advice, std::error_code* ec)
{
    int ret = ::madvise(addr, len, advice);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::madvise()");
    }
    return ret;
}

int Munmap(void* addr, size_t len, std::error_code* ec)
{
    int ret = ::munmap(addr, len);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::munmap()");
    }
    return ret;
}

}
}
}
