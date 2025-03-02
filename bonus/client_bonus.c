/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:38:42 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/20 17:39:54 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static t_client	g_client;

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
		while (!g_client.g_ready)
			usleep(1);
		g_client.g_ready = 0;
		i--;
	}
}

void	ack_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1 && g_client.og_pid == info->si_pid)
		g_client.g_ready = 1;
	else if (signum == SIGUSR2 && g_client.og_pid == info->si_pid)
	{
		ft_putstr_fd("Message Sent!\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

bool	pid_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	error_check(bool argc_not_3)
{
	if (argc_not_3)
	{
		ft_putstr_fd("Usage: ./client <server-pid>  <message>\n", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					i;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ack_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc == 3)
	{
		i = 0;
		g_client.og_pid = ft_atoi(argv[1]);
		if (!pid_is_digit(argv[1]) || g_client.og_pid == -1
			|| g_client.og_pid == 0)
			return (ft_putstr_fd("Invalid Pid.\n", STDERR_FILENO), EXIT_FAILURE);
		while (argv[2][i])
			ft_encrypt(g_client.og_pid, argv[2][i++]);
		ft_encrypt(g_client.og_pid, argv[2][i]);
	}
	error_check(argc != 3);
	return (EXIT_SUCCESS);
}
