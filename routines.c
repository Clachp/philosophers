/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/04 18:09:36 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	print_status(now(philo->data), philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = now(philo->data);
	pthread_mutex_unlock(&philo->data->lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(fork_1);
	pthread_mutex_unlock(fork_2);
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->meals_lock);
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
