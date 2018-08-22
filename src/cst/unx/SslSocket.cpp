#include <cst/unx/SslSocket.h>

namespace cst {
namespace unx {

SslSocket::SslSocket(Socket&& sock)
{
    ssl_.connect(sock.fd());

    family_ = sock.family_;
    type_ = sock.type_;
    proto_ = sock.proto_;
    fd_ = std::move(sock.fd_);
}

bool SslSocket::verify_certificate() const noexcept
{
    std::unique_ptr<X509, decltype(::X509_free)*>
    cert(::SSL_get_peer_certificate(ssl_), ::X509_free);
    if (!cert)
        return false;

    if (::SSL_get_verify_result(ssl_) != X509_V_OK)
        return false;

    return true;
}

}
}
