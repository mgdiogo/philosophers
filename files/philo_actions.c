/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:07 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/06 14:38:08 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ph_eat(t_philo_data *ph);
void	ph_think(t_philo_data *ph);
int		ph_death(t_philo_data *ph);

void	ph_eat(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is eating!");
	if (ph->n_times_eat > 0)
		ph->n_times_eat -= 1;
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
	print_actions(ph->philo_id, "is thinking!");
}

void	ph_sleep(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is sleeping!");
	usleep(philo()->time_sleep);
}
