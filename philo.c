/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:28:10 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/31 17:05:04 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6)
	{
		philo()->n_philos = ft_atoi(argv[1]);
		if (philo()->n_philos <= 0)
			return (printf("%s\n", INVALID_PH));
		philo()->time_death = ft_atoi(argv[2]);
		philo()->time_eat = ft_atoi(argv[3]);
		philo()->time_sleep = ft_atoi(argv[4]);
		philo()->start_time = get_time();
		if (argc == 6)
			philo()->n_times_eat = ft_atoi(argv[5]);
		allocate_philos();
	}
	else
		printf("Error: you're either using too many args, or too few!\n");
	return (0);
}
