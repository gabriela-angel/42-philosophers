/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:23:41 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:20 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_meal_mutexes(int stop_index)
{
	t_table	*table;
	int		i;

	i = -1;
	table = get_table();
	if (!table || stop_index < 0)
		return ;
	while (++i <= stop_index)
		pthread_mutex_destroy(&(table->threads[i]).meal_lock);
}

static void	destroy_fork_mutexes(int stop_index)
{
	t_table	*table;
	int		i;

	i = -1;
	table = get_table();
	if (!table || stop_index < 0)
		return ;
	while (++i <= stop_index)
		pthread_mutex_destroy(&table->fork_locks[i]);
}

void	destroy_stage_mutexes(int stop_index, int stage)
{
	t_table	*table;

	table = get_table();
	if (!table)
		return ;
	if (stage == 0 && stop_index >= 0)
		destroy_meal_mutexes(stop_index);
	else if (stage == 1 && stop_index <= 0)
	{
		destroy_meal_mutexes(table->n_of_philos - 1);
		destroy_fork_mutexes(stop_index);
	}
	else if (stage >= 2)
	{
		destroy_meal_mutexes(table->n_of_philos - 1);
		destroy_fork_mutexes(table->n_of_philos - 1);
		pthread_mutex_destroy(&table->stop_lock);
	}
	if (stage >= 3)
		pthread_mutex_destroy(&table->print_lock);
	if (stage >= 4)
		pthread_mutex_destroy(&table->start_lock);
}

void	print_err_msg(char *error_msg)
{
	printf("%s\n", error_msg);
}

void	handle_error(char *error_msg, int stage, int stop_index)
{
	if (stage > -1)
		destroy_stage_mutexes(stop_index, stage);
	ft_gc_exit();
	print_err_msg(error_msg);
	exit(1);
}
