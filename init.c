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

void	*sleep_routine(void *arg)
{
	t_philo philo;
	philo = *(t_philo*)arg;
	int time = 200;
	printf(" %dms, philo %d is sleeping\n", time, philo.id);
	return (0);
}

// forks = ressources partagees
void	*take_forks(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->left_fork);
	printf("Philo %d has taken a fork\n", philo->id);
	printf("Philo %d left fork : ", philo->id);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	return (NULL);
}

t_data	init_data(char **argv)
{
	t_data	data;

	data.n = ft_atoi(argv[1]);
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

	philo = malloc(sizeof(t_philo) * data.n);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data.n)
	{
		philo[i].id = i + 1;
//		philo[i].data->start_time = get_time();
		pthread_mutex_init(&philo[i].left_fork, NULL);
		if (i == data.n - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		pthread_create(&philo[i].tid, NULL, take_forks, &philo[i]);
		i++;
	}
	return (philo);
}