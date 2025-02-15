#ifndef MINITALK_H
#define MINITALK_H

# include <unistd.h> // for pause function.
# include <signal.h> // for sigaction and signal handling.
# include <stdlib.h> // for constants like EXIT_FAILURE / EXIT_SUCCESS.
# include <stdbool.h> // for boolean flags

// string to integer.
long ft_atoi(const char *str);
// reseting global buffer.
void	ft_bzero(void *s, size_t n);

// for printing.
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

# include <stdio.h> // for testing

#endif // MINITALK_H