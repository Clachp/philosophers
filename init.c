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

void	take_forks(t_philo philo)
{
	pthread_mutex_lock(philo.right_fork);
	pthread_mutex_lock(&philo.left_fork);
	printf("Philo %d has taken a fork\n", philo.id);
	philo.is_eating = 1;
}	

void	drop_forks(t_philo philo)
{
	pthread_mutex_unlock(&philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}


void	eat(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	take_forks(philo);
	printf("%ldms, Philo %d is eating\n", time, philo.id);
	usleep(philo.data->time_to_eat * 1000);
	drop_forks(philo);
}

void	think(t_philo philo)
{
	time_t time;

	time = get_time() - philo.data->start_time;
	printf("%ld philo %d is thinking\n", time, philo.id);
	usleep(time * 10);
}

void	go_sleep(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	printf("%ld philo %d is sleeping\n", time, philo.id);
	usleep(3000);
}

void	*start_routine(void *arg)
{
	t_philo philo;
	philo = *(t_philo*)arg;
	pthread_mutex_lock(&philo.data->lock);
	while (philo.meals)
	{
		printf("PHILO CREATE : %d\n", philo.id);
		think(philo);
		go_sleep(philo);
		eat(philo);
		printf("meals nbr : %d\n", philo.meals);
		philo.meals--;
	}
	pthread_mutex_unlock(&philo.data->lock);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	int		i;

	data->philo_nbr = ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if(!data->forks)
		return (-1);	
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi (argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_nbr = ft_atoi(argv[5]);
	else
		data->meals_nbr = -1;
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int init_philo(t_data *data, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals = data->meals_nbr;
		philo[i].is_eating = 0;
		philo[i].left_fork = data->forks[i];
		if (i == data->philo_nbr - 1)
			philo[i].right_fork = &philo[0].left_fork;
		else
			philo[i].right_fork = &philo[i + 1].left_fork;
		i++;
	}
	return (0);
}

void	init_threads(t_philo *philo, t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&philo[i].tid, NULL, start_routine, &philo[i]);
		printf("Apres thred\n");
		i++;
	}
	i = 0;
	while (i < philo->data->philo_nbr)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
}