/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/19 18:47:47 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*supervise(void *arg)
{
	t_philo	*philo;
	time_t	time;

	philo = (t_philo*)arg;
	pthread_mutex_lock(&philo->data->lock);
	time = get_time() - philo->data->start_time;
	print_status(time, philo, "is in supervise");
	if (philo->last_meal > philo->data->time_to_die)
	{
		
		philo->has_to_die = 1;
		print_status(time, philo, "died");
		
	}
	pthread_mutex_unlock(&philo->data->lock);	
	return (NULL);
}