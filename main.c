/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:35:08 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/05 15:44:25 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi_long(argv[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
	if (data->philo_nbr > 1)
		pthread_join(data->monitor, NULL);
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

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_arg(argv) == -1)
	{
		printf("Wrong input format\n");
		return (0);
	}
	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (printf("Error with allocation memory\n"), 0);
		if (init_data(data, argv) == -1)
			return (printf("Error initializing data\n"), 0);
		init_philo(data);
		init_threads(data);
		destroy_data(data);
	}
	else
		printf("Wrong argument number\n");
	return (0);
}
