#ifndef _CST_UNX_OS_ERROR_H
#define _CST_UNX_OS_ERROR_H

#include <system_error>

namespace cst {
namespace unx {

inline std::error_code Make_os_error_code(int ev) noexcept
{
    return std::error_code(ev, std::system_category());
}

[[noreturn]] inline void Throw_os_error(int ev, const std::string& what_arg)
{
    throw std::system_error(ev, std::system_category(), what_arg);
}

}
}

#endif
