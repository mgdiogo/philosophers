/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:22:09 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/14 00:13:31 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void				clean_up(void);
void				get_forks(t_philo_data *ph);
void				eating_process(t_philo_data *ph);

void	get_forks(t_philo_data *ph)
{
	if (ph->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo()->forks[ph->philo_id]);
		print_actions(ph->philo_id, " has taken a fork!");
		pthread_mutex_lock(&philo()->forks[ph->philo_id + 1 
			% philo()->n_philos]);
		print_actions(ph->philo_id, " has taken a fork!");
	}
	else
	{
		pthread_mutex_lock(&philo()->forks[ph->philo_id + 1 
			% philo()->n_philos]);
		print_actions(ph->philo_id, " has taken a fork!");
		pthread_mutex_lock(&philo()->forks[ph->philo_id]);
		print_actions(ph->philo_id, " has taken a fork!");
	}
}

void	eating_process(t_philo_data *ph)
{
	get_forks(ph);
	ph_eat(ph);
	pthread_mutex_unlock(&philo()->forks[ph->philo_id + 1 
		% philo()->n_philos]);
	pthread_mutex_unlock(&philo()->forks[ph->philo_id]);
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
		pthread_mutex_destroy(&(philo()->forks[i]));
	pthread_mutex_destroy(&philo()->print_mutex);
	pthread_mutex_destroy(&philo()->data_mutex);
	free(philo()->forks);
	free(philo()->philos);
}
