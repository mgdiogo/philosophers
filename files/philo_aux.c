/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:22:09 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/16 17:42:55 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_up(void);
void	death_loop(void);
void	get_forks(t_philo_data *ph);
void	eating_process(t_philo_data *ph);

void	get_forks(t_philo_data *ph)
{
	if (ph->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo()->forks[ph->philo_id]);
		print_actions(ph, ph->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo()->forks[(ph->philo_id + 1)
			% philo()->n_philos]);
		print_actions(ph, ph->philo_id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo()->forks[(ph->philo_id + 1)
			% philo()->n_philos]);
		print_actions(ph, ph->philo_id, "has taken a fork");
		pthread_mutex_lock(&philo()->forks[ph->philo_id]);
		print_actions(ph, ph->philo_id, "has taken a fork");
	}
}

void	eating_process(t_philo_data *ph)
{
	get_forks(ph);
	ph_eat(ph);
	ph_sleep(ph);
	ph_think(ph);
}

void	clean_up(void)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < philo()->n_philos)
		pthread_join(philo()->philos[i].ph_thread, NULL);
	while (++j < philo()->n_philos)
		pthread_mutex_destroy(&(philo()->forks[j]));
	pthread_mutex_destroy(&philo()->print_mutex);
	pthread_mutex_destroy(&philo()->data_mutex);
	pthread_mutex_destroy(&philo()->last_meal);
	pthread_mutex_destroy(&philo()->t_eat_mutex);
	free(philo()->forks);
	free(philo()->philos);
}

void	death_checker(void)
{
	int	i;
	int	eat_checker;

	sync_func();
	while (1)
	{
		i = 0;
		eat_checker = 1;
		while (i++ < philo()->n_philos - 1)
		{
			if (ph_death(&philo()->philos[i]))
				return ;
			if (philo()->philos[i].n_times_eat < philo()->n_times_eat)
				eat_checker = 0;
		}
		pthread_mutex_lock(&philo()->data_mutex);
		if (philo()->n_times_eat > 0 && eat_checker == 1)
		{
			philo()->flag = 1;
			pthread_mutex_unlock(&philo()->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo()->data_mutex);
	}
}
