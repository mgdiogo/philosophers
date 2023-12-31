/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:28:14 by mpedroso          #+#    #+#             */
/*   Updated: 2023/11/18 19:14:40 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INVALID_PH "The number of philosophers needs to be atleast 1"
# define INVALID_ATOI "Arguments should always be positive.\n\
Make sure not to use more than one '+' sign!\n"
# define MAX_INT 2147483647
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
	pthread_mutex_t	last_meal;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	t_eat_mutex;
	pthread_mutex_t	*forks;
	t_philo_data	*philos;
}					t_philo;

void				clean_up(void);
void				sync_func(void);
void				death_checker(void);
t_philo				*philo(void);
long				get_time(void);
long				ft_atoi(char *str);
void				create_philos(void);
void				allocate_philos(void);
void				*philo_routine(void *arg);
void				ph_eat(t_philo_data *ph);
int					ph_death(t_philo_data *ph);
void				ph_sleep(t_philo_data *ph);
void				ph_think(t_philo_data *ph);
void				get_forks(t_philo_data *ph);
int					check_death(t_philo_data *ph);
void				eating_process(t_philo_data *ph);
void				u_sleep(long time_sleep);
void				print_actions(t_philo_data *ph, int id, char *str);

#endif