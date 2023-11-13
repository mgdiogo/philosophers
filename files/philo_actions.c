/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:07 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/13 22:22:38 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_eat(t_philo_data *ph);
void	ph_think(t_philo_data *ph);
void	ph_sleep(t_philo_data *ph);
int		ph_death(t_philo_data *ph);

void	ph_eat(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is eating!");
	if (ph->n_times_eat != philo()->n_times_eat)
		ph->n_times_eat++;
	ph->last_meal = get_time();
	usleep(philo()->time_eat);
}

int	ph_death(t_philo_data *ph)
{
	pthread_mutex_lock(&philo()->data_mutex);
	if (philo()->flag)
	{
		pthread_mutex_unlock(&philo()->data_mutex);
		return (1);
	}
	if (get_time() - ph->last_meal >= philo()->time_death)
	{
		print_actions(ph->philo_id, "has died!");
		philo()->flag = 1;
		pthread_mutex_unlock(&philo()->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo()->data_mutex);
	return (0);
}

void	ph_think(t_philo_data *ph)
{
	long	wait;

	if (philo()->n_times_eat == 0 || ph->n_times_eat != philo()->n_times_eat)
	{
		print_actions(ph->philo_id, "is thinking!");
		wait = philo()->time_death - (get_time() - ph->last_meal)
			- (philo()->time_eat / 2);
		if (wait > 0)
			usleep(wait);
	}
}

void	ph_sleep(t_philo_data *ph)
{
	if (philo()->n_times_eat == 0 || ph->n_times_eat != philo()->n_times_eat)
	{
		print_actions(ph->philo_id, "is sleeping!");
		usleep(philo()->time_sleep);
	}
}
