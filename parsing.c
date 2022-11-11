/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:32:26 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/11 18:38:19 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	r;

	if (nptr == NULL)
		return (0);
	i = 0;
	s = 1;
	r = 0;
	while ((nptr[i] >= 7 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -s;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
	}
	return (s * r);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		write (1, "-2147483648", 11);
	else if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n >= 0 && n <= 9)
	{
		c = '0' + n;
		write (1, &c, 1);
	}
	else if (n != -2147483648)
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putnbr_fd(n % 10, 1);
	}
}

void	ft_putstr(char *s)
{
	while (s && *s)
		write (1, &*s++, 1);
}