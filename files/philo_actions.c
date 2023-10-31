/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:45:07 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/31 16:55:18 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ph_eat(t_philo_data *ph);

void	ph_eat(t_philo_data *ph)
{
	print_actions(ph->philo_id, "is eating!");
	if (ph->n_times_eat > 0)
		ph->n_times_eat -= 1;
	ph->last_meal = get_time();
}
