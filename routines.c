/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/03 16:54:38 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	now(t_data *data)
{
	return (get_time() - data->start_time);
}

void	go_sleep(t_philo *philo)
{
	print_status(now(philo->data), philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	eat(t_philo *philo, pthread_mutex_t *fork_1, pthread_mutex_t *fork_2)
{
	pthread_mutex_lock(fork_1);
	print_status(now(philo->data), philo, "has taken a fork");
	pthread_mutex_lock(fork_2);
	print_status(now(philo->data), philo, "has taken a fork");
	philo->is_eating = 1;
	print_status(now(philo->data), philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = now(philo->data);
	pthread_mutex_unlock(&philo->data->lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(fork_1);
	pthread_mutex_unlock(fork_2);
	go_sleep(philo);
	print_status(now(philo->data), philo, "is thinking");
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
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->id % 2)
			eat(philo, philo->right_fork, philo->left_fork);
		else
			eat(philo, philo->left_fork, philo->right_fork);
		philo->is_eating = 0;
		if (philo->meals)
		{
			philo->meals--;
			if (philo->meals == 0)
				break ;
		}
	}
	return (0);
}
