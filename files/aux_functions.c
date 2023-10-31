/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:34:01 by mpedroso          #+#    #+#             */
/*   Updated: 2023/10/31 14:59:32 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	print_actions(int id, char *str)
{
	pthread_mutex_lock(&philo()->print);
	printf("%ld |\t %i is %s\n", get_time(), id, str);
	pthread_mutex_unlock(&philo()->print);
}

