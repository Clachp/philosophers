/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:30:15 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/03 16:42:20 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t	get_time()
{
	struct timeval	t;
	time_t			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return (time);
}

long long	ft_atoi_long(const char *nptr)
{
	int	i;
	int	s;
	long long	r;

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

void	print_status(time_t time, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->has_to_die == 0)
		printf("%ldms philo %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
}
	