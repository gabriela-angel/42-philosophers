/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:23:41 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/03 20:01:56 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_philo *threads, int n_of_philos)
{
	int	i;
	int	n_of_philos;

	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(&threads[i].fork_lock);
		i++;
	}
}

void	handle_error(char *error_msg)
{
	t_table	*table;

	table = get_table();
	destroy_mutexes(table->threads, table->n_of_philos);
	ft_free_all();
	printf("%s\n", error_msg);
	exit(1);
}
