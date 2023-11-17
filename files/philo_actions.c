/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:07 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/17 23:45:05 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_eat(t_philo_data *ph);
void	ph_think(t_philo_data *ph);
void	ph_sleep(t_philo_data *ph);
int		ph_death(t_philo_data *ph);
int		check_death(t_philo_data *ph);

void	ph_eat(t_philo_data *ph)
{
	print_actions(ph, ph->philo_id, "is eating");
	pthread_mutex_lock(&philo()->t_eat_mutex);
	if (ph->n_times_eat != philo()->n_times_eat)
		ph->n_times_eat++;
	pthread_mutex_unlock(&philo()->t_eat_mutex);
	pthread_mutex_lock(&philo()->last_meal);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&philo()->last_meal);
	usleep(philo()->time_eat);
	pthread_mutex_unlock(&philo()->forks[ph->philo_id]);
	pthread_mutex_unlock(&philo()->forks[(ph->philo_id + 1)
		% philo()->n_philos]);
}

int	ph_death(t_philo_data *ph)
{
	pthread_mutex_lock(&philo()->last_meal);
	if (get_time() - ph->last_meal >= philo()->time_death)
	{
		print_actions(ph, ph->philo_id, "died");
		pthread_mutex_unlock(&philo()->last_meal);
		pthread_mutex_lock(&philo()->data_mutex);
		philo()->flag = 1;
		pthread_mutex_unlock(&philo()->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo()->last_meal);
	return (0);
}

void	ph_think(t_philo_data *ph)
{
	long	wait;

	if ((philo()->time_death > (philo()->time_eat * 2)) 
		&& (philo()->n_philos % 2 == 0))
	{
		print_actions(ph, ph->philo_id, "is thinking");
		usleep(500);
		return ;
	}
	wait = (philo()->time_death - (get_time() - ph->last_meal)
			- philo()->time_eat) / 2;
	print_actions(ph, ph->philo_id, "is thinking");
	if (wait > 0)
		usleep(wait);
}

void	ph_sleep(t_philo_data *ph)
{
	long	wait;

	wait = philo()->time_death - (get_time() - ph->last_meal);
	print_actions(ph, ph->philo_id, "is sleeping");
	if (wait < philo()->time_sleep)
		usleep(wait);
	else
		usleep(philo()->time_sleep);
}

int	check_death(t_philo_data *ph)
{
	pthread_mutex_lock(&philo()->data_mutex);
	pthread_mutex_lock(&philo()->t_eat_mutex);
	if (philo()->flag || (philo()->n_times_eat > 0
			&& ph->n_times_eat == philo()->n_times_eat))
	{
		pthread_mutex_unlock(&philo()->data_mutex);
		pthread_mutex_unlock(&philo()->t_eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo()->data_mutex);
	pthread_mutex_unlock(&philo()->t_eat_mutex);
	return (0);
}
