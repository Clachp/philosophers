/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/05 15:30:19 by cchapon          ###   ########.fr       */
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
	pthread_mutex_lock(philo->right_fork);
	print_status(now(philo->data), philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	print_status(now(philo->data), philo, "died");
	philo->data->has_to_die = 1;
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->has_to_die == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		if (philo->meals == philo->data->meals_nbr)
		{
			philo->data->total++;
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->id % 2)
			eat(philo, philo->right_fork, philo->left_fork);
		else
			eat(philo, philo->left_fork, philo->right_fork);
	}
	return (0);
}
