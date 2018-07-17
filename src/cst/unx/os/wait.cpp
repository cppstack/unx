#include <cst/unx/os/wait.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

pid_t Wait(int* wstatus, std::error_code* ec) noexcept
{
    pid_t pid = ::wait(wstatus);
    if (pid == -1 && ec)
        *ec = Make_os_error_code(errno);
    return pid;
}

pid_t Wait(int* wstatus)
{
    pid_t pid = ::wait(wstatus);
    if (pid == -1)
        Throw_os_error(errno, "::wait()");
    return pid;
}

pid_t Waitpid(pid_t pid, int* wstatus, int options, std::error_code* ec) noexcept
{
    pid_t id = ::waitpid(pid, wstatus, options);
    if (id == -1 && ec)
        *ec = Make_os_error_code(errno);
    return id;
}

pid_t Waitpid(pid_t pid, int* wstatus, int options)
{
    pid_t id = ::waitpid(pid, wstatus, options);
    if (id == -1)
        Throw_os_error(errno, "::waitpid()");
    return id;
}

}
}
