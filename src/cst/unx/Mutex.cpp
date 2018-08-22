#include <cst/unx/Mutex.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

Mutex::Mutex()
    : holder_(0)
{
    os::Pthread_mutex_init(&mtx_, nullptr);
}

void Mutex::lock()
{
    os::Pthread_mutex_lock(&mtx_);
    holder_ = ::pthread_self();
}

bool Mutex::trylock()
{
    std::error_code ec;

    if (os::Pthread_mutex_trylock(&mtx_, &ec) != 0) {
        if (ec.value() == EBUSY)
            return false;

        throw std::system_error(ec, "::pthread_mutex_trylock()");
    }

    holder_ = ::pthread_self();
    return true;
}

void Mutex::unlock()
{
    std::error_code ec;

    if (::pthread_equal(holder_, ::pthread_self())) {
        holder_ = 0;  /* only release holder_ while still holding it */
        if (os::Pthread_mutex_unlock(&mtx_, &ec))
            holder_ = ::pthread_self(); /* restore holder, unlock() failed */
    } else
        ec = Make_os_error_code(EPERM);

    if (ec)
        throw std::system_error(ec, "::pthread_mutex_unlock()");
}

Mutex::~Mutex()
{
    if (::pthread_equal(holder_, ::pthread_self()))
        ::pthread_mutex_unlock(&mtx_);

    ::pthread_mutex_destroy(&mtx_);
}

}
}
