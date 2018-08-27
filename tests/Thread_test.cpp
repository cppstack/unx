#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/Thread.h>

namespace unx = cst::unx;

void* Update_res_(void* argv)
{
    (*(int*)argv)++;
    return nullptr;
}

TEST_CASE("thread", "[Thread]")
{
    int res = 0;

    unx::Thread th0;
    unx::Thread th1(Update_res_, &res);

    th0 = std::move(th1);
    th0.join();

    REQUIRE(res == 1);
}
