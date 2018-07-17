#include <cst/unx/os/pthread.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

int Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start)(void*), void* arg, std::error_code* ec) noexcept
{
    int err = ::pthread_create(thread, attr, start, arg);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start)(void*), void* arg)
{
    int err = ::pthread_create(thread, attr, start, arg);
    if (err)
        Throw_os_error(err, "::pthread_create()");
    return err;
}

int Pthread_join(pthread_t thread, void** retval, std::error_code* ec) noexcept
{
    int err = ::pthread_join(thread, retval);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_join(pthread_t thread, void** retval)
{
    int err = ::pthread_join(thread, retval);
    if (err)
        Throw_os_error(err, "::pthread_join()");
    return err;
}

int Pthread_detach(pthread_t thread, std::error_code* ec) noexcept
{
    int err = ::pthread_detach(thread);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_detach(pthread_t thread)
{
    int err = ::pthread_detach(thread);
    if (err)
        Throw_os_error(err, "::pthread_detach()");
    return err;
}

int Pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr, std::error_code* ec) noexcept
{
    int err = ::pthread_mutex_init(mutex, attr);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr)
{
    int err = ::pthread_mutex_init(mutex, attr);
    if (err)
        Throw_os_error(err, "::pthread_mutex_init()");
    return err;
}

int Pthread_mutex_lock(pthread_mutex_t* mutex, std::error_code* ec) noexcept
{
    int err = ::pthread_mutex_lock(mutex);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_mutex_lock(pthread_mutex_t* mutex)
{
    int err = ::pthread_mutex_lock(mutex);
    if (err)
        Throw_os_error(err, "::pthread_mutex_lock()");
    return err;
}

int Pthread_mutex_trylock(pthread_mutex_t* mutex, std::error_code* ec) noexcept
{
    int err = ::pthread_mutex_trylock(mutex);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_mutex_trylock(pthread_mutex_t* mutex)
{
    int err = ::pthread_mutex_trylock(mutex);
    if (err)
        Throw_os_error(err, "::pthread_mutex_trylock()");
    return err;
}

int Pthread_mutex_unlock(pthread_mutex_t* mutex, std::error_code* ec) noexcept
{
    int err = ::pthread_mutex_unlock(mutex);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_mutex_unlock(pthread_mutex_t* mutex)
{
    int err = ::pthread_mutex_unlock(mutex);
    if (err)
        Throw_os_error(err, "::pthread_mutex_unlock()");
    return err;
}

int Pthread_mutex_destroy(pthread_mutex_t* mutex, std::error_code* ec) noexcept
{
    int err = ::pthread_mutex_destroy(mutex);
    if (err && ec)
        *ec = Make_os_error_code(err);
    return err;
}

int Pthread_mutex_destroy(pthread_mutex_t* mutex)
{
    int err = ::pthread_mutex_destroy(mutex);
    if (err)
        Throw_os_error(err, "::pthread_mutex_destroy()");
    return err;
}

}
}
