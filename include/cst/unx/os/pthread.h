#ifndef _CST_UNX_OS_PTHREAD_H
#define _CST_UNX_OS_PTHREAD_H

#include <pthread.h>
#include <system_error>

namespace cst {
namespace unx {

int Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start)(void*), void* arg, std::error_code* ec = nullptr);

int Pthread_join(pthread_t thread, void** retval, std::error_code* ec = nullptr);

int Pthread_detach(pthread_t thread, std::error_code* ec = nullptr);


int Pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr, std::error_code* ec = nullptr);

int Pthread_mutex_lock(pthread_mutex_t* mutex, std::error_code* ec = nullptr);
int Pthread_mutex_trylock(pthread_mutex_t* mutex, std::error_code* ec = nullptr);
int Pthread_mutex_unlock(pthread_mutex_t* mutex, std::error_code* ec = nullptr);

int Pthread_mutex_destroy(pthread_mutex_t* mutex, std::error_code* ec = nullptr);

}
}

#endif
