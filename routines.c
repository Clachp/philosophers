/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:39 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/26 18:05:53 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

time_t now(time_t start)
{
	return(get_time() - start);
}

void	eat(t_philo *philo, pthread_mutex_t *fork_1, pthread_mutex_t *fork_2)
{
	time_t	time;

	pthread_mutex_lock(fork_1);
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "has taken a fork");
	pthread_mutex_lock(fork_2);
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "has taken a fork");
	philo->is_eating = 1;
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal = get_time() - philo->data->start_time;
	//printf("philo %d last meal in eat : %ld\n", philo->id, philo->last_meal);
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(fork_1);
	pthread_mutex_unlock(fork_2);
	
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

void	*start_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo*)arg;
	
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->has_to_die == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->id % 2)
		{
			eat(philo, philo->right_fork, philo->left_fork);
			go_sleep(philo);
			think(philo);
		}
		else
		{
			eat(philo, philo->left_fork, philo->right_fork);
			go_sleep(philo);
			think(philo);
		}
		philo->is_eating = 0;
		if (philo->meals)
		{
			philo->meals--;
			if (philo->meals == 0)
				break ;
		}
	}
	return (0);
}