/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:43:42 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/23 17:35:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->is_eating == TRUE)
		return ((void)pthread_mutex_unlock(&philo->philo_mutex), TRUE);
	pthread_mutex_unlock(&philo->philo_mutex);
	return (FALSE);
}

void	free_that_shit(t_values *values)
{
	pthread_mutex_destroy(&values->values_mutex);
	pthread_mutex_destroy(&values->printf_mutex);	
	pthread_mutex_destroy(&values->monitor_mutex);
	free(values->threads);
	free(values->forks);
}

long int	what_time(struct timeval *time_val, struct timeval *start)
{
	long int	a;

	gettimeofday(time_val, 0);
	a = ((time_val->tv_sec - start->tv_sec) * 1000000 + time_val->tv_usec
			- start->tv_usec) / 1000;
	return (a);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->values->values_mutex);
	if (philo->values->stop)
		return ((void)(pthread_mutex_unlock(&philo->values->values_mutex)), 1);
	pthread_mutex_unlock(&philo->values->values_mutex);
	return (0);
}

int	ft_usleep(useconds_t time, t_philo *philo)
{
	int	j;
	int	k;

	j = time / 5;
	k = 0;
	while (k < 5 && !check_stop(philo))
	{
		usleep(j);
		k++;
	}
	if (check_stop(philo))
		return (0);
	return (1);
}
