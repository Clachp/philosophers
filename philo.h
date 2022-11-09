/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:10 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/09 19:21:56 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread>
# include <sys/time.h>

// une structure = data pour un philo
typedef struct s_data
{
	int				id; /*numero du philosophe*/
	pthread_t		*philo_thread; /*identifiant du thread du philo*/
	int				fork; /*doit etre egal a 2 pour manger*/
	struct s_data	*next;
}	t_data;

#endif