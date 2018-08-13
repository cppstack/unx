#include <cst/unx/os/openssl.h>
#include <cst/unx/error/ssl_error.h>

namespace cst {
namespace unx {
namespace os {

int SSL_Connect(SSL* ssl, std::error_code* ec)
{
    int rc = ::SSL_connect(ssl);
    if (rc <= 0) {
        int ev = ::SSL_get_error(ssl, rc);
        if (ec)
            *ec = Make_ssl_error_code(ev);
        else
            Throw_ssl_error(ev, "::SSL_connect()");
    }
    return rc;
}

int SSL_Peek(SSL* ssl, void* buf, int num, std::error_code* ec)
{
    int rc = ::SSL_peek(ssl, buf, num);
    if (rc <= 0) {
        int ev = ::SSL_get_error(ssl, rc);
        if (ec)
            *ec = Make_ssl_error_code(ev);
        else
            Throw_ssl_error(ev, "::SSL_peek()");
    }
    return rc;
}

int SSL_Read(SSL* ssl, void* buf, int num, std::error_code* ec)
{
    int rc = ::SSL_read(ssl, buf, num);
    if (rc <= 0) {
        int ev = ::SSL_get_error(ssl, rc);
        if (ec)
            *ec = Make_ssl_error_code(ev);
        else
            Throw_ssl_error(ev, "::SSL_read()");
    }
    return rc;
}

int SSL_Readn(SSL* ssl, void* buf, int num, std::error_code* ec)
{
    int nread = 0;

    while (nread < num) {
        int n = ::SSL_read(ssl, (char *) buf + nread, num - nread);
        if (n <= 0) {
            int ev = ::SSL_get_error(ssl, n);
            if (ec)
                *ec = Make_ssl_error_code(ev);
            else
                Throw_ssl_error(ev, "::SSL_read()");

            return n;
        }

        nread += n;
    }

    return nread;
}

int SSL_Write(SSL* ssl, const void* buf, int num, std::error_code* ec)
{
    int rc = ::SSL_write(ssl, buf, num);
    if (rc <= 0) {
        int ev = ::SSL_get_error(ssl, rc);
        if (ec)
            *ec = Make_ssl_error_code(ev);
        else
            Throw_ssl_error(ev, "::SSL_write()");
    }
    return rc;
}

int SSL_Writen(SSL* ssl, const void* buf, int num, std::error_code* ec)
{
    int nwritten = 0;

    while (nwritten < num) {
        int n = ::SSL_write(ssl, (const char*) buf + nwritten, num - nwritten);
        if (n <= 0) {
            int ev = ::SSL_get_error(ssl, n);
            if (ec)
                *ec = Make_ssl_error_code(ev);
            else
                Throw_ssl_error(ev, "::SSL_write()");

            return n;
        }

        nwritten += n;
    }

    return nwritten;
}

int SSL_Shutdown(SSL* ssl, std::error_code* ec)
{
    int rc = ::SSL_shutdown(ssl);
    if (rc == 0)  /* try again */
        rc = ::SSL_shutdown(ssl);
    if (rc <= 0) {
        int ev = ::SSL_get_error(ssl, rc);
        if (ec)
            *ec = Make_ssl_error_code(ev);
        else
            Throw_ssl_error(ev, "::SSL_shutdown()");
    }
    return rc;
}

}
}
}
