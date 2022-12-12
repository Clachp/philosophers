/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:35:08 by cchapon           #+#    #+#             */
/*   Updated: 2022/12/12 16:55:12 by cchapon          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo *philo;
	t_data	data;
	
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