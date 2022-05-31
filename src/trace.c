#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

int main() {
    int status;
    int pid = fork();
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./child", "child", NULL);
    }
    printf("child pid: %d\n", pid);
    wait(NULL);
    ptrace(PTRACE_CONT, pid, 0, 0);
    wait(NULL);
    printf("parent\n");
    kill(pid, SIGKILL);
    return 0;
}
