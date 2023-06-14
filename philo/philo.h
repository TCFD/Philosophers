/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:29:36 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/23 12:34:27 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef                     PHILO_H
# define                    PHILO_H

// Includes
# include                   <stdio.h>
# include                   <stdlib.h>
# include                   <pthread.h>
# include                   <unistd.h>
# include                   <sys/time.h>
# include                   <string.h>
// Colors
# define NC					"\e[0m"
# define RED				"\e[31m"
# define GREEN				"\e[32m"
# define YELLOW				"\e[33m"
# define BLUE				"\e[34m"
# define PURPLE				"\e[35m"
# define CYAN				"\e[36m"
# define LIGHT_GRAY			"\e[37m"
// General macros
# define FALSE				0
# define HOLY_SHIT_IM_DEAD	0
# define TRUE				1
# define IM_ALIVE			1

typedef struct s_values
{
	struct timeval	start_time;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				should_eat_to_stop;
	int				nb_of_eat_to_stop;
	int				nb_of_philos;
	int				count;
	int				stop;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	values_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	even_mutex;
	pthread_mutex_t	uneven_mutex;
	pthread_mutex_t	monitor_mutex;
	pthread_t		*threads;
}	t_values;

typedef struct s_philo
{
	int				who_am_i;
	int				is_eating;
	int				times_eaten;
	struct timeval	last_time_eaten;
	struct timeval	current_time;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_values		*values;
}	t_philo;

int			ft_atoi(char *str);
long int	what_time(struct timeval *time_val, struct timeval *start);
void		*initialize_philo(void *v);
int			eat(t_philo *philo);
int			ft_usleep(useconds_t time, t_philo *philo);
void		ft_sleep(t_philo *philo);
int			check_stop(t_philo *philo);
void		free_that_shit(t_values *values);
int			is_eating(t_philo *philo);
int			thread_and_mutexs_init(t_values *values);
int			check_and_assign_values(int argc, char **argv, t_values *values);
void		mutex_init(t_values *values);
int			malloc_and_memset(t_values *values);
int			check_values(char **argv);
#endif