#include "minitalk.h"

void    s_talk_protocol(int signum)
{
    if (signum == SIGUSR1)
        ft_putstr_fd("0", 1);
    else if (signum == SIGUSR2)
        ft_putstr_fd("1", 1);
}


int main(void)
{
    struct  sigaction sa;

    
    signal(SIGUSR1, s_talk_protocol);
    signal(SIGUSR2, s_talk_protocol);

    printf("function  ==> %p\n function address ==> %p\n", s_talk_protocol, &s_talk_protocol);

    int serv_pid;
    serv_pid = getpid();

    ft_putstr_fd("The Server Has Started, Server PID Is: [ ", 1);
    ft_putnbr_fd(serv_pid,1);
    ft_putstr_fd(" ].\n", 1);
    while (1)
        pause();
    exit (EXIT_SUCCESS);
}