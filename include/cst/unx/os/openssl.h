#ifndef _CST_UNX_OS_SSL_H
#define _CST_UNX_OS_SSL_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

int SSL_Connect(SSL* ssl, std::error_code* ec = nullptr);

int SSL_Peek(SSL* ssl, void* buf, int num, std::error_code* ec = nullptr);

int SSL_Read(SSL* ssl, void* buf, int num, std::error_code* ec = nullptr);
int SSL_Readn(SSL* ssl, void* buf, int num, std::error_code* ec = nullptr);

int SSL_Write(SSL* ssl, const void* buf, int num, std::error_code* ec = nullptr);
int SSL_Writen(SSL* ssl, const void* buf, int num, std::error_code* ec = nullptr);

int SSL_Shutdown(SSL* ssl, std::error_code* ec = nullptr);

}
}
}

#endif
