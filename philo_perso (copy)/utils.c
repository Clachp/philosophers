/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:30:15 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/28 18:23:39 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t	get_time()
{
	struct timeval	t;
	time_t			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * (time_t)1000) + (t.tv_usec / 1000);
	return (time);
}

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

void	print_status(time_t time, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	printf("philo %d has to die = %d\n", philo->id, philo->data->has_to_die);
	printf("%ldms philo %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print);
}