/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:02:14 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/16 20:52:13 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*supervise(void *arg)
{
	t_philo	*philo;
	time_t	time;

	philo = (t_philo*)arg;
	if (philo->last_meal > philo->data->time_to_die)
	{
		philo->has_to_die = 1;
	}
		
	
}