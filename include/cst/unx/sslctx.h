#ifndef _CST_UNX_SSL_CTX_H
#define _CST_UNX_SSL_CTX_H

#include <cst/unx/os/openssl.h>
#include <memory>

namespace cst {
namespace unx {

class SslCtx {
public:
    SslCtx(const SslCtx&) = delete;
    SslCtx& operator=(const SslCtx&) = delete;

    static SslCtx& get()
    {
        static SslCtx ctx;
        return ctx;
    }

    static void cleanup() noexcept;

    operator ::SSL_CTX*() const noexcept { return ctx_.get(); }

    ~SslCtx() { cleanup(); }

private:
    SslCtx();

    std::unique_ptr<::SSL_CTX, void(*)(::SSL_CTX*)> ctx_{nullptr, ::SSL_CTX_free};
};

}
}

#endif
