#ifndef _CST_UNX_OS_TYPES_H
#define _CST_UNX_OS_TYPES_H

#include <sys/types.h>

namespace cst {
namespace unx {

using mode_t = ::mode_t;
using off_t = ::off_t;
using pid_t = ::pid_t;
using size_t = ::size_t;
using ssize_t = ::ssize_t;

}
}

#endif
