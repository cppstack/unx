#ifndef _CST_UNX_OS_SIGNAL_H
#define _CST_UNX_OS_SIGNAL_H

#include <signal.h>
#include <system_error>

namespace cst {
namespace unx {
namespace os {

::sighandler_t Signal(int signum, ::sighandler_t handler, std::error_code* ec = nullptr);
::sighandler_t Signal_n(int signum, ::sighandler_t handler, std::error_code* ec = nullptr);
::sighandler_t Signal_i(int signum, ::sighandler_t handler, std::error_code* ec = nullptr);

int Sigaction(int signum, const struct sigaction* act, struct sigaction* oldact, std::error_code* ec = nullptr);

int Kill(pid_t pid, int sig, std::error_code* ec = nullptr);
int Raise(int sig, std::error_code* ec = nullptr);

int Sigemptyset(sigset_t* set, std::error_code* ec = nullptr);
int Sigfillset(sigset_t* set, std::error_code* ec = nullptr);
int Sigaddset(sigset_t* set, int signum, std::error_code* ec = nullptr);
int Sigdelset(sigset_t* set, int signum, std::error_code* ec = nullptr);
int Sigismember(const sigset_t* set, int signum, std::error_code* ec = nullptr);

int Sigprocmask(int how, const sigset_t* set, sigset_t* oldset, std::error_code* ec = nullptr);
int Sigpending(sigset_t* set, std::error_code* ec = nullptr);

int Sigsuspend(const sigset_t* mask, std::error_code* ec = nullptr);

}
}
}

#endif
