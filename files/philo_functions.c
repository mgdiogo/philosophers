/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:14:38 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/18 19:04:42 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_philos(void);
void	allocate_philos(void);
void	u_sleep(long time_sleep);
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
	pthread_mutex_init(&philo()->last_meal, 0);
	pthread_mutex_init(&philo()->t_eat_mutex, 0);
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
		pthread_create(&philo()->philos[i].ph_thread, NULL, 
			&philo_routine, (void *)&philo()->philos[i]);
	if (philo()->n_philos > 1)
		death_checker();
}

void	*philo_routine(void *arg)
{
	t_philo_data	*ph;

	ph = (t_philo_data *)arg;
	sync_func();
	if (philo()->n_philos == 1)
	{
		print_actions(ph, ph->philo_id, "has taken a fork");
		u_sleep(philo()->time_death);
		print_actions(ph, ph->philo_id, "has died");
		return (NULL);
	}
	if (ph->philo_id % 2 == 0)
		u_sleep(1000);
	while (!check_death(ph))
		eating_process(ph);
	return (NULL);
}

void	u_sleep(long time_sleep)
{
	int		i;
	long	time;

	time = get_time();
	while (get_time() - time < time_sleep)
	{
		i = -1;
		while (++i < philo()->n_philos)
		{
			if (check_death(&philo()->philos[i]))
				return ;
		}
		usleep(time_sleep / 1000);
	}
}
