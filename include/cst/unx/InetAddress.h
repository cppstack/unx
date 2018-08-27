#ifndef _CST_UNX_INET_ADDRESS_H
#define _CST_UNX_INET_ADDRESS_H

#include <cst/unx/os/inet.h>
#include <cstring>  // std::memset()

namespace cst {
namespace unx {

class InetAddress {
    friend std::ostream& operator<<(std::ostream&, const InetAddress&);

public:
    InetAddress() noexcept
    {
        std::memset(&storage_, 0, sizeof(storage_));
    }

    InetAddress(const std::string& ip, uint16_t port);
    InetAddress(const std::string& ip, uint16_t port, int af);

    int family() const noexcept
    { return storage_.ss_family; }

    const sockaddr* addr() const noexcept
    { return (sockaddr*) &storage_; }

    sockaddr* addr() noexcept
    { return (sockaddr*) &storage_; }

    const struct sockaddr_in* addr_v4() const noexcept
    { return (struct sockaddr_in*) &storage_; }

    const struct sockaddr_in6* addr_v6() const noexcept
    { return (struct sockaddr_in6*) &storage_; }

    socklen_t len() const noexcept
    { return len_; }

    socklen_t* len() noexcept
    { return &len_; }

private:
    const void* sin_addr_(int af) const noexcept
    {
        /* af must be either AF_INET or AF_INET6 */
        if (af == AF_INET)
            return &((struct sockaddr_in*) &storage_)->sin_addr;
        else
            return &((struct sockaddr_in6*) &storage_)->sin6_addr;
    }

    void* sin_addr_(int af) noexcept
    {
        return const_cast<void*>(
              static_cast<const InetAddress*>(this)->sin_addr_(af)
        );
    }

    const uint16_t& sin_port_(int af) const noexcept
    {
        /* af must be either AF_INET or AF_INET6 */
        return (af == AF_INET) ?
               ((struct sockaddr_in*) &storage_)->sin_port
             : ((struct sockaddr_in6*) &storage_)->sin6_port;
    }

    uint16_t& sin_port_(int af) noexcept
    {
        return const_cast<uint16_t&>(
              static_cast<const InetAddress&>(*this).sin_port_(af)
        );
    }

    struct sockaddr_storage storage_;
    socklen_t len_ = sizeof(storage_);
};

class InetAddressError : public std::logic_error {
public:
    InetAddressError(const std::string& ip)
        : logic_error("invalid ip address " + ip)
    { }

    InetAddressError(const std::string& ip, int af)
        : logic_error("invalid ip address " + ip + " for address family " + Af_str_(af))
    { }

private:
    static std::string Af_str_(int af) noexcept
    {
        switch (af) {
        case AF_INET:
            return "AF_INET";
        case AF_INET6:
            return "AF_INET6";
        default:
            return "Unknown";
        }
    }
};

}
}

#endif
