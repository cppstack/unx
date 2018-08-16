#include <cst/unx/os/pthread.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

int Pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start)(void*), void* arg, std::error_code* ec)
{
    int err = ::pthread_create(thread, attr, start, arg);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_create()");
    }
    return err;
}

int Pthread_join(pthread_t thread, void** retval, std::error_code* ec)
{
    int err = ::pthread_join(thread, retval);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_join()");
    }
    return err;
}

int Pthread_detach(pthread_t thread, std::error_code* ec)
{
    int err = ::pthread_detach(thread);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_detach()");
    }
    return err;
}

int Pthread_cancel(pthread_t thread, std::error_code* ec)
{
    int err = ::pthread_cancel(thread);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_cancel()");
    }
    return err;
}

int Pthread_setcancelstate(int state, int* oldstate, std::error_code* ec)
{
    int err = ::pthread_setcancelstate(state, oldstate);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_setcancelstate()");
    }
    return err;
}

int Pthread_setcanceltype(int type, int* oldtype, std::error_code* ec)
{
    int err = ::pthread_setcanceltype(type, oldtype);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_setcanceltype()");
    }
    return err;
}


int Pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr, std::error_code* ec)
{
    int err = ::pthread_mutex_init(mutex, attr);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_mutex_init()");
    }
    return err;
}

int Pthread_mutex_lock(pthread_mutex_t* mutex, std::error_code* ec)
{
    int err = ::pthread_mutex_lock(mutex);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_mutex_lock()");
    }
    return err;
}

int Pthread_mutex_trylock(pthread_mutex_t* mutex, std::error_code* ec)
{
    int err = ::pthread_mutex_trylock(mutex);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_mutex_trylock()");
    }
    return err;
}

int Pthread_mutex_unlock(pthread_mutex_t* mutex, std::error_code* ec)
{
    int err = ::pthread_mutex_unlock(mutex);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_mutex_unlock()");
    }
    return err;
}

int Pthread_mutex_destroy(pthread_mutex_t* mutex, std::error_code* ec)
{
    int err = ::pthread_mutex_destroy(mutex);
    if (err) {
        if (ec)
            *ec = Make_os_error_code(err);
        else
            Throw_os_error(err, "::pthread_mutex_destroy()");
    }
    return err;
}

}
}
}
