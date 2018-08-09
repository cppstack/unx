#include <cst/unx/inet_address.h>
#include <sstream>
#include <initializer_list>

namespace cst {
namespace unx {

InetAddress::InetAddress(const std::string& ip, uint16_t port)
    : InetAddress()
{
    for (int af : { AF_INET, AF_INET6 }) {
        if (os::Inet_pton(af, ip.c_str(), sin_addr_(af)) == 1) {
            sin_port_(af) = htons(port);
            storage_.ss_family = af;
            len_ = (af == AF_INET) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6);
            return;
        }
    }

    throw InetAddressError(ip);
}

InetAddress::InetAddress(const std::string& ip, uint16_t port, int af)
    : InetAddress()
{
    if (os::Inet_pton(af, ip.c_str(), sin_addr_(af)) != 1)
        throw InetAddressError(ip, af);

    sin_port_(af) = htons(port);
    storage_.ss_family = af;
    len_ = (af == AF_INET) ? sizeof(sockaddr_in) : sizeof(sockaddr_in6);
}

std::ostream& operator<<(std::ostream& os, const InetAddress& addr)
{
    char buf[INET6_ADDRSTRLEN + 1];
    int af = addr.storage_.ss_family;

    if (::inet_ntop(af, addr.sin_addr_(af), buf, sizeof(buf)))
        os << buf << ':' << ntohs(addr.sin_port_(af));
    else
        os << "(null)";

    return os;
}

}
}
