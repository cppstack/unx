#ifndef _CST_UNX_THREAD_H
#define _CST_UNX_THREAD_H

#include <cst/unx/os/pthread.h>
#include <functional>

namespace cst {
namespace unx {

class Thread {
public:
    typedef std::function<void*(void*)> function_t;

    Thread() = default;

    Thread(const function_t& func, void* argv);

    Thread(const Thread&) = delete;
    Thread(Thread&& that) noexcept
    {
        move_(std::move(that));
    }

    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&& that) noexcept;

    bool joinable() const noexcept { return tid_ != 0; }

    void join()
    {
        os::Pthread_join(tid_, nullptr);
        tid_ = 0;
    }

    void detach()
    {
        os::Pthread_detach(tid_);
        tid_ = 0;
    }

    ~Thread()
    {
        if (joinable())
            std::terminate();
    }

private:
    void move_(Thread&& that) noexcept
    {
        tid_  = std::exchange(that.tid_, 0);
        func_ = std::move(that.func_);
        argv_ = std::exchange(that.argv_, nullptr);
    }

    ::pthread_t tid_ = 0;
    function_t func_;
    void* argv_ = nullptr;
};

}
}

#endif
