/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:14:38 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/14 16:10:02 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		philo()->philos[i].n_times_eat = 0;
	}
	i = -1;
	while (++i < philo()->n_philos)
		pthread_create(&philo()->philos[i].ph_thread, 
			NULL, &philo_routine, (void *)&philo()->philos[i]);
	death_loop();
}

void	*philo_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	sync_func();
	if (philo()->n_philos == 1)
	{
		print_actions(ph->philo_id, "has taken a fork");
		usleep(philo()->time_death);
		print_actions(ph->philo_id, "has died");
		return (NULL);
	}
	if (ph->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if ((philo()->n_times_eat > 0 
				&& ph->n_times_eat == philo()->n_times_eat) || ph_death(ph))
			break ;
		eating_process(ph);
	}
	return (NULL);
}
