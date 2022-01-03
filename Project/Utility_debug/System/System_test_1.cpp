#include "System_test.h"

using std::cout; using std::endl;
using std::string; using std::cin;

void printWaitStatus(const char* msg, int status)
{
    if (msg != nullptr)
        printf("%s", msg);

    if (WIFEXITED(status)) {
        printf("child exited, status=%d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        printf("child killed by signal %d (%s)",
            WTERMSIG(status), strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP
        if (WCOREDUMP(status))
            printf(" (core dumped)");
#endif
        printf("\n");
    }
    else if (WIFSTOPPED(status)) {
        printf("child stopped by signal %d (%s)\n",
            WSTOPSIG(status), strsignal(WSTOPSIG(status)));
#ifdef WIFCONTINUED
    }
    else if (WIFCONTINUED(status)) {
        printf("child continued\n");
#endif
    }
    else {
        printf("status=%x\n",
            (unsigned int)status);
    }
}

int sys1()
{
    auto ret = system("ls");

    if (ret == -1)
        cout << "a child process could not be created, or"
        "its status could not be retrieved!" << endl;
    else
        printWaitStatus(nullptr, ret);


    return EXIT_SUCCESS;
}