/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:39:56 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/20 17:52:14 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_server
{
	int				g_old_pid;
	unsigned char	bytes[4];
	int				seq_size;
	unsigned char	c;
	int				i;
}	t_server;

typedef struct s_client
{
	volatile sig_atomic_t	g_ready;
	int						og_pid;
}	t_client;

long	ft_atoi(const char *str);

void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_bzero(void *s, size_t n);

#endif // MINITALK_H
