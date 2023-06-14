/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:16:26 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/23 12:47:37 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_and_assign_values(int argc, char **argv, t_values *values)
{
	if (!check_values(argv))
		return (0);
	values->nb_of_philos = ft_atoi(argv[1]);
	values->time_to_die = ft_atoi(argv[2]);
	values->time_to_eat = ft_atoi(argv[3]) * 1000 * 0.999;
	values->time_to_sleep = ft_atoi(argv[4]) * 1000 * 0.999;
	values->count = 1;
	values->finished = 0;
	values->should_eat_to_stop = FALSE;
	values->stop = FALSE;
	if (argc == 6)
	{
		values->should_eat_to_stop = TRUE;
		values->nb_of_eat_to_stop = ft_atoi(argv[5]);
	}
	if (!malloc_and_memset(values))
		return (0);
	return (1);
}

void	case_one(t_values *values)
{
	printf("%s0 1 is thinking%s\n", YELLOW, NC);
	printf("%s0 1 has taken a fork%s\n", GREEN, NC);
	usleep(values->time_to_die * 1000);
	printf("%s%u 1 died%s\n", RED, values->time_to_die, NC);
}

int	thread_and_mutexs_init(t_values *values)
{
	int			i;

	mutex_init(values);
	i = -1;
	gettimeofday(&values->start_time, 0);
	if (values->nb_of_philos > 1)
	{
		while (++i < values->nb_of_philos)
			if (pthread_create(values->threads + i, NULL, &initialize_philo,
					(void *)values) != 0)
				return (printf("error\n"));
	}
	else
		case_one(values);
	return (1);
}

void	mutex_init(t_values *values)
{
	int	i;

	i = -1;
	while (++i < values->nb_of_philos)
		pthread_mutex_init(&values->forks[i], NULL);
	pthread_mutex_init(&values->values_mutex, NULL);
	pthread_mutex_init(&values->printf_mutex, NULL);
	pthread_mutex_init(&values->monitor_mutex, NULL);
}
