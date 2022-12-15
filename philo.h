/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:10 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/15 19:29:10 by cchapon          ###   ########.fr       */
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

typedef struct s_data
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_think;
	int	time_to_sleep;
	int meals_nbr;
	time_t	start_time;
	time_t	timestsmp;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int				id; 
	int				meals;
	int				is_eating;
	int				last_meal;
	pthread_t		tid; 
	pthread_mutex_t	left_fork; 
	pthread_mutex_t	*right_fork; 
	t_data	*data;
}	t_philo;


int	ft_atoi(const char *nptr);
time_t	get_time();
int	check_arg(char **argv);
//t_data	init_data(char **argv);
int	init_data(t_data *data, char **argv);
//t_philo	*init_philo(t_data data);
int init_philo(t_data *data, t_philo *philo);
void	init_threads(t_philo *philo, t_data *data);

#endif