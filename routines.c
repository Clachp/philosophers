/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/09 18:01:49 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervise(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i == data->philo_nbr)
			i = 0;
		if (set_has_to_die(data, data->philo[i]) == 1)
			break ;
		i++;
	}
	return (NULL);
}

void	*solo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%ldms philo %d has taken a fork\n", now(philo->data), philo->id);
	ft_usleep(philo->data, philo->data->time_to_die);
	printf("%ldms philo %d died\n", now(philo->data), philo->id);
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->die);
		if (philo->data->has_to_die == 1)
			return (pthread_mutex_unlock(&philo->data->die), NULL);
		pthread_mutex_unlock(&philo->data->die);
		pthread_mutex_lock(&philo->data->meals_lock);
		if (philo->meals == philo->data->meals_nbr)
		{
			philo->data->total++;
			return (pthread_mutex_unlock(&philo->data->meals_lock), NULL);
		}
		pthread_mutex_unlock(&philo->data->meals_lock);
		if (philo->id % 2)
			eat(philo, philo->right_fork, philo->left_fork);
		else
			eat(philo, philo->left_fork, philo->right_fork);
	}
	return (0);
}
