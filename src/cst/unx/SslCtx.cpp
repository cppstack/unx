#include <cst/unx/SslCtx.h>
#include <cst/unx/error/ssl_error.h>

namespace cst {
namespace unx {

SslCtx::SslCtx()
{
    ::SSL_library_init();
    ::SSL_load_error_strings();

    ctx_.reset(::SSL_CTX_new(::SSLv23_client_method()));
    if (!ctx_)
        Throw_ssl_error(static_cast<int>(ssl_errc::ssl), "::SSL_CTX_new()");

    ::SSL_CTX_set_default_verify_paths(ctx_.get());
    ::SSL_CTX_set_verify(ctx_.get(), SSL_VERIFY_NONE, nullptr);

    SSL_CTX_set_mode(ctx_.get(), SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_mode(ctx_.get(), SSL_MODE_AUTO_RETRY);
}

void SslCtx::Cleanup_() noexcept
{
    ::ERR_free_strings();
    ::ERR_remove_thread_state(NULL);
    ::CRYPTO_cleanup_all_ex_data();
    ::SSL_COMP_free_compression_methods();
    ::EVP_cleanup();
}

}
}
