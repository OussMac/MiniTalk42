#include "minitalk.h"





volatile sig_atomic_t ready = 0;

void encrypt(int s_pid, unsigned char letter) // A --> 65 --> 0100 0001 --> 1000 0010
{
    int i;
    unsigned char c;

    i = 7;
    while (i >= 0)
    {
        c = letter >> i;
        if (c & 1)
            kill(s_pid, SIGUSR2);
        else
            kill(s_pid, SIGUSR1);
        while (!ready)
            pause();
        ready = 0;
        i--;
    }
}


void    ack_handler(int signum)
{
    (void)signum;
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
            encrypt(s_pid, argv[2][i]);
            i++;
        }
        encrypt(s_pid, argv[2][i]);
    }
    return (EXIT_SUCCESS);
}
