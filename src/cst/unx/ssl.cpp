#include <cst/unx/ssl.h>
#include <cst/unx/error/ssl_error.h>

namespace cst {
namespace unx {

int Ssl::connect(int fd)
{
    if (!ssl_)
        ssl_.reset(::SSL_new(SslCtx::get()));

    if (!ssl_)
        Throw_ssl_error(static_cast<int>(ssl_errc::ssl), "::SSL_new()");

    if (::SSL_set_fd(ssl_.get(), fd) != 1)
        Throw_ssl_error(static_cast<int>(ssl_errc::ssl), "::SSL_set_fd()");

    int ret = ::SSL_connect(ssl_.get());
    if (ret <= 0) {
        int err = ::SSL_get_error(ssl_.get(), ret);
        Throw_ssl_error(err, "::SSL_connect()");
    }

    state_ = CONNECTED_;

    return ret;
}

Ssl& Ssl::operator=(Ssl&& that)
{
    if (this != &that) {
        shutdown();

        ssl_ = std::move(that.ssl_);
        state_ = std::exchange(that.state_, DISCONNECTED_);
    }

    return *this;
}

void Ssl::shutdown()
{
    if (state_ == CONNECTED_) {
        os::SSL_Shutdown(ssl_.get());
        state_ = DISCONNECTED_;
    }
}

}
}
