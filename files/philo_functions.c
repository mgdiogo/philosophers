/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:14:38 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/03 17:08:04 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_philos(void);
void	allocate_philos(void);
void	*philo_routine(void *arg);

void	allocate_philos(void)
{
	int	i;

	i = -1;
	philo()->philos = malloc(sizeof(t_philo_data) * philo()->n_philos);
	philo()->forks = malloc(sizeof(pthread_mutex_t) * philo()->n_philos);
	while (++i < philo()->n_philos)
		pthread_mutex_init(&philo()->forks[i], 0);
	pthread_mutex_init(&philo()->print_mutex, 0);
	pthread_mutex_init(&philo()->data_mutex, 0);
	create_philos();
}

void	create_philos(void)
{
	int	i;

	i = -1;
	while (++i < philo()->n_philos)
	{
		philo()->philos[i].philo_id = i;
		philo()->philos[i].last_meal = get_time();
		philo()->philos[i].n_times_eat = philo()->n_times_eat;
	}
	i = -1;
	while (++i < philo()->n_philos)
		pthread_create(&philo()->philos[i].ph_thread, 
			NULL, &philo_routine, (void *)&philo()->philos[i]);
}

void	*philo_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	sync_func();
	while (!ph_death(ph))
		print_actions(ph->philo_id, "has said hello");
	return (NULL);
}
