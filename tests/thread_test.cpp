#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/thread.h>

namespace unx = cst::unx;

void* update_res(void* argv)
{
    (*(int*)argv)++;
    return nullptr;
}

TEST_CASE("thread", "[Thread]")
{
    int res = 0;

    unx::Thread th0;
    unx::Thread th1(update_res, &res);

    th0 = std::move(th1);
    th0.join();

    REQUIRE(res == 1);
}
