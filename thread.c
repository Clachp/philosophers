/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/20 19:33:02 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

//

void	*supervise(void *arg)
{
	t_philo	*philo;
	time_t	time;

	philo = (t_philo*)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->last_meal == 0)
		{
			time = get_time() - philo->data->start_time;
			// printf("timing if : %ld\n", time);
		}
		else
		{
		// printf("get time = %ld || start_time = %ld || last_meal = %ld\n", get_time(), philo->data->start_time, philo->last_meal);
			time = get_time() - philo->last_meal;
			// printf("timing else : %ld\n", time);
		}
	// checker le temps pour chaque philo (boucler sur philo[i])
		if (time > philo->data->time_to_die)
		{
			printf("timing : %ld\n", time);
			philo->has_to_die = 1;
			print_status(now(philo->data->start_time), philo, "died");
			pthread_mutex_unlock(&philo->data->lock);	
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (NULL);
}

	// pthread_mutex_lock(&philo->data->lock);
		// if (philo->last_meal > philo->data->time_to_die || get_time() - philo->data->start_time > philo->data->time_to_die)
		// {
		// 	philo->has_to_die = 1;
		// 	print_status(get_time() - philo->data->start_time, philo, "died");
		// 	pthread_mutex_unlock(&philo->data->lock);
		// 	break ;
		// }
		// pthread_mutex_unlock(&philo->data->lock);