#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cst/unx/Mutex.h>

namespace unx = cst::unx;

TEST_CASE("mutex", "[Mutex]")
{
    unx::Mutex mutex;
    REQUIRE( mutex.trylock());
    REQUIRE(!mutex.trylock());
    mutex.unlock();
    mutex.lock();
}
