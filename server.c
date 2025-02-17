#include "minitalk.h"

__pid_t old_pid;

void    decrypt(int signum, siginfo_t *info, void *context)
{
    (void)context;
    static unsigned char c;
    static int i;

    if (info->si_pid != old_pid)
    {
        c = 0;
        i = 0;
    }
    old_pid = info->si_pid;
    c <<= 1;
    if (signum == SIGUSR2)
        c |= 1;
    usleep(42);
    kill(info->si_pid, SIGUSR1);
    i++;
    if (i == 8)
    {
        if (c == '\0')
            write(STDOUT_FILENO, "\n", 1);
        else
            write(STDOUT_FILENO, &c, 1);
        c = 0;
        i = 0;
    }
}


int main(int argc, char *argv[])
{
    struct sigaction sa;
    int serv_pid;
    (void)argc;
    if (argc != 1)
    {
        ft_putstr_fd("Usage : ./server \n", 1);
        return (EXIT_FAILURE);
    }
    serv_pid = getpid();
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = decrypt;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1); 
    sigaddset(&sa.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    ft_putstr_fd("The Server Has Started, Server PID Is: [ ", 1);
    ft_putnbr_fd(serv_pid,1);
    ft_putstr_fd(" ].\n", 1);
    while (1)
        pause();
    return (EXIT_SUCCESS);
}
