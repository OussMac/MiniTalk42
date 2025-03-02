/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:40:28 by oimzilen          #+#    #+#             */
/*   Updated: 2025/02/20 17:31:48 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
}

long	ft_atoi(const char *str)
{
	int		i;
	long	pow;
	int		s;

	i = 0;
	s = 1;
	pow = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		pow = (pow * 10) + (str[i] - 48);
		i++;
	}
	return (pow * s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	if (n == 0)
		return ;
	i = 0;
	ptr = (unsigned char *) s;
	while (i < n)
		ptr[i++] = 0;
}
