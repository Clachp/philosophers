/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:39:10 by cchapon           #+#    #+#             */
/*   Updated: 2023/01/03 15:37:26 by cchapon          ###   ########.fr       */
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
	int				has_to_die;
	time_t	start_time;
	time_t	timestsmp;
	pthread_t	death_monitor;
	pthread_t	meals_monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int				id; 
	int				meals;
	int				is_eating;
	time_t			last_meal;
	pthread_mutex_t	plock;
	
	pthread_t		tid; 
	pthread_mutex_t	*left_fork; 
	pthread_mutex_t	*right_fork; 
	t_data	*data;
}	t_philo;


long long	ft_atoi_long(const char *nptr);
time_t	get_time();
int	check_arg(char **argv);
//t_data	init_data(char **argv);
int	init_data(t_data *data, char **argv);
//t_philo	*init_philo(t_data data);
int init_philo(t_data *data);
void	init_threads(t_data *data);
void	*start_routine(void *arg);
void	print_status(time_t time, t_philo *philo, char *status);
void	*supervise(void *arg);
time_t	now(t_data *data);

#endif