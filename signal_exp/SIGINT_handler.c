#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum)
{
    printf("cought signal number %d\n", signum);
}

int main(void)
{
    // ctrl + c sends a signal to the process to interrupt it.
    signal(SIGINT, handler);
    while (1)
    {
        printf("forever loop lol %d\n", getpid());
        sleep(1);
    }
    return (EXIT_SUCCESS);
}