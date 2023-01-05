/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/05 16:15:23 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	print_status(now(philo->data), philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	eat(t_philo *philo, pthread_mutex_t *frk_1, pthread_mutex_t *frk_2)
{
	pthread_mutex_lock(frk_1);
	print_status(now(philo->data), philo, "has taken a fork");
	pthread_mutex_lock(frk_2);
	print_status(now(philo->data), philo, "has taken a fork");
	print_status(now(philo->data), philo, "is eating");
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = now(philo->data);
	pthread_mutex_unlock(&philo->data->lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(frk_1);
	pthread_mutex_unlock(frk_2);
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->meals_lock);
	go_sleep(philo);
	print_status(now(philo->data), philo, "is thinking");
}

int	set_has_to_die(t_data *data, t_philo philo)
{
	pthread_mutex_lock(&data->lock);
	if (data->total == data->meals_nbr)
	{
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->lock);
		pthread_mutex_unlock(&data->die);
		return (1);
	}
	if ((now(data) - philo.last_meal > data->time_to_die && \
	philo.is_eating == 0))
	{
		pthread_mutex_unlock(&data->lock);
		printf("philo>meals : %d || meals_nbr : %d\n", philo.meals, data->meals_nbr);
		if (philo.meals < data->meals_nbr)
			print_status(now(data), data->philo, "died");
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->die);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}
