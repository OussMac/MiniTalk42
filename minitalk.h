#ifndef MINITALK_H
#define MINITALK_H

# include <unistd.h> // for pause function.
# include <signal.h> // for sigaction and signal handling.
# include <stdlib.h> // for constants like EXIT_FAILURE / EXIT_SUCCESS.

// string to integer.
long ft_atoi(const char *str);

// for printing.
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

# include <stdio.h> // for testing

#endif // MINITALK_H