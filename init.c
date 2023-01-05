/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:32:26 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/05 16:21:44 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_struct(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
	{
		free(data);
		return (-1);
	}
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
	{
		free(data->forks);
		free(data);
		return (-1);
	}
	return (0);
}

void	throw_error(char *str, t_data *data)
{
	printf("%s\n", str);
	destroy_data(data);
}

int	init_data(t_data *data, char **argv)
{
	int		i;

	data->philo_nbr = ft_atoi_long(argv[1]);
	data->time_to_die = ft_atoi_long(argv[2]);
	data->time_to_eat = ft_atoi_long (argv[3]);
	data->time_to_sleep = ft_atoi_long(argv[4]);
	data->has_to_die = 0;
	data->total = 0;
	data->meals_nbr = -1;
	if (argv[5])
		data->meals_nbr = ft_atoi_long(argv[5]);
	if (allocate_struct(data) == -1)
		return (printf("Error with allocation memory\n"), -1);
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->die, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	return (0);
}

void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].meals = -2;
		if (data->meals_nbr != -1)
			data->philo[i].meals = 0;
		data->philo[i].is_eating = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = &data->forks[i];
		if (i == data->philo_nbr - 1)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

void	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	if (data->philo_nbr == 1)
	{
		if (pthread_create(&data->philo->tid, NULL, solo_routine, \
		data->philo) != 0)
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
}
