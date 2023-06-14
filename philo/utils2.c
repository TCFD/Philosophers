/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:19:25 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/22 13:33:26 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	return_value;
	int	boolean;

	i = 0;
	return_value = 0;
	boolean = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	i--;
	if (str[++i] == '-' || str[i] == '+')
		if (str[i] == '-')
			boolean = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		return_value *= 10;
		return_value += str[i] - 48;
		i++;
	}
	if (boolean)
		return (-return_value);
	return (return_value);
}

int	malloc_and_memset(t_values *values)
{
	values->threads = malloc(sizeof(pthread_t) * values->nb_of_philos);
	if (!values->threads)
		return (0);
	memset(values->threads, 0, sizeof(pthread_t) * values->nb_of_philos);
	values->forks = malloc(sizeof(pthread_mutex_t) * (values->nb_of_philos));
	if (!values->forks)
		return (free(values->threads), 0);
	memset(values->forks, 0, sizeof(pthread_mutex_t)
		* (values->nb_of_philos));
	return (1);
}

int	check_values(char **argv)
{
	int	i;
	int	temp;

	i = 0;
	while (argv[++i])
	{
		temp = ft_atoi(argv[i]);
		if (temp <= 0)
			return (0);
	}
	return (1);
}
