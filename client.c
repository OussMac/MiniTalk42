#include "minitalk.h"

int main(int ac, char *av[])
{
    int srv_pid;
    if (ac == 3)
    {
        srv_pid = ft_atoi(av[1]);

        if (av[2][0] == '0')
            kill(srv_pid, SIGUSR1);
        else if (av[2][0] == '1')
            kill(srv_pid, SIGUSR2);
    }
    else
        exit (EXIT_FAILURE);
    exit (EXIT_SUCCESS);   
}