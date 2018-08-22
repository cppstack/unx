#include <cst/unx/Thread.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

Thread::Thread(const function_t& func, void* argv)
    : func_(func), argv_(argv)
{
    os::Pthread_create(&tid_, nullptr, *func_.target<void*(*)(void*)>(), argv_);
}

Thread& Thread::operator=(Thread&& that) noexcept
{
    if (this != &that) {
        if (joinable())
            std::terminate();

        move_(std::move(that));
    }

    return *this;
}

}
}
