#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/File.h>
#include <cst/unx/os/mman.h>

namespace unx = cst::unx;

TEST_CASE("create file", "[mmap]")
{
    const char* path = "mtp.txt";
    const char msg[] = "Hello, world!";
    const std::size_t mlen = 256;

    unx::File f1(path, O_RDWR|O_CREAT|O_TRUNC);

    void* buf1 = unx::os::Mmap(NULL, mlen, PROT_WRITE, MAP_SHARED, f1.fd(), 0);

    f1.truncate(sizeof(msg));
    std::memcpy(buf1, msg, sizeof(msg));

    unx::os::Munmap(buf1, mlen);

    char buf2[mlen];
    unx::File f2(path, O_RDONLY);
    f2.read(buf2, sizeof(buf2));

    REQUIRE(f2.size() == sizeof(msg));
    REQUIRE(std::strcmp(buf2, msg) == 0);

    ::unlink(path);
}
