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

    static SslCtx& Get()
    {
        static SslCtx ctx;
        return ctx;
    }

    operator ::SSL_CTX*() const noexcept { return ctx_.get(); }

    ~SslCtx()
    {
        Cleanup_();
    }

private:
    SslCtx();

    static void Cleanup_() noexcept;

    std::unique_ptr<::SSL_CTX, void(*)(::SSL_CTX*)> ctx_{nullptr, ::SSL_CTX_free};
};

}
}

#endif
