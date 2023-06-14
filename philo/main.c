/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:04:15 by rciaze            #+#    #+#             */
/*   Updated: 2023/05/23 13:12:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_values	values;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Bad usage."));
	if (!check_and_assign_values(argc, argv, &values))
		return (0);
	if (thread_and_mutexs_init(&values) != 1)
		return (0);
	i = -1;
	while (++i < values.nb_of_philos && values.nb_of_philos != 1)
		if (pthread_join(values.threads[i], NULL) != 0)
			return (printf("error 1\n"));
	free_that_shit(&values);
	return (0);
}
