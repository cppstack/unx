#ifndef _CST_UNX_SSLSOCKET_H
#define _CST_UNX_SSLSOCKET_H

#include <cst/unx/Socket.h>
#include <cst/unx/Ssl.h>

namespace cst {
namespace unx {

class SslSocket : public Socket {
public:
    SslSocket(Socket&& sock);

    bool verify_certificate() const noexcept;

    virtual ssize_t peek(void* buf, size_t len) override
    {
        return os::SSL_Peek(ssl_, buf, len);
    }

    virtual ssize_t read(void* buf, size_t len) override
    {
        return os::SSL_Read(ssl_, buf, len);
    }

    virtual ssize_t readn(void* buf, size_t len) override
    {
        return os::SSL_Readn(ssl_, buf, len);
    }

    virtual ssize_t write(const void* buf, size_t len) override
    {
        return os::SSL_Write(ssl_, buf, len);
    }

    virtual ssize_t writen(const void* buf, size_t len) override
    {
        return os::SSL_Writen(ssl_, buf, len);
    }

    void shutdown()
    {
        ssl_.shutdown();
    }

    virtual void close() override
    {
        ssl_.shutdown();
        Socket::close();
    }

private:
    Ssl ssl_;
};

}
}

#endif
