#ifndef _CST_UNX_GAI_ERROR_H
#define _CST_UNX_GAI_ERROR_H

#include <netdb.h>
#include <system_error>

namespace cst {
namespace unx {

class the_gai_category : public std::error_category {
public:
    const char* name() const noexcept override
    { return "gai"; }

    std::string message(int ev) const override
    { return ::gai_strerror(ev); }
};

inline const std::error_category& gai_category() noexcept
{
    static the_gai_category instance;
    return instance;
}

inline std::error_code Make_gai_error_code(int ev) noexcept
{
    return std::error_code(ev, gai_category());
}

[[noreturn]] inline void Throw_gai_error(int ev, const std::string& what_arg)
{
    throw std::system_error(ev, gai_category(), what_arg);
}

}
}

#endif
