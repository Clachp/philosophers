/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/28 18:28:47 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*supervise(void *arg)
{
	t_data	*data;
	time_t	time;
	int	i;
	
	data = (t_data*)arg;
	i = 0;
	while (1)
	{
		if (i == data->philo_nbr)
			i = 0; 
		pthread_mutex_lock(&data->death_lock);
		time = now(data) - data->philo[i].last_meal;
		if (time > data->time_to_die)
		{
			data->has_to_die = 1;
			pthread_mutex_unlock(&data->death_lock);
			break ;
		}
		pthread_mutex_unlock(&data->death_lock);
		i++;
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].last_meal = now(data);
		i++;
	}
	pthread_create(&data->death_monitor, NULL, supervise, data);
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philo[i].tid, NULL, start_routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
	pthread_join(data->death_monitor, NULL);
}