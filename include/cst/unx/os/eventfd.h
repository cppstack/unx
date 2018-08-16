#ifndef _CST_UNX_OS_EVENTFD_H
#define _CST_UNX_OS_EVENTFD_H

#include <sys/eventfd.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

int Eventfd(unsigned int initval, int flags, std::error_code* ec = nullptr);

}
}
}

#endif
