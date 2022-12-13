/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:57:51 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/13 16:43:01 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data data, char **argv)
{

	data.n = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi (argv[3]);
	data.time_to_think = 0;
	data.time_to_sleep = ft_atoi(argv[4]);
}

void	init_philo(t_data data)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data.n);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data.n)
	{
		philo[i].id = i + 1;
		philo[i].data = &data;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		if (i == data.n - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
}

void	init(t_data data, char **argv)
{
	init_data(data, argv);
	init_philo(data)
}

