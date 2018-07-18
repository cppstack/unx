#include <cst/unx/os/wait.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {

pid_t Wait(int* wstatus, std::error_code* ec)
{
    pid_t pid = ::wait(wstatus);
    if (pid == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::wait()");
    }
    return pid;
}

pid_t Waitpid(pid_t pid, int* wstatus, int options, std::error_code* ec)
{
    pid_t id = ::waitpid(pid, wstatus, options);
    if (id == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::waitpid()");
    }
    return id;
}

}
}
