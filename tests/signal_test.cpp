#include <cst/unx/os/signal.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <unistd.h>

namespace unx = cst::unx;

const char* msg[] = {
    "SIGINT is caught.\n",
    "SIGALRM is caught.\n",
    "Other signo is caught.\n"
};

char buf[1024];

void sig_handler(int signo)
{
    if (signo == SIGINT)
        ::write(STDERR_FILENO, msg[0], std::strlen(msg[0]));
    else if (signo == SIGALRM)
        ::write(STDERR_FILENO, msg[1], std::strlen(msg[1]));
    else
        ::write(STDERR_FILENO, msg[2], std::strlen(msg[2]));
}

void test_no_signal_handler()
{
    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, buf, n);
        else {
            /* never run, because usually reading stdin doesn't return -1
             * once we get a signal, the default handler will abort the program
             */
            ::perror("read()");
            break;
        }
    }
}

void test_signal()
{
    unx::os::Signal(SIGINT,  sig_handler);
    unx::os::Signal(SIGALRM, sig_handler);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, buf, n);
        else {
            /* never run even with signals (no matter SIGINT or SIGALRM),
             * because the system's signal() will always
             * restart the read() in kernel after finishing running the handler
             * so this test case cannot be interrupted normally, have to kill it
             */
            ::perror("read()");
            break;
        }
    }
}

void test_signal_()
{
    unx::os::Signal_(SIGINT,  sig_handler);
    unx::os::Signal_(SIGALRM, sig_handler);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, buf, n);
        else {
            /* run when SIGALRM comes,
             * the customized signal_() will not restart the read() in kernel
             * if the signo is SIGALRM. errno is EINTR.
             */
            assert(errno == EINTR);
            ::perror("read()");
            break;
        }
    }
}

void test_signal_intr()
{
    unx::os::Signal_intr(SIGINT,  sig_handler);
    unx::os::Signal_intr(SIGALRM, sig_handler);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, buf, n);
        else {
            /* run when SIGINT or SIGALRM comes,
             * the customized signal_intr() will not restart the read()
             * for any signums. errno is EINTR.
             */
            assert(errno == EINTR);
            ::perror("read()");
            break;
        }
    }
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
        return 0;

    int tc = std::atoi(argv[1]);

    if (tc == 1)
        test_no_signal_handler();
    else if (tc == 2)
        test_signal();
    else if (tc == 3)
        test_signal_();
    else if (tc == 4)
        test_signal_intr();

    return 0;
}
