/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/19 19:13:25 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t now(time_t start)
{
	return(get_time() - start);
}

void	eat_right_fork(t_philo *philo)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->right_fork);
	print_status(time, philo, "has taken a right fork");
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->left_fork);
	print_status(time, philo, "has taken a left fork");
	philo->is_eating = 1;
	if (philo->last_meal)
		philo->last_meal = get_time() - philo->last_meal;
	else	
		philo->last_meal = get_time() - philo->data->start_time;
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_left_fork(t_philo *philo)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->left_fork);
	print_status(time, philo, "has taken a left fork");
	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(philo->right_fork);
	print_status(time, philo, "has taken a right fork");
	philo->is_eating = 1;
	if (philo->last_meal)
		philo->last_meal = get_time() - philo->last_meal;
	else	
		philo->last_meal = get_time() - philo->data->start_time;
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	think(t_philo *philo)
{
	time_t time;

	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is thinking");
}

void	go_sleep(t_philo *philo)
{
	time_t	time;

	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

// int		continue(t_data *data)
// {
// 	pthread_mutex_lock(data->lock);
// 	if (meals)
// }

void	*start_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo*)arg;
	//pthread_create(&philo->data->death_monitor, NULL, supervise, arg);
	while (philo->has_to_die == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->last_meal > philo->data->time_to_die)
		{
			philo->has_to_die = 1;
			print_status(get_time() - philo->data->start_time, philo, "died");
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->id % 2)
			eat_right_fork(philo);
		else 
			eat_left_fork(philo);
		philo->is_eating = 0;
		go_sleep(philo);
		think(philo);
		if (philo->meals)
		{
			philo->meals--;
			if (philo->meals == 0)
				break ;
		}
	}
	//pthread_join(philo->data->death_monitor, NULL);
	return (0);
}