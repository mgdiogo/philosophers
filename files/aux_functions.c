/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:34:01 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/14 00:09:24 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*philo(void);
long	get_time(void);
long	ft_atoi(char *str);
void	print_actions(int id, char *str);

t_philo	*philo(void)
{
	static t_philo	philo;

	return (&philo);
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
		{
			printf("Arguments should always be positive.\n");
			printf("Make sure not to use more than one '+' sign!\n");
			exit (1);
		}
		else
			res = (res * 10) + str[i] - 48;
		i++;
	}
	return (res);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000L + time.tv_usec);
}

void	print_actions(int id, char *str)
{
	pthread_mutex_lock(&philo()->print_mutex);
	printf("%ld\t%i\t%s\n", ((get_time() - philo()->start_time) / 1000),
		id, str);
	pthread_mutex_unlock(&philo()->print_mutex);
}

void	sync_func(void)
{
	long	time;

	time = philo()->start_time - get_time();
	if (time > 0)
		usleep(time);
}
