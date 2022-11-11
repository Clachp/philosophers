/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchapon <cchapon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:35:08 by cchapon           #+#    #+#             */
/*   Updated: 2022/11/11 18:39:23 by cchapon          ###   ########.fr       */
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

void	*think_routine()
{
	write(1, "thinking routine\n", 18);
}

int	main(int argc, char **argv)
{
	t_data philo;
	
	

}