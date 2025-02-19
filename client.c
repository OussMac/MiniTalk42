/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:38:42 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/17 17:56:22 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ready = 0;

void	ft_encrypt(int s_pid, char letter)
{
	int		i;
	int		failure;
	char	c;

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
		while (!g_ready)
			usleep(1);
		g_ready = 0;
		i--;
	}
}

void	ack_handler(int signum)
{
	if (signum == SIGUSR1)
		g_ready = 1;
}

int	main(int argc, char *argv[])
{
	int	i;
	int	s_pid;

	signal(SIGUSR1, ack_handler);
	if (argc != 3)
	{
		ft_putstr_fd("Usage : ./client <server-pid>  <message> \n", 1);
		return (EXIT_FAILURE);
	}
	else
	{
		i = 0;
		s_pid = ft_atoi(argv[1]);
		if (!pid_is_digit(argv[1]) || s_pid == -1 || s_pid == 0)
		{
			ft_putstr_fd("Invalid Pid.\n", 1);
			return (EXIT_FAILURE);
		}
		while (argv[2][i])
			ft_encrypt(s_pid, argv[2][i++]);
		ft_encrypt(s_pid, argv[2][i]);
	}
	return (EXIT_SUCCESS);
}
