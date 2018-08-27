#include <cst/unx/os/signal.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <unistd.h>

namespace unx = cst::unx;

const char* Msg_[] = {
    "SIGINT is caught.\n",
    "SIGALRM is caught.\n",
    "Other signo is caught.\n"
};

char Buf_[1024];

void Sig_handler_(int signo)
{
    if (signo == SIGINT)
        ::write(STDERR_FILENO, Msg_[0], std::strlen(Msg_[0]));
    else if (signo == SIGALRM)
        ::write(STDERR_FILENO, Msg_[1], std::strlen(Msg_[1]));
    else
        ::write(STDERR_FILENO, Msg_[2], std::strlen(Msg_[2]));
}

void Test_no_signal_handler_()
{
    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, Buf_, sizeof(Buf_) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, Buf_, n);
        else {
            /* never run, because usually reading stdin doesn't return -1
             * once we get a signal, the default handler will abort the program
             */
            ::perror("read()");
            break;
        }
    }
}

void Test_signal_()
{
    unx::os::Signal(SIGINT,  Sig_handler_);
    unx::os::Signal(SIGALRM, Sig_handler_);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, Buf_, sizeof(Buf_) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, Buf_, n);
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

void Test_signal_n_()
{
    unx::os::Signal_n(SIGINT,  Sig_handler_);
    unx::os::Signal_n(SIGALRM, Sig_handler_);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, Buf_, sizeof(Buf_) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, Buf_, n);
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

void Test_signal_i_()
{
    unx::os::Signal_i(SIGINT,  Sig_handler_);
    unx::os::Signal_i(SIGALRM, Sig_handler_);

    ::alarm(10);

    for (;;) {
        int n = ::read(STDIN_FILENO, Buf_, sizeof(Buf_) - 1);
        if (n >= 0)
            ::write(STDOUT_FILENO, Buf_, n);
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
        Test_no_signal_handler_();
    else if (tc == 2)
        Test_signal_();
    else if (tc == 3)
        Test_signal_n_();
    else if (tc == 4)
        Test_signal_i_();

    return 0;
}
