/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/16 22:24:50 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t now(time_t start)
{
	return(get_time() - start);
}

void	take_forks(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(philo.right_fork);
	print_status(time, &philo, "has taken a fork");
	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(&philo.left_fork);
	print_status(time, &philo, "has taken a fork");
	philo.is_eating = 1;
}	

void	drop_forks(t_philo philo)
{
	pthread_mutex_unlock(&philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
}


void	eat_right_fork(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(philo.right_fork);
	print_status(time, &philo, "has taken a fork");
	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(&philo.left_fork);
	print_status(time, &philo, "has taken a fork");
	philo.is_eating = 1;
	time = get_time() - philo.data->start_time;
	print_status(time, &philo, "is eating");
	usleep(philo.data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	// print_status(time, &philo, "hdgfjhsdgf is eating\n");
}

void	eat_left_fork(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(&philo.left_fork);
	print_status(time, &philo, "has taken a fork");
	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(philo.right_fork);
	print_status(time, &philo, "has taken a fork");
	philo.is_eating = 1;
	time = get_time() - philo.data->start_time;
	print_status(time, &philo, "is eating");
	usleep(philo.data->time_to_eat * 1000);
	pthread_mutex_unlock(philo.right_fork);
	pthread_mutex_unlock(&philo.left_fork);
	// print_status(time, &philo, "hdgfjhsdgf is eating\n");
}

void	think(t_philo philo)
{
	time_t time;

	time = get_time() - philo.data->start_time;
	print_status(time, &philo, "is thinking");
	//usleep(time * 10);
}

void	go_sleep(t_philo philo)
{
	time_t	time;

	time = get_time() - philo.data->start_time;
	print_status(time, &philo, "is sleeping");
	usleep(philo.data->time_to_sleep * 1000);
}

// int		continue(t_data *data)
// {
// 	pthread_mutex_lock(data->lock);
// 	if (meals)
// }

void	*start_routine(void *arg)
{
	t_philo philo;
	philo = *(t_philo*)arg;
	// pthread_mutex_lock(&philo.data->lock);
	// dprintf(2, "%ld je suis philo %d\n", now(philo.data->start_time), philo.id);
	if (philo.id % 2)
			usleep(100000);
	// dprintf(2, "%ld je suis philo %d je commence mainetnant\n", now(philo.data->start_time), philo.id);
	while (philo.meals)
	{
		eat_right_fork(philo);
		philo.is_eating = 0;
		go_sleep(philo);
		// printf("meals nbr : %d\n", philo.meals);
		print_status((get_time() - philo.data->start_time), &philo, "timer");
		philo.meals--;
	}
	// pthread_mutex_unlock(&philo.data->lock);
	return (0);
}