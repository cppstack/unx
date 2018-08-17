#ifndef _CST_UNX_SSL_H
#define _CST_UNX_SSL_H

#include <cst/unx/sslctx.h>

namespace cst {
namespace unx {

class Ssl {
public:
    Ssl() = default;

    Ssl(const Ssl&) = delete;

    Ssl(Ssl&& that) noexcept
        : ssl_(std::move(that.ssl_)),
          state_(std::exchange(that.state_, DISCONNECTED_))
    { }

    Ssl& operator=(const Ssl&) = delete;
    Ssl& operator=(Ssl&& that);

    operator SSL*() const noexcept
    {
        return ssl_.get();
    }

    int connect(int fd);

    void shutdown();

    ~Ssl()
    {
        if (state_ == CONNECTED_)
            ::SSL_shutdown(ssl_.get());
    }

private:
    enum State { DISCONNECTED_, CONNECTED_ };

    std::unique_ptr<::SSL, void(*)(::SSL*)> ssl_{nullptr, ::SSL_free};

    enum State state_ = DISCONNECTED_;
};

}
}

#endif
