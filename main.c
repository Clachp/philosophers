/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:35:08 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/13 16:44:47 by cchapon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// 3 routines = 3 fonctions pour manger dormir penser
// chaque thread (= chaque philo) appelle ces trois routines en boucle ou 
// num_of_time_each_philo_must_eat

// argv[1] = number_of_philosophes = number_of_forks
// chaque fourchette est a proteger par un mutex pour garder le bon nombre de fourchettes 
// argv[2] = time_to_die
// argv[3] = time_to_eat
// argv[4] = time_to_sleep
// argv[5] = number_of_time_each_philo_must_eat	

int	check_arg(char **argv)
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	
	if (check_arg(argv) == -1)
	{
		printf("Wrong input format\n");
		return (0);
	}
	if (argc == 5 || argc == 6)
	{
		data = init_data(argv);
		philo = init_philo(data);
	}
	else
		printf("Wrong argument number\n");
	free(philo);
	return (0);
}