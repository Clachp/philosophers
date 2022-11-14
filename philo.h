/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:10 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/14 18:47:37 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

// data pour un philo
typedef struct s_philo
{
	int				id; /*numero du philosophe*/
	pthread_t		tid; /*identifiant du thread du philo*/
	pthread_mutex_t	fork; /*doit etre egal a 2 pour manger + protegee lors de l'execution d'une routine eat*/
	pthread_mutex_t	left_fork; /*= 0*/
	pthread_mutex_t	right_fork; /* =0 philo mange seulement si left_fork et right fork sont accessibles */
}	t_philo;

// data du programme
typedef struct s_data
{
	int	nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_think;
	int	time_to_sleep;
	
}	t_data;

int	ft_atoi(const char *nptr);

int	get_time();
int	check_arg(char **argv);
t_data	init_data(char **argv);
t_philo	*init_philo(t_data data);

#endif