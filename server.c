#include "minitalk.h"

char    decrypt(char *letter);

// global variable to keep track of index in each letter buffer and the content of it.
typedef struct s_server
{
    char    letter[9];
    int     i;
}           t_server;
// declaration and initialization of the global variable.
t_server server;

void    process_letter(int signum, siginfo_t *info, void *context)
{
    char c;
    (void)context;
    (void)info;

    if (signum == SIGUSR1)
        server.letter[server.i] = '0';
    else if (signum == SIGUSR2)
        server.letter[server.i] = '1';
    server.i++;

    if (server.i == 8)
    {
        server.letter[server.i] = '\0';
        c = decrypt(server.letter);
        ft_putchar_fd(c, 1);
        ft_bzero(server.letter, 9);
        server.i = 0;
    }
    return ;
}

int main(void)
{

    struct sigaction sa;


    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1); 
    sigaddset(&sa.sa_mask, SIGUSR2);
    sa.sa_sigaction = process_letter;
    sa.sa_flags = SA_SIGINFO;

    ft_bzero(server.letter, 9);

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

char    decrypt(char *letter)
{
    int             i;
    unsigned char   c;
    int             ascii;

    c = 0;
    i = 0;
    ascii = 128;
    while (letter[i])
    {
        if (letter[i] == '0')
            c += 0;
        else if (letter[i] == '1')
            c += ascii;
        i++;
        ascii /= 2;
    }
    // printf("%d\n", c);
    return (c);
}

// void    s_talk_protocol(int signum)
// {
//     unsigned char   c;
//     char            *letter;
//     letter = process_letter(signum);
//     c = decrypt(letter);
//     // ft_putchar_fd(c, 1);
// }

