/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:02 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/17 17:45:24 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static t_server server;

void	utf_sequence(int curr_si_pid)
{
	if (server.c <= 0x7F)
	{
		if (server.c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(curr_si_pid, SIGUSR2);
		}
		else
			write(STDOUT_FILENO, &server.c, 1);
		server.c = 0;
		server.i = 0;
		ft_bzero(server.bytes, 4);
		return;
	}
	server.bytes[server.seq_size++] = server.c;
	if ((server.bytes[0] & 0b11100000) == 0b11000000 && server.seq_size == 2)
	{
		puts("count is 2");
		server.c = 0;
		server.i = 0;
		server.seq_size = 0;
		ft_bzero(server.bytes, 4);
		return;
	}
	if ((server.bytes[0] & 0b11110000) == 0b11100000 && server.seq_size == 3)
	{
		puts("count is 3");
		server.c = 0;
		server.i = 0;
		server.seq_size = 0;
		ft_bzero(server.bytes, 4);
		return;
	}
	if ((server.bytes[0] & 0b11111000) == 0b11110000 && server.seq_size == 4)
	{
		puts("count is 4");
		server.c = 0;
		server.i = 0;
		server.seq_size = 0;
		ft_bzero(server.bytes, 4);
		return;
	}
	server.c = 0;
	server.i = 0;
	puts("dkhl wlkn khrj");
}

void	ft_decrypt(int signum, siginfo_t *info, void *context)
{

	(void)context;
	if (server.g_old_pid != 0 && info->si_pid != server.g_old_pid)
	{
		server.c = 0;
		server.i = 0;
		server.seq_size = 0;
		ft_bzero(server.bytes, 4);
	}
	server.g_old_pid = info->si_pid;
	server.c <<= 1;
	if (signum == SIGUSR2)
		server.c |= 1;
	server.i++;
	if (server.i == 8)
		utf_sequence(info->si_pid);
	usleep(37);
	kill(info->si_pid, SIGUSR1);
}

void	server_info(void)
{
	int	serv_pid;

	serv_pid = getpid();
	ft_putstr_fd("The Server Has Started, Server PID Is: [ ", STDOUT_FILENO);
	ft_putnbr_fd(serv_pid, STDOUT_FILENO);
	ft_putstr_fd(" ].\n", STDOUT_FILENO);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	(void)argc;
	if (argc != 1)
	{
		ft_putstr_fd("Usage : ./server \n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_decrypt;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_info();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
