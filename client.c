#include "minitalk.h"

volatile sig_atomic_t ready = 0;

void    ft_encrypt(int s_pid, char letter) // A --> 65 --> 0100 0001 --> 1000 0010
{
    int     i;
    char    c;
    int     failure;

    i = 7;
    while (i >= 0)
    {
        c = letter >> i;
        if (c & 1)
            failure = kill(s_pid, SIGUSR2);
        else
            failure = kill(s_pid, SIGUSR1);
        if (failure == -1)
        {
            ft_putstr_fd(" Failed Sending Signal.\n", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
        while (!ready)
            pause();
        ready = 0;
        i--;
    }
}

void    ack_handler(int signum)
{
    if (signum == SIGUSR1)
        ready = 1;
}


int main(int argc, char *argv[])
{
    signal(SIGUSR1, ack_handler);
    if (argc != 3)
    {
        ft_putstr_fd("Usage : ./client <server-pid>  <message> \n", 1);
        return (EXIT_FAILURE);
    }
    else
    {
        int i;
        int s_pid;

        i = 0;
        s_pid = ft_atoi(argv[1]);
        while(argv[2][i])
        {
            ft_encrypt(s_pid, argv[2][i]);
            i++;
        }
        ft_encrypt(s_pid, argv[2][i]);
    }
    return (EXIT_SUCCESS);
}
