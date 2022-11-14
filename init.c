/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:32:26 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/14 15:05:42 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_arg(char **argv)
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}


t_data	init_data(char **argv)
{
	t_data	data;

	// data = malloc(sizeof(t_data));
	// if (!data)
	// 	retrun (NULL);
	data.nbr = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi (argv[3]);
	data.time_to_think = 0;
	data.time_to_sleep = ft_atoi(argv[4]);
	return (data);
}

// initialiser un tableau de structures 
t_philo	*init_philo(t_data data)
{
	t_philo *philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data.nbr);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data.nbr)
	{
		philo[i].id = i + 1;
		//pthread_create(&philo[i]->tid, NULL, sleep_routine(data.time_to_sleep), NULL);
		i++;
	}
	return (philo);

}