/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:57:35 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/22 13:20:13 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	let_forks_go(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
	if (philo->values->should_eat_to_stop
		&& philo->times_eaten == philo->values->nb_of_eat_to_stop)
	{
		pthread_mutex_lock(&philo->values->values_mutex);
		if (++philo->values->finished == philo->values->nb_of_philos)
			philo->values->stop = TRUE;
		pthread_mutex_unlock(&philo->values->values_mutex);
	}
	return (0);
}

int	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->values->printf_mutex);
	if (!check_stop(philo))
		printf("%s%ld %d has taken a fork%s\n", GREEN, what_time
			(&philo->current_time, &philo->values->start_time),
			philo->who_am_i, NC);
	pthread_mutex_unlock(&philo->values->printf_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->values->printf_mutex);
	if (!check_stop(philo))
		printf("%s%ld %d has taken a fork%s\n", GREEN, what_time
			(&philo->current_time, &philo->values->start_time),
			philo->who_am_i, NC);
	pthread_mutex_unlock(&philo->values->printf_mutex);
	return (1);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->values->printf_mutex);
	if (!check_stop(philo))
		printf("%s%ld %d is sleeping%s\n", PURPLE, what_time(&philo
				->current_time, &philo->values->start_time),
			philo->who_am_i, NC);
	pthread_mutex_unlock(&philo->values->printf_mutex);
	ft_usleep(philo->values->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->values->printf_mutex);
	if (!check_stop(philo))
		printf("%s%ld %d is thinking%s\n", YELLOW, what_time(&philo
				->current_time, &philo->values->start_time),
			philo->who_am_i, NC);
	pthread_mutex_unlock(&philo->values->printf_mutex);
	if (philo->times_eaten == 0 && philo->who_am_i % 2 == 0)
		usleep(philo->values->time_to_eat * 0.9);
}

int	eat(t_philo *philo)
{
	think(philo);
	if (!grab_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = TRUE;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_lock(&philo->values->printf_mutex);
	if (!check_stop(philo))
		printf("%s%ld %d is eating%s\n", CYAN, what_time(&philo
				->current_time, &philo->values->start_time),
			philo->who_am_i, NC);
	pthread_mutex_unlock(&philo->values->printf_mutex);
	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&philo->last_time_eaten, NULL);
	philo->is_eating = FALSE;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_usleep(philo->values->time_to_eat, philo);
	return (let_forks_go(philo));
}
