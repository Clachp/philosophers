/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/27 15:34:06 by cchapon          ###   ########.fr       */
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
		usleep(5000);
		pthread_mutex_lock(&data->lock);
		// pb : last meal est toujours egal a 0
		printf("philo %d last meal in supervise : %ld\n", data->philo[i].id, data->philo[i].last_meal);
		if (data->philo[i].last_meal == 0)
		{
			time = get_time() - data->start_time;
		}
		else
		{
			time = get_time() - data->philo[i + 1].last_meal;
		}
		//printf("philo nbr : %d || time : %ld\n", data->philo[i].id, time);
	// checker le temps pour chaque philo (boucler sur philo[i])
	
		if (time > data->time_to_die)
		{
			pthread_mutex_unlock(&data->lock);	
			data->philo[i].has_to_die = 1;
			print_status(now(data), &data->philo[i], "died");
			
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		i++;
	}
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
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

/*void	*supervise(void *arg)
{
	t_philo	*philo;
	time_t	time;
	int	i;
	

	philo = (t_philo*)arg;
	i = 0;
	while (1)
	{
		if (i == philo->data->philo_nbr)
			i =0;
		pthread_mutex_lock(&philo->data->lock);
		printf("philo %d last meal in supervise : %ld\n", philo[i].id, philo[i + 1].last_meal);
		if (philo[i].last_meal == 0)
		{
			time = get_time() - philo[i].data->start_time;
			
		}
		else
		{
			time = get_time() - philo[i].last_meal;
			//printf("philo nbr : %d || last_meal : %ld\n", philo[i].id, philo[i].last_meal);
		}
		if (time > philo[i].data->time_to_die)
		{
			philo[i].has_to_die = 1;
			print_status(now(philo[i].data->start_time), philo, "died");
			pthread_mutex_unlock(&philo[i].data->lock);	
			break ;
		}
		pthread_mutex_unlock(&philo[i].data->lock);
		i++;
	}
	return (NULL);
}*/