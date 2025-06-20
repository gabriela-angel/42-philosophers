/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:23:41 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/19 23:45:14 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// FIX THIS!
void	destroy_mutexes(t_philo *threads, int n_of_philos)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(&threads[i].meal_lock);
		i++;
	}
}

void	print_err_msg(char *error_msg)
{
	printf("%s\n", error_msg);
}

void	handle_error(char *error_msg)
{
	t_table	*table;

	table = get_table();
	destroy_mutexes(table->threads, table->n_of_philos);
	ft_gc_exit();
	print_err_msg(error_msg);
	exit(1);
}
