/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:07 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/15 20:32:42 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ph_eat(t_philo_data *ph);
void	ph_think(t_philo_data *ph);
void	ph_sleep(t_philo_data *ph);
int		ph_death(t_philo_data *ph);

void	ph_eat(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is eating");
	if (ph->n_times_eat != philo()->n_times_eat)
		ph->n_times_eat++;
	ph->last_meal = get_time();
	usleep(philo()->time_eat);
	pthread_mutex_unlock(&philo()->forks[ph->philo_id]);
	pthread_mutex_unlock(&philo()->forks[(ph->philo_id + 1)
		% philo()->n_philos]);
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
		printf("%ld\t%i\t%s\n", ((get_time() - philo()->start_time) / 1000),
			ph->philo_id, "died");
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

	if ((philo()->time_death > (philo()->time_eat * 2)) 
		&& (philo()->n_philos % 2 == 0))
	{
		print_actions(ph->philo_id, "is thinking");
		usleep(500);
		return ;
	}
	wait = philo()->time_death - (get_time() - ph->last_meal)
		- (philo()->time_eat / 2);
	print_actions(ph->philo_id, "is thinking");
	if (wait > 0)
		usleep(wait);
}

void	ph_sleep(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is sleeping");
	usleep(philo()->time_sleep);
}
