/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:28:10 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/15 20:31:20 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	if (argc >= 5 && argc <= 6)
	{
		philo()->n_philos = ft_atoi(argv[1]);
		if (philo()->n_philos <= 0)
			return (printf("%s\n", INVALID_PH));
		philo()->time_death = ft_atoi(argv[2]) * 1000;
		philo()->time_eat = ft_atoi(argv[3]) * 1000;
		philo()->time_sleep = ft_atoi(argv[4]) * 1000;
		philo()->start_time = get_time() + (philo()->n_philos * 2);
		if (argc == 6)
			philo()->n_times_eat = ft_atoi(argv[5]);
		if (philo()->time_death < 0 || philo()->time_eat < 0 
			|| philo()->time_sleep < 0)
			return (printf("%s", INVALID_ATOI));
		allocate_philos();
	}
	else
		printf("Error: you're either using too many args, or too few!\n");
	clean_up();
	return (0);
}
