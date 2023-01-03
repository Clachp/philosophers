/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:32:26 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/03 16:52:00 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_struct(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (-1);
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (-1);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	int		i;

	i = 0;
	data->philo_nbr = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long (argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->has_to_die = 0;
	data->meals_nbr = -1;
	if (argv[5])
		data->meals_nbr = ft_atoi_long(argv[5]);
	if (allocate_struct(data) == -1)
		return (-1);
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->print, NULL);
	return (0);
}

int	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals = data->meals_nbr;
		data->philo[i].is_eating = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = &data->forks[i];
		if (i == data->philo_nbr - 1)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
		pthread_mutex_init(&data->philo[i].plock, NULL);
		i++;
	}
	return (0);
}
