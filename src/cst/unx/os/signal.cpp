#include <cst/unx/os/signal.h>
#include <cst/unx/error/os_error.h>

namespace cst {
namespace unx {
namespace os {

sighandler_t Signal(int signum, sighandler_t handler, std::error_code* ec)
{
    sighandler_t orig = ::signal(signum, handler);
    if (orig == SIG_ERR) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::signal()");
    }
    return orig;
}

sighandler_t Signal_(int signum, sighandler_t handler, std::error_code* ec)
{
    sigaction act, oact;

    act.sa_handler = handler;
    act.sa_flags = 0;
    if (Sigemptyset(&act.sa_mask, ec) == -1)
        return SIG_ERR;

    if (signum == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef  SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }

    if (Sigaction(signum, &act, &oact, ec) == -1)
        return SIG_ERR;

    return oact.sa_handler;
}

sighandler_t Signal_intr(int signum, sighandler_t handler, std::error_code* ec)
{
    sigaction act, oact;

    act.sa_handler = handler;
    act.sa_flags = 0;
    if (Sigemptyset(&act.sa_mask, ec) == -1)
        return SIG_ERR;

#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif

    if (Sigaction(signum, &act, &oact, ec) == -1)
        return SIG_ERR;

    return oact.sa_handler;
}

int Sigaction(int signum, const sigaction* act, sigaction* oldact, std::error_code* ec)
{
    int ret = ::sigaction(signum, act, oldact);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigaction()");
    }
    return ret;
}

int Kill(pid_t pid, int sig, std::error_code* ec)
{
    int ret = ::kill(pid, sig);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::kill()");
    }
    return ret;
}

int Raise(int sig, std::error_code* ec)
{
    int ret = ::raise(sig);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::raise()");
    }
    return ret;
}

int Sigemptyset(sigset_t* set, std::error_code* ec)
{
    int ret = ::sigemptyset(set);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigemptyset()");
    }
    return ret;
}

int Sigfillset(sigset_t* set, std::error_code* ec)
{
    int ret = ::sigfillset(set);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigfillset()");
    }
    return ret;
}

int Sigaddset(sigset_t* set, int signum, std::error_code* ec)
{
    int ret = ::sigaddset(set, signum);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigaddset()");
    }
    return ret;
}

int Sigdelset(sigset_t* set, int signum, std::error_code* ec)
{
    int ret = ::sigdelset(set, signum);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigdelset()");
    }
    return ret;
}

int Sigismember(const sigset_t* set, int signum, std::error_code* ec)
{
    int ret = ::sigismember(set, signum);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigismember()");
    }
    return ret;
}

int Sigprocmask(int how, const sigset_t* set, sigset_t* oldset, std::error_code* ec)
{
    int ret = ::sigprocmask(how, set, oldset);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigprocmask()");
    }
    return ret;
}

int Sigpending(sigset_t* set, std::error_code* ec)
{
    int ret = ::sigpending(set);
    if (ret == -1) {
        if (ec)
            *ec = Make_os_error_code(errno);
        else
            Throw_os_error(errno, "::sigpending()");
    }
    return ret;
}

int Sigsuspend(const sigset_t* mask, std::error_code* ec)
{
    ::sigsuspend(mask);  /* always return -1 */
    if (ec)
        *ec = Make_os_error_code(errno);
    else
        Throw_os_error(errno, "::sigsuspend()");
    return -1;
}

}
}
}
