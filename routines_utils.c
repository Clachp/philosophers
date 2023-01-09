/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/09 17:21:49 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	print_status(now(philo->data), philo, "is sleeping");
	ft_usleep(philo->data, philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	temp;

	print_status(now(philo->data), philo, "is thinking");
	temp = (philo->data->time_to_die - \
	(philo->data->time_to_eat + philo->data->time_to_sleep)) / 2;
	if (temp >= 0)
		ft_usleep(philo->data, temp);
}

int	set_has_to_die(t_data *data, t_philo philo)
{
	pthread_mutex_lock(&data->meals_lock);
	if (data->total == data->meals_nbr)
	{
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->die);
		pthread_mutex_unlock(&data->meals_lock);
		return (1);
	}
	if ((now(data) - philo.last_meal > data->time_to_die && \
	philo.is_eating == 0))
	{
		if (philo.meals < data->meals_nbr)
			print_status(now(data), &philo, "died");
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->die);
		pthread_mutex_unlock(&data->meals_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->meals_lock);
	return (0);
}

void	eat(t_philo *philo, pthread_mutex_t *frk_1, pthread_mutex_t *frk_2)
{
	pthread_mutex_lock(frk_1);
	print_status(now(philo->data), philo, "has taken a fork");
	pthread_mutex_lock(frk_2);
	print_status(now(philo->data), philo, "has taken a fork");
	print_status(now(philo->data), philo, "is eating");
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(frk_1);
	pthread_mutex_unlock(frk_2);
	pthread_mutex_lock(&philo->data->eating_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->eating_lock);
	go_sleep(philo);
	usleep(100);
	think(philo);
}

void	print_status(time_t time, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->die);
	if (philo->data->has_to_die == 0)
		printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->die);
	if (ft_strcmp(status, "is eating") == 0)
	{
		pthread_mutex_lock(&philo->data->meals_lock);
		philo->last_meal = now(philo->data);
		if (philo->data->meals_nbr > -1)
			philo->meals++;
		pthread_mutex_lock(&philo->data->eating_lock);
		philo->is_eating = 1;
		pthread_mutex_unlock(&philo->data->eating_lock);
		pthread_mutex_unlock(&philo->data->meals_lock);
	}
}
