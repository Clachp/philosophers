/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:10 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/17 17:50:16 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

// data pour un philo
typedef struct s_philo
{
	int				id; /*numero du philosophe*/
	pthread_t		tid; /*identifiant du thread du philo*/
	pthread_mutex_t	left_fork; /* fourchette du philo N */
	pthread_mutex_t	*right_fork; /* fourchette du philo N + 1 */
	struct s_data	*data;
}	t_philo;
// donnee partagees a protgeger par des mutex
// + proteger les printf par des mutex

typedef struct s_data
{
	int	n;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_think;
	int	time_to_sleep;
	time_t	start_time;
	time_t	timestsmp;
	pthread_mutex_t	*forks;
	t_philo	*philo;
}	t_data;

int	ft_atoi(const char *nptr);
time_t	get_time();
int	check_arg(char **argv);
t_data	init_data(char **argv);
t_philo	*init_philo(t_data data);

#endif