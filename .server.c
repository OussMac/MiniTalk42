#include "minitalk.h"

char decrypt(unsigned char *letter);

// global variable to keep track of index in each letter buffer and the content of it.
unsigned char   letter[8];

void    process_letter(int signum, siginfo_t *info, void *context)
{
    unsigned char   c;
    static int      i;

    (void)context, (void)info;

    if (signum == SIGUSR1)
        letter[i] = '0';
    else if (signum == SIGUSR2)
        letter[i] = '1';
    kill(info->si_pid, SIGUSR1);
    i++;

    if (i == 8)
    {
        c = decrypt(letter);
        if (c == '\0')
            write(STDIN_FILENO, "\n", 1);
        else
            write(STDIN_FILENO, &c, 1);
        ft_bzero(letter, 8);
        i = 0;
    }
    return ;
}

int main(void)
{

    struct sigaction sa;


    sa.sa_sigaction = process_letter;
    sa.sa_flags = SA_SIGINFO;

    ft_bzero(letter, 8);

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1); 
    sigaddset(&sa.sa_mask, SIGUSR2);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    int serv_pid;
    serv_pid = getpid();

    ft_putstr_fd("The Server Has Started, Server PID Is: [ ", 1);
    ft_putnbr_fd(serv_pid,1);
    ft_putstr_fd(" ].\n", 1);
    while (1)
        pause();
    exit (EXIT_SUCCESS);
}

// new decrypt

char decrypt(unsigned char *letter)
{
    unsigned char c = 0;
    int i = 0;

    while (i < 8)
    {
        c <<= 1;
        if (letter[i] == '1')
            c |= 1;
        i++;
    }
    return (c);
}
