#include "minitalk.h"


char *char_to_bits(unsigned char ascii)
{
    char    *bits;
    char    rev_bits[8];
    int     i;
    int     j;

    bits = (char *) malloc (sizeof(char) * 9);
    while (ascii > 0)
    {
        rev_bits[i++] = (ascii % 2) + 48;
        ascii /= 2;
    }
    while (i < 8)
        rev_bits[i++] = '0';
    j = 0;
    while (i > 0)
    {
        i--;
        bits[j] = rev_bits[i];
        j++;
    }
    bits[j] = '\0';
    printf("%s\n", bits);
    return (bits);
}

void    process_letter(char *letter, int srv_pid)
{
    int i;
    
    i = 0;
    while (letter[i])
    {
        if (letter[i] = '0')
            kill(srv_pid, SIGUSR1);
        else if (letter[i] = '1')
            kill(srv_pid, SIGUSR2);
        i++;
    }
}


void    talk_protocol(char *str, int srv_pid)
{
    int i;
    char *bits;

    i = 0;
    while (str[i])
    {
        bits = char_to_bits(str[i]);
        process_letter(bits, srv_pid);
        free(bits);
        i++;
    }
}

int main(int ac, char *av[])
{
    int srv_pid;
    if (ac == 3)
    {
        srv_pid = ft_atoi(av[1]);
        talk_protocol(av[2], srv_pid);
    }
    else
        exit (EXIT_FAILURE);
    exit (EXIT_SUCCESS);   
}