#ifndef _CST_UNX_OS_WAIT_H
#define _CST_UNX_OS_WAIT_H

#include <sys/wait.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

pid_t Wait(int* wstatus, std::error_code* ec = nullptr);

pid_t Waitpid(pid_t pid, int* wstatus, int options, std::error_code* ec = nullptr);

}
}
}

#endif
