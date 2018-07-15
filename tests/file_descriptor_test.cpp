#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/file_descriptor.h>
#include <cst/unx/os/unistd.h>
#include <cst/unx/os/fcntl.h>

namespace unx = cst::unx;

TEST_CASE("FileDescriptor", "[FileDescriptor]")
{
    const char* path = "tmp.txt";
    int fd = -1;

    {
        unx::FileDescriptor fd1;
        unx::FileDescriptor fd2(unx::Open(path, O_RDWR|O_CREAT));
        REQUIRE(fd2 != -1);

        fd1 = std::move(fd2);
        REQUIRE(fd2 == -1);

        fd = fd1;
        REQUIRE(::fcntl(fd, F_GETFD) != -1);
    }

    REQUIRE(::fcntl(fd, F_GETFD) == -1);

    ::unlink(path);
}
