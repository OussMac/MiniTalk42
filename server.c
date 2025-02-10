#include "minitalk.h"

void    handler(int signum)
{
    if (signum == SIGUSR1)
        printf("0\n");
    else if (signum == SIGUSR2)
        printf("1\n");
}


int main(void)
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    int serv_pid;
    serv_pid = getpid();

    ft_putstr_fd("The Server Has Started, Server PID Is: [ ", 1);
    ft_putnbr_fd(serv_pid,1);
    ft_putstr_fd(" ].\n", 1);
    while (1)
        pause();
    exit (EXIT_SUCCESS);
}