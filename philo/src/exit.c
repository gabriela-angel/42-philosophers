/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:23:41 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/21 16:01:40 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(void)
{
	t_table	*table;
	int	i;

	i = 0;
	table = get_table();
	if (!table)
		return;
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->stop_lock);
	while (i < table->n_of_philos)
	{
		pthread_mutex_destroy(&(table->threads[i]).meal_lock);
		pthread_mutex_destroy(&table->fork_locks[i]);
		i++;
	}
}

void	print_err_msg(char *error_msg)
{
	printf("%s\n", error_msg);
}

void	handle_error(char *error_msg)
{
	destroy_mutexes();
	ft_gc_exit();
	print_err_msg(error_msg);
	exit(1);
}
