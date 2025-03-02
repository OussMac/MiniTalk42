/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:02 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/20 17:45:03 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static t_server	g_s;

void	print_sequence(unsigned char *bytes, int seq_size)
{
	int	i;

	i = 0;
	while (i < seq_size)
		write(STDOUT_FILENO, &bytes[i++], 1);
	g_s.c = 0;
	g_s.i = 0;
	g_s.seq_size = 0;
	ft_bzero(g_s.bytes, 4);
}

int	utf_sequence(int curr_si_pid)
{
	if (g_s.c <= 0x7F)
	{
		if (g_s.c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(curr_si_pid, SIGUSR2);
		}
		else
			write(STDOUT_FILENO, &g_s.c, 1);
		g_s.c = 0;
		g_s.i = 0;
		ft_bzero(g_s.bytes, 4);
		return (0);
	}
	g_s.bytes[g_s.seq_size++] = g_s.c;
	if ((g_s.bytes[0] & 0b11100000) == 0b11000000 && g_s.seq_size == 2)
		return (print_sequence(g_s.bytes, g_s.seq_size), 0);
	else if ((g_s.bytes[0] & 0b11110000) == 0b11100000 && g_s.seq_size == 3)
		return (print_sequence(g_s.bytes, g_s.seq_size), 0);
	else if ((g_s.bytes[0] & 0b11111000) == 0b11110000 && g_s.seq_size == 4)
		return (print_sequence(g_s.bytes, g_s.seq_size), 0);
	g_s.c = 0;
	g_s.i = 0;
	return (0);
}

void	ft_decrypt(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_s.g_old_pid != 0 && info->si_pid != g_s.g_old_pid)
	{
		g_s.c = 0;
		g_s.i = 0;
		g_s.seq_size = 0;
		ft_bzero(g_s.bytes, 4);
	}
	g_s.g_old_pid = info->si_pid;
	g_s.c <<= 1;
	if (signum == SIGUSR2)
		g_s.c |= 1;
	g_s.i++;
	if (g_s.i == 8)
		utf_sequence(info->si_pid);
	usleep(37);
	kill(info->si_pid, SIGUSR1);
}

void	s_info(void)
{
	int	serv_pid;

	serv_pid = getpid();
	ft_putstr_fd("The s Has Started, s PID Is: [ ", STDOUT_FILENO);
	ft_putnbr_fd(serv_pid, STDOUT_FILENO);
	ft_putstr_fd(" ].\n", STDOUT_FILENO);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	(void)argc;
	if (argc != 1)
	{
		ft_putstr_fd("Usage : ./s \n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_decrypt;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	s_info();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
