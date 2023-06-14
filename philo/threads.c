/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:57:32 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/22 13:33:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (!check_stop(philo))
	{
		usleep(2000);
		pthread_mutex_lock(&philo->values->printf_mutex);
		if (!is_eating(philo) && what_time(&philo->current_time,
				&philo->last_time_eaten) >= philo->values->time_to_die
			&& !check_stop(philo))
		{
			pthread_mutex_lock(&philo->values->values_mutex);
			philo->values->stop = TRUE;
			pthread_mutex_unlock(&philo->values->values_mutex);
			printf("%s%ld %d died%s\n", RED, what_time(&philo->current_time,
					&philo->values->start_time), philo->who_am_i, NC);
		}
		pthread_mutex_unlock(&philo->values->printf_mutex);
	}
	return (NULL);
}

void	look_arround(t_philo *philo)
{
	philo->left_fork = &philo->values->forks[philo->who_am_i - 1];
	if (philo->who_am_i == philo->values->nb_of_philos)
		philo->right_fork = &philo->values->forks[0];
	else
		philo->right_fork = &philo->values->forks[philo->who_am_i];
}

void	*initialize_philo(void *v)
{
	t_philo		philo;

	philo.values = (t_values *) v;
	pthread_mutex_lock(&philo.values->values_mutex);
	philo.who_am_i = philo.values->count;
	philo.values->count++;
	pthread_mutex_unlock(&philo.values->values_mutex);
	pthread_mutex_init(&philo.philo_mutex, NULL);
	gettimeofday(&philo.last_time_eaten, NULL);
	philo.is_eating = FALSE;
	philo.times_eaten = 0;
	look_arround(&philo);
	if (pthread_create(&philo.thread, NULL, &monitoring, (void *)&philo) != 0)
		return ((void)(printf("error\n")), NULL);
	while (!check_stop(&philo))
	{
		if (!eat(&philo))
			ft_sleep(&philo);
		else
			return ((void)pthread_join(philo.thread, NULL), NULL);
	}
	pthread_join(philo.thread, NULL);
	pthread_mutex_destroy(&philo.philo_mutex);
	return (NULL);
}
