#ifndef _CST_UNX_SSL_ERROR_H
#define _CST_UNX_SSL_ERROR_H

#include <openssl/ssl.h>
#include <system_error>

namespace cst {
namespace unx {

enum class ssl_errc {
    none             = SSL_ERROR_NONE,
    ssl              = SSL_ERROR_SSL,
    want_read        = SSL_ERROR_WANT_READ,
    want_write       = SSL_ERROR_WANT_WRITE,
    want_x509_lookup = SSL_ERROR_WANT_X509_LOOKUP,
    syscall          = SSL_ERROR_SYSCALL,
    zero_return      = SSL_ERROR_ZERO_RETURN,
    want_connect     = SSL_ERROR_WANT_CONNECT,
    want_accept      = SSL_ERROR_WANT_ACCEPT
};

class the_ssl_category : public std::error_category {
public:
    const char* name() const noexcept override
    { return "ssl"; }

    std::string message(int ev) const override;
};

const std::error_category& ssl_category() noexcept
{
    static the_ssl_category instance;
    return instance;
}

inline std::error_code Make_ssl_error_code(int ev) noexcept
{
    return std::error_code(ev, ssl_category());
}

[[noreturn]] inline void Throw_ssl_error(int ev, const std::string& what_arg)
{
    throw std::system_error(ev, ssl_category(), what_arg);
}

}
}

#endif
