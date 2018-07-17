#ifndef _CST_UNX_MUTEX_H
#define _CST_UNX_MUTEX_H

#include <cst/unx/os/pthread.h>

namespace cst {
namespace unx {

class Mutex {
public:
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

    Mutex();

    void lock();
    bool trylock();
    void unlock();

    ~Mutex();

private:
    pthread_mutex_t mtx_;
    pthread_t holder_;
};

}
}

#endif
