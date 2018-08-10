#include <cst/unx/error/ssl_error.h>

namespace cst {
namespace unx {

std::string the_ssl_category::message(int ev) const
{
    switch(static_cast<ssl_errc>(ev)) {
    case ssl_errc::none:
        return "success";
    case ssl_errc::ssl:
        return "ssl error";
    case ssl_errc::want_read:
        return "want read";
    case ssl_errc::want_write:
        return "want write";
    case ssl_errc::want_x509_lookup:
        return "want x509 lookup";
    case ssl_errc::syscall:
        return "syscall error";
    case ssl_errc::zero_return:
        return "zero return";
    case ssl_errc::want_connect:
        return "want connect";
    case ssl_errc::want_accept:
        return "want accept";
    default:
        return "unknown error";
    }
}

}
}
