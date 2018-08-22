#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/File.h>

namespace unx = cst::unx;

TEST_CASE("create file", "[File]")
{
    const char* path = "tmp.txt";

    ::unlink(path);

    try {
        unx::File f(path, O_RDWR|O_CREAT);
    } catch (const std::system_error& e) {
        REQUIRE(false);
        return;
    }

    REQUIRE(::access(path, F_OK) == 0);

    ::unlink(path);
}

TEST_CASE("open no_such_file", "[File]")
{
    try {
        unx::File f("no_such_file", O_RDWR);
    } catch (const std::system_error& e) {
        REQUIRE(e.code().value() == ENOENT);
        return;
    }

    REQUIRE(false);
}

TEST_CASE("read, write, seek file and get size", "[File]")
{
    const char* path = "tmp.txt";
    const char* text = "Hello world!";
    char buf[30];

    unx::File f("tmp.txt", O_RDWR|O_CREAT|O_TRUNC);
    f.writes(text);
    f.seek(0, SEEK_SET);
    f.read(buf, sizeof(buf));

    REQUIRE(std::strcmp(buf, text) == 0);

    REQUIRE(f.size() == std::strlen(text));
    REQUIRE(f.size() == f.seek(-1, SEEK_END) + 1);

    ::unlink(path);
}
