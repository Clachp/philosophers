/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/05 14:12:39 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_has_to_die(t_data *data, t_philo philo)
{
	pthread_mutex_lock(&data->lock);
	if ((now(data) - philo.last_meal > data->time_to_die && \
	philo.is_eating == 0))
	{
		pthread_mutex_unlock(&data->lock);
		print_status(now(data), data->philo, "died");
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->die);
		return (1);
	}
	if (data->total == data->meals_nbr)
	{
		pthread_mutex_lock(&data->die);
		data->has_to_die = 1;
		pthread_mutex_unlock(&data->lock);
		pthread_mutex_unlock(&data->die);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}

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

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->die);
	pthread_mutex_destroy(&data->meals_lock);
	free(data->philo);
	free(data->forks);
	free(data);
}

void	throw_error(char *str, t_data *data)
{
	printf("%d\n", str);
	destroy_data(data);
}

void	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	if (data->philo_nbr == 1)
	{
		if (pthread_create(&data->philo->tid, NULL, solo_routine, data->philo) != 0)
			return (throw_error("Error creating thread", data));
		pthread_join(data->philo->tid, NULL);
		return ;
	}
	if (pthread_create(&data->monitor, NULL, supervise, data) != 0)
		return (throw_error("Error creating thread", data));
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philo[i].tid, NULL, start_routine, \
		&data->philo[i]) != 0)
			return (throw_error("Error creating thread", data));
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
