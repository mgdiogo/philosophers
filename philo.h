/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:28:14 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/03 15:46:10 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INVALID_PH "The number of philosophers needs to be atleast 1"
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_data
{
	int				philo_id;
	int				n_times_eat;
	long			last_meal;
	pthread_t		ph_thread;
}					t_philo_data;

typedef struct s_philo
{
	int				flag;
	int				n_philos;
	int				n_times_eat;
	long			time_eat;
	long			time_sleep;
	long			time_death;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	*forks;
	t_philo_data	*philos;
}					t_philo;

void				sync_func(void);
t_philo				*philo(void);
long				get_time(void);
long				ft_atoi(char *str);
void				create_philos(void);
void				allocate_philos(void);
void				*philo_routine(void *arg);
void				ph_eat(t_philo_data *ph);
int					ph_death(t_philo_data *ph);
void				print_actions(int id, char *str);

#endif