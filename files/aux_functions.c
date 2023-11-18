/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:34:01 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/18 19:15:37 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*philo(void);
long	get_time(void);
void	sync_func(void);
long	ft_atoi(char *str);
int		check_int(long nbr);

t_philo	*philo(void)
{
	static t_philo	philo;

	return (&philo);
}

int	check_int(long nbr)
{
	if (nbr > MAX_INT)
		return (1);
	return (0);
}

long	ft_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0') || str[i] == '-' || str[i] == '+')
			return (-1);
		else
			res = (res * 10) + str[i] - 48;
		i++;
	}
	if (check_int(res))
		return (-1);
	return (res);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000L + time.tv_usec);
}

void	sync_func(void)
{
	long	time;

	time = philo()->start_time - get_time();
	if (time > 0)
		u_sleep(time);
}
